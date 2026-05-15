/*
 * Análisis experimental – Tarea 2 "Divide y Vencerás"
 *
 * Genera los CSV para los 13 gráficos requeridos:
 *   G1  → data/g1_merge_umbrales.csv
 *   G2-4 → data/g2_g3_g4_merge_casos.csv
 *   G5-7 → data/g5_g6_g7_quick_pivotes.csv
 *   G8-10 → data/g8_g9_g10_t1_vs_t2.csv
 *   G11-12 → data/g11_g12_busqueda.csv
 *   G13  → data/g13_quickselect.csv
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "algoritmos.h"

/* ─── Configuración ──────────────────────────────────────────── */
#define REPETICIONES    10      /* promediar sobre N ejecuciones */
#define RANGO_PUNTAJE   10001   /* rand() % RANGO_PUNTAJE        */

/* Tamaños para algoritmos O(n log n)  →  gráficos T2 y comparativas */
static int TAMANOS_T2[]     = {10000, 20000, 30000, 40000, 50000};
static int NUM_T2           = 5;

/* Tamaños para algoritmos O(n²) de T1  →  gráficos T1 vs T2 */
static int TAMANOS_T1[]     = {1000, 2000, 3000, 4000, 5000};
static int NUM_T1           = 5;

/* Umbrales a probar para Merge Sort optimizado */
static int UMBRALES[]       = {1, 10, 30, 60};
static int NUM_UMBRALES     = 4;

/* ─── Utilidades ─────────────────────────────────────────────── */

/* Tiempo en segundos entre dos clock_t */
static inline double seg(clock_t inicio, clock_t fin) {
    return (double)(fin - inicio) / CLOCKS_PER_SEC;
}

/* Copia el arreglo fuente → destino */
static void copiar(Deportista *dst, const Deportista *src, int n) {
    memcpy(dst, src, n * sizeof(Deportista));
}

/* ─── Generadores de casos ───────────────────────────────────── */

void generarCasoPromedio(Deportista arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i].id      = i + 1;
        arr[i].puntaje = rand() % RANGO_PUNTAJE;
        sprintf(arr[i].nombre, "Dep%d", i);
    }
}

/*
 * Mejor caso para ordenamiento descendente:
 *   arreglo ya ordenado de mayor a menor  →  merge sort O(n log n) sin merges extras,
 *   quick sort con mediana-3 elige buen pivote, etc.
 */
void generarMejorCasoOrdenamiento(Deportista arr[], int n) {
    generarCasoPromedio(arr, n);
    mergeSort(arr, 0, n - 1);          /* ordena ascendente          */
    /* invertir para obtener orden descendente */
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        Deportista tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
    }
}

/*
 * Peor caso para Quick Sort con pivote último/primero:
 *   arreglo ya ordenado ascendente  →  el pivote siempre es mínimo/máximo
 *   y la partición queda 0 | n-1 elementos  →  O(n²).
 */
void generarPeorCasoOrdenamiento(Deportista arr[], int n) {
    generarCasoPromedio(arr, n);
    mergeSort(arr, 0, n - 1);          /* ordena ascendente (peor para pivote ultimo) */
}

/* ─── Macros de medición (evitan repetir el mismo patrón) ────── */

/*
 * MEDIR(func_call, acumulador)
 * Copia `orig` → `copia`, ejecuta func_call, suma el tiempo a `acumulador`.
 * Usar dentro de un for(r=0; r<REPETICIONES; r++).
 */
#define MEDIR(src, copia, n, func_call, acum)          \
    do {                                                \
        copiar((copia), (src), (n));                    \
        clock_t _t0 = clock();                         \
        (func_call);                                    \
        (acum) += seg(_t0, clock());                   \
    } while (0)

/* Promedio dividiendo entre REPETICIONES */
#define PROM(acum) ((acum) / REPETICIONES)

/* ═══════════════════════════════════════════════════════════════
 * G1 – Análisis de umbrales de Merge Sort optimizado
 *      CSV: N, k1, k10, k30, k60
 * ═══════════════════════════════════════════════════════════════ */
void experimento_G1(FILE *f) {
    fprintf(f, "N");
    for (int u = 0; u < NUM_UMBRALES; u++)
        fprintf(f, ",k%d", UMBRALES[u]);
    fprintf(f, "\n");

    Deportista *orig  = malloc(TAMANOS_T2[NUM_T2-1] * sizeof(Deportista));
    Deportista *copia = malloc(TAMANOS_T2[NUM_T2-1] * sizeof(Deportista));

    for (int i = 0; i < NUM_T2; i++) {
        int n = TAMANOS_T2[i];
        generarCasoPromedio(orig, n);
        fprintf(f, "%d", n);

        for (int u = 0; u < NUM_UMBRALES; u++) {
            double acum = 0.0;
            int k = UMBRALES[u];
            for (int r = 0; r < REPETICIONES; r++)
                MEDIR(orig, copia, n, mergeSortOptimizado(copia, 0, n-1, k), acum);
            fprintf(f, ",%.6f", PROM(acum));
        }
        fprintf(f, "\n");
    }
    free(orig); free(copia);
    printf("  G1 OK\n");
}

/* ═══════════════════════════════════════════════════════════════
 * G2-G4 – Merge Sort clásico vs optimizado (mejor/peor/promedio)
 *         CSV: N, caso, clasico, optimizado
 *         "caso" = mejor | peor | promedio
 * ═══════════════════════════════════════════════════════════════ */
void experimento_G2_G3_G4(FILE *f) {
    fprintf(f, "N,caso,clasico,optimizado\n");

    /* Umbral óptimo para merge optimizado (ajusta si G1 indica otro) */
    int UMBRAL_OPT = 30;

    Deportista *orig  = malloc(TAMANOS_T2[NUM_T2-1] * sizeof(Deportista));
    Deportista *copia = malloc(TAMANOS_T2[NUM_T2-1] * sizeof(Deportista));

    typedef void (*GenFunc)(Deportista*, int);
    const char *nombres[] = {"mejor", "peor", "promedio"};
    GenFunc gens[]        = {generarMejorCasoOrdenamiento,
                              generarPeorCasoOrdenamiento,
                              generarCasoPromedio};

    for (int c = 0; c < 3; c++) {
        for (int i = 0; i < NUM_T2; i++) {
            int n = TAMANOS_T2[i];
            gens[c](orig, n);

            double a_clas = 0.0, a_opt = 0.0;
            for (int r = 0; r < REPETICIONES; r++) {
                MEDIR(orig, copia, n, mergeSort(copia, 0, n-1), a_clas);
                MEDIR(orig, copia, n, mergeSortOptimizado(copia, 0, n-1, UMBRAL_OPT), a_opt);
            }
            fprintf(f, "%d,%s,%.6f,%.6f\n",
                    n, nombres[c], PROM(a_clas), PROM(a_opt));
        }
    }
    free(orig); free(copia);
    printf("  G2-G4 OK\n");
}

/* ═══════════════════════════════════════════════════════════════
 * G5-G7 – Quick Sort: 4 variantes de pivote × 3 casos
 *          CSV: N, caso, ultimo, primero, aleatorio, mediana3
 * ═══════════════════════════════════════════════════════════════ */
void experimento_G5_G6_G7(FILE *f) {
    fprintf(f, "N,caso,ultimo,primero,aleatorio,mediana3\n");

    Deportista *orig  = malloc(TAMANOS_T2[NUM_T2-1] * sizeof(Deportista));
    Deportista *copia = malloc(TAMANOS_T2[NUM_T2-1] * sizeof(Deportista));

    typedef void (*GenFunc)(Deportista*, int);
    const char *nombres[] = {"mejor", "peor", "promedio"};
    GenFunc gens[]        = {generarMejorCasoOrdenamiento,
                              generarPeorCasoOrdenamiento,
                              generarCasoPromedio};

    for (int c = 0; c < 3; c++) {
        for (int i = 0; i < NUM_T2; i++) {
            int n = TAMANOS_T2[i];
            gens[c](orig, n);

            double a1=0, a2=0, a3=0, a4=0;
            for (int r = 0; r < REPETICIONES; r++) {
                MEDIR(orig, copia, n, quickSort(copia, 0, n-1, 1), a1); /* ultimo    */
                MEDIR(orig, copia, n, quickSort(copia, 0, n-1, 2), a2); /* primero   */
                MEDIR(orig, copia, n, quickSort(copia, 0, n-1, 3), a3); /* aleatorio */
                MEDIR(orig, copia, n, quickSort(copia, 0, n-1, 4), a4); /* mediana3  */
            }
            fprintf(f, "%d,%s,%.6f,%.6f,%.6f,%.6f\n",
                    n, nombres[c],
                    PROM(a1), PROM(a2), PROM(a3), PROM(a4));
        }
    }
    free(orig); free(copia);
    printf("  G5-G7 OK\n");
}

/* ═══════════════════════════════════════════════════════════════
 * G8-G10 – Comparación Tarea 1 vs Tarea 2 (todos los algoritmos)
 *           CSV: N, caso, bubble, insertion, selection, cocktail,
 *                merge, quick
 *  Nota: T1 usa TAMANOS_T1 (pequeños); T2 también trabaja bien
 *        ahí, así que la comparación es directa y justa.
 * ═══════════════════════════════════════════════════════════════ */
void experimento_G8_G9_G10(FILE *f) {
    fprintf(f, "N,caso,bubble,insertion,selection,cocktail,merge,quick\n");

    Deportista *orig  = malloc(TAMANOS_T1[NUM_T1-1] * sizeof(Deportista));
    Deportista *copia = malloc(TAMANOS_T1[NUM_T1-1] * sizeof(Deportista));

    typedef void (*GenFunc)(Deportista*, int);
    const char *nombres[] = {"mejor", "peor", "promedio"};
    GenFunc gens[]        = {generarMejorCasoOrdenamiento,
                              generarPeorCasoOrdenamiento,
                              generarCasoPromedio};

    for (int c = 0; c < 3; c++) {
        for (int i = 0; i < NUM_T1; i++) {
            int n = TAMANOS_T1[i];
            gens[c](orig, n);

            double a_bub=0, a_ins=0, a_sel=0, a_ckt=0,
                   a_mrg=0, a_qck=0;

            for (int r = 0; r < REPETICIONES; r++) {
                MEDIR(orig, copia, n, bubbleSort(copia, n),          a_bub);
                MEDIR(orig, copia, n, insertionSortN(copia, n),       a_ins);
                MEDIR(orig, copia, n, selectionSort(copia, n),       a_sel);
                MEDIR(orig, copia, n, cocktailShakerSort(copia, n),  a_ckt);
                MEDIR(orig, copia, n, mergeSort(copia, 0, n-1),      a_mrg);
                /* Quick: usar mediana-3 como representante de T2    */
                MEDIR(orig, copia, n, quickSort(copia, 0, n-1, 4),   a_qck);
            }
            fprintf(f, "%d,%s,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f\n",
                    n, nombres[c],
                    PROM(a_bub), PROM(a_ins), PROM(a_sel), PROM(a_ckt),
                    PROM(a_mrg), PROM(a_qck));
        }
    }
    free(orig); free(copia);
    printf("  G8-G10 OK\n");
}

/* ═══════════════════════════════════════════════════════════════
 * G11-G12 – Algoritmos de búsqueda (peor caso y caso promedio)
 *            CSV: N, caso, secuencial, binaria_iter, binaria_rec,
 *                 binaria_rango, exponencial, interpolacion
 *
 *  Peor caso  : buscar un elemento que NO existe (recorre todo)
 *  Caso promedio: buscar un elemento que SÍ existe, elegido al azar
 * ═══════════════════════════════════════════════════════════════ */
void experimento_G11_G12(FILE *f) {
    fprintf(f, "N,caso,secuencial,binaria_iter,binaria_rec,"
               "binaria_rango,exponencial,interpolacion\n");

    Deportista *arr   = malloc(TAMANOS_T2[NUM_T2-1] * sizeof(Deportista));
    int primero, ultimo; /* para busquedaBinariaRangos */

    for (int i = 0; i < NUM_T2; i++) {
        int n = TAMANOS_T2[i];

        /* Generar y ORDENAR el arreglo (requisito de todas las búsquedas) */
        generarCasoPromedio(arr, n);
        mergeSort(arr, 0, n - 1);

        /* Elemento garantizado fuera del rango → peor caso real */
        int target_peor    = RANGO_PUNTAJE + 1;
        /* Elemento existente en posición aleatoria → caso promedio */
        int idx_random     = rand() % n;

        /* --- PEOR CASO --- */
        {
            double a_seq=0, a_bi=0, a_br=0, a_brng=0, a_exp=0, a_int=0;
            for (int r = 0; r < REPETICIONES; r++) {
                clock_t t0;

                t0 = clock(); busquedaSecuencial(arr, n, target_peor);
                a_seq  += seg(t0, clock());

                t0 = clock(); busquedaBinariaIterativa(arr, 0, n-1, target_peor);
                a_bi   += seg(t0, clock());

                t0 = clock(); busquedaBinariaRecursiva(arr, 0, n-1, target_peor);
                a_br   += seg(t0, clock());

                t0 = clock(); busquedaBinariaRangos(arr, n, target_peor, &primero, &ultimo);
                a_brng += seg(t0, clock());

                t0 = clock(); busquedaExponencial(arr, n, target_peor);
                a_exp  += seg(t0, clock());

                t0 = clock(); busquedaInterpolacion(arr, n, target_peor);
                a_int  += seg(t0, clock());
            }
            fprintf(f, "%d,peor,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f\n",
                    n, PROM(a_seq), PROM(a_bi), PROM(a_br),
                    PROM(a_brng), PROM(a_exp), PROM(a_int));
        }

        /* --- CASO PROMEDIO --- */
        {
            double a_seq=0, a_bi=0, a_br=0, a_brng=0, a_exp=0, a_int=0;
            for (int r = 0; r < REPETICIONES; r++) {
                /* Re-elegir posición aleatoria en cada repetición */
                int t = arr[rand() % n].puntaje;
                clock_t t0;

                t0 = clock(); busquedaSecuencial(arr, n, t);
                a_seq  += seg(t0, clock());

                t0 = clock(); busquedaBinariaIterativa(arr, 0, n-1, t);
                a_bi   += seg(t0, clock());

                t0 = clock(); busquedaBinariaRecursiva(arr, 0, n-1, t);
                a_br   += seg(t0, clock());

                t0 = clock(); busquedaBinariaRangos(arr, n, t, &primero, &ultimo);
                a_brng += seg(t0, clock());

                t0 = clock(); busquedaExponencial(arr, n, t);
                a_exp  += seg(t0, clock());

                t0 = clock(); busquedaInterpolacion(arr, n, t);
                a_int  += seg(t0, clock());
            }
            fprintf(f, "%d,promedio,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f\n",
                    n, PROM(a_seq), PROM(a_bi), PROM(a_br),
                    PROM(a_brng), PROM(a_exp), PROM(a_int));
        }

        /* --- MEJOR CASO --- */
        {
            double a_seq=0, a_bi=0, a_br=0, a_brng=0, a_exp=0, a_int=0;
            for (int r = 0; r < REPETICIONES; r++) {
                /* Para Secuencial, Exponencial e Interpolación, el mejor caso O(1) es el índice 0 */
                int target_mejor_ext = arr[0].puntaje;
                /* Para Binaria, el mejor caso O(1) ocurre si acierta al medio en la primera división */
                int target_mejor_bin = arr[(n-1)/2].puntaje;
                clock_t t0;

                t0 = clock(); busquedaSecuencial(arr, n, target_mejor_ext);
                a_seq  += seg(t0, clock());

                t0 = clock(); busquedaBinariaIterativa(arr, 0, n-1, target_mejor_bin);
                a_bi   += seg(t0, clock());

                t0 = clock(); busquedaBinariaRecursiva(arr, 0, n-1, target_mejor_bin);
                a_br   += seg(t0, clock());

                t0 = clock(); busquedaBinariaRangos(arr, n, target_mejor_bin, &primero, &ultimo);
                a_brng += seg(t0, clock());

                t0 = clock(); busquedaExponencial(arr, n, target_mejor_ext);
                a_exp  += seg(t0, clock());

                t0 = clock(); busquedaInterpolacion(arr, n, target_mejor_ext);
                a_int  += seg(t0, clock());
            }
            fprintf(f, "%d,mejor,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f\n",
                    n, PROM(a_seq), PROM(a_bi), PROM(a_br),
                    PROM(a_brng), PROM(a_exp), PROM(a_int));
        }
    }
    free(arr);
    printf("  G11-G12 OK\n");
}

/* ═══════════════════════════════════════════════════════════════
 * G13 – Quick Select: mejor caso vs peor caso
 *        CSV: N, mejor, peor
 *
 *  Mejor caso: arreglo aleatorio, k = n/2 (particiones balanceadas)
 *  Peor caso : arreglo ordenado ascendente + pivote último
 *              → siempre split 0|(n-1)  →  O(n²)
 *              Se busca k=0 para forzar el recorrido máximo.
 * ═══════════════════════════════════════════════════════════════ */
void experimento_G13(FILE *f) {
    fprintf(f, "N,mejor,peor\n");

    Deportista *orig  = malloc(TAMANOS_T2[NUM_T2-1] * sizeof(Deportista));
    Deportista *copia = malloc(TAMANOS_T2[NUM_T2-1] * sizeof(Deportista));

    for (int i = 0; i < NUM_T2; i++) {
        int n = TAMANOS_T2[i];

        /* --- MEJOR CASO: aleatorio, k central --- */
        double a_mejor = 0.0;
        for (int r = 0; r < REPETICIONES; r++) {
            generarCasoPromedio(orig, n);   /* nueva permutación cada vez */
            copiar(copia, orig, n);
            clock_t t0 = clock();
            quickSelectUltimo(copia, 0, n-1, n/2);
            a_mejor += seg(t0, clock());
        }

        /* --- PEOR CASO: ordenado ascendente, k = 0, pivote último --- */
        /* quickSelect debe usar pivote último internamente para que    */
        double a_peor = 0.0;
        generarPeorCasoOrdenamiento(orig, n);   /* ordenado ascendente */
        for (int r = 0; r < REPETICIONES; r++) {
            copiar(copia, orig, n);
            clock_t t0 = clock();
            quickSelect(copia, 0, n-1, 0);      /* k=0 → siempre lado pequeño */
            a_peor += seg(t0, clock());
        }

        fprintf(f, "%d,%.6f,%.6f\n", n, PROM(a_mejor), PROM(a_peor));
    }
    free(orig); free(copia);
    printf("  G13 OK\n");
}

/* ═══════════════════════════════════════════════════════════════
 * MAIN
 * ═══════════════════════════════════════════════════════════════ */
int main(void) {
    srand((unsigned)time(NULL));

    /* Crear carpeta data/ si no existe */
    system("mkdir -p data");

    printf("=== Análisis Experimental – Tarea 2 ===\n");

    FILE *f;

    printf("[G1] Umbrales Merge Sort...\n");
    f = fopen("data/g1_merge_umbrales.csv", "w");
    experimento_G1(f);
    fclose(f);

    printf("[G2-G4] Merge clásico vs optimizado (mejor/peor/promedio)...\n");
    f = fopen("data/g2_g3_g4_merge_casos.csv", "w");
    experimento_G2_G3_G4(f);
    fclose(f);

    printf("[G5-G7] Quick Sort pivotes (mejor/peor/promedio)...\n");
    f = fopen("data/g5_g6_g7_quick_pivotes.csv", "w");
    experimento_G5_G6_G7(f);
    fclose(f);

    printf("[G8-G10] Comparación T1 vs T2 (mejor/peor/promedio)...\n");
    f = fopen("data/g8_g9_g10_t1_vs_t2.csv", "w");
    experimento_G8_G9_G10(f);
    fclose(f);

    printf("[G11-G12] Búsqueda (peor caso y caso promedio)...\n");
    f = fopen("data/g11_g12_busqueda.csv", "w");
    experimento_G11_G12(f);
    fclose(f);

    printf("[G13] Quick Select (mejor vs peor)...\n");
    f = fopen("data/g13_quickselect.csv", "w");
    experimento_G13(f);
    fclose(f);

    printf("\n¡Listo! Archivos CSV generados en data/\n");
    return 0;
}