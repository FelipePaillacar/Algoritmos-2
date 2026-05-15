// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <string.h>
// #include "algoritmos.h"

// #define REPETICIONES 10 

// // --- GENERADORES DE DATOS ---
// void generarCasoPromedio(Deportista arr[], int n) {
//     for (int i = 0; i < n; i++) {
//         arr[i].id = i + 1;
//         sprintf(arr[i].nombre, "Dep%d", i);
//         arr[i].puntaje = rand() % 1001; 
//     }
// }

// void generarMejorCaso(Deportista arr[], int n) {
//     generarCasoPromedio(arr, n);
//     // Ordenado descendente (como piden tus algoritmos)
//     mergeSort(arr, 0, n - 1); 
// }

// void generarPeorCaso(Deportista arr[], int n) {
//     generarCasoPromedio(arr, n);
//     // Ordenado ascendente (lo opuesto al objetivo)
//     // Usamos un bubble simple para invertirlo antes del test
//     for (int i = 0; i < n - 1; i++) {
//         for (int j = 0; j < n - i - 1; j++) {
//             if (arr[j].puntaje > arr[j+1].puntaje) {
//                 Deportista tmp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = tmp;
//             }
//         }
//     }
// }

// int main() {
//     srand(time(NULL));
//     // Tamaños para algoritmos eficientes (Merge/Quick)
//     int tamanos[] = {10000, 20000, 30000, 40000, 50000};
//     // Tamaños pequeños para algoritmos O(n^2) de la Tarea 1
//     int tamanos_lentos[] = {1000, 2000, 3000, 4000, 5000};
//     int num_t = sizeof(tamanos)/sizeof(tamanos[0]);

//     // 1. Comparativa Tarea 1 vs Tarea 2
//     FILE *f_t1vst2 = fopen("data/t1_vs_t2.csv", "w");
//     // 2. Análisis de Umbrales (Merge Sort)
//     FILE *f_merge = fopen("data/mergesort_umbrales.csv", "w");
//     // 3. Análisis de Pivotes (Quick Sort)
//     FILE *f_quick = fopen("data/quicksort_pivotes.csv", "w");
//     // 4. Análisis de Búsquedas (Promedio y Peor Caso)
//     FILE *f_busqueda = fopen("data/busqueda_analisis.csv", "w");
//     // 5. Quick Select
//     FILE *f_select = fopen("data/quickselect_analisis.csv", "w");

//     fprintf(f_t1vst2, "N,Bubble,Selection,Merge,Quick\n");
//     fprintf(f_merge, "N,U1,U10,U30,U60\n");
//     fprintf(f_quick, "N,Ultimo,Primero,Aleatorio,Mediana\n");
//     fprintf(f_busqueda, "N,Binaria_Prom,Binaria_Peor,Exponencial,Interpolacion\n");
//     fprintf(f_select, "N,Promedio,Peor\n");

//     printf("Iniciando Análisis Experimental...\n");

//     for (int i = 0; i < num_t; i++) {
//         int n = tamanos[i];
//         int n_lento = tamanos_lentos[i];
//         printf("Procesando N = %d...\n", n);

//         Deportista *orig = malloc(n * sizeof(Deportista));
//         Deportista *copia = malloc(n * sizeof(Deportista));
//         Deportista *orig_lento = malloc(n_lento * sizeof(Deportista));
        
//         generarCasoPromedio(orig, n);
//         generarCasoPromedio(orig_lento, n_lento);

//         // --- T1 vs T2 ---
//         double t_bub=0, t_sel=0, t_m=0, t_q=0;
//         for(int r=0; r<REPETICIONES; r++) {
//             memcpy(copia, orig_lento, n_lento*sizeof(Deportista));
//             clock_t s = clock(); bubbleSort(copia, n_lento); t_bub += (double)(clock()-s);
            
//             memcpy(copia, orig_lento, n_lento*sizeof(Deportista));
//             s = clock(); selectionSort(copia, n_lento); t_sel += (double)(clock()-s);

//             memcpy(copia, orig_lento, n_lento*sizeof(Deportista));
//             s = clock(); mergeSort(copia, 0, n_lento-1); t_m += (double)(clock()-s);
            
//             memcpy(copia, orig_lento, n_lento*sizeof(Deportista));
//             s = clock(); quickSort(copia, 0, n_lento-1, 4); t_q += (double)(clock()-s);
//         }
//         fprintf(f_t1vst2, "%d,%f,%f,%f,%f\n", n_lento, t_bub/REPETICIONES, t_sel/REPETICIONES, t_m/REPETICIONES, t_q/REPETICIONES);

//         // --- MERGE UMBRALES ---
//         double tu1=0, tu10=0, tu30=0, tu60=0;
//         for(int r=0; r<REPETICIONES; r++) {
//             memcpy(copia, orig, n*sizeof(Deportista));
//             clock_t s = clock(); mergeSortOptimizado(copia, 0, n-1, 1); tu1 += (double)(clock()-s);
//             memcpy(copia, orig, n*sizeof(Deportista));
//             s = clock(); mergeSortOptimizado(copia, 0, n-1, 10); tu10 += (double)(clock()-s);
//             memcpy(copia, orig, n*sizeof(Deportista));
//             s = clock(); mergeSortOptimizado(copia, 0, n-1, 30); tu30 += (double)(clock()-s);
//             memcpy(copia, orig, n*sizeof(Deportista));
//             s = clock(); mergeSortOptimizado(copia, 0, n-1, 60); tu60 += (double)(clock()-s);
//         }
//         fprintf(f_merge, "%d,%f,%f,%f,%f\n", n, tu1/REPETICIONES, tu10/REPETICIONES, tu30/REPETICIONES, tu60/REPETICIONES);

//         // --- QUICK PIVOTES (En Peor Caso) ---
//         // El PDF pide ver el impacto del pivote en el rendimiento
//         generarPeorCaso(orig, n); 
//         double tp1=0, tp2=0, tp3=0, tp4=0;
//         for(int r=0; r<REPETICIONES; r++) {
//             memcpy(copia, orig, n*sizeof(Deportista));
//             clock_t s = clock(); quickSort(copia, 0, n-1, 1); tp1 += (double)(clock()-s); // Ultimo
//             memcpy(copia, orig, n*sizeof(Deportista));
//             s = clock(); quickSort(copia, 0, n-1, 2); tp2 += (double)(clock()-s); // Primero
//             memcpy(copia, orig, n*sizeof(Deportista));
//             s = clock(); quickSort(copia, 0, n-1, 3); tp3 += (double)(clock()-s); // Aleatorio
//             memcpy(copia, orig, n*sizeof(Deportista));
//             s = clock(); quickSort(copia, 0, n-1, 4); tp4 += (double)(clock()-s); // Mediana 3
//         }
//         fprintf(f_quick, "%d,%f,%f,%f,%f\n", n, tp1/REPETICIONES, tp2/REPETICIONES, tp3/REPETICIONES, tp4/REPETICIONES);

//         // --- BUSQUEDAS ---
//         mergeSort(orig, 0, n-1); // Ordenar para búsquedas
//         int target_existe = orig[n/2].puntaje;
//         int target_no_existe = 9999; // Fuera del rango 0-1000

//         clock_t s1 = clock(); busquedaBinariaRecursiva(orig, 0, n-1, target_existe);
//         clock_t s2 = clock(); busquedaBinariaRecursiva(orig, 0, n-1, target_no_existe);
//         clock_t s3 = clock(); busquedaExponencial(orig, n, target_existe);
//         clock_t s4 = clock(); busquedaInterpolacion(orig, n, target_existe);

//         fprintf(f_busqueda, "%d,%f,%f,%f,%f\n", n, (double)(s2-s1), (double)(clock()-s2), (double)(clock()-s3), (double)(clock()-s4));

//         // --- QUICK SELECT ---
//         double ts_prom=0;
//         generarCasoPromedio(orig, n);
//         clock_t ss = clock(); quickSelect(orig, 0, n-1, n/2); ts_prom = (double)(clock()-ss);
//         fprintf(f_select, "%d,%f,0.0\n", n, ts_prom);

//         free(orig); free(copia); free(orig_lento);
//     }

//     fclose(f_t1vst2); fclose(f_merge); fclose(f_quick); fclose(f_busqueda); fclose(f_select);
//     printf("¡Análisis completado! Archivos CSV listos en data/.\n");
//     return 0;
// }


/*
 * experimentos.c
 * Análisis experimental – Tarea 2 "Divide y Vencerás"
 *
 * Genera los CSV para los 13 gráficos requeridos:
 *   G1  → data/g1_merge_umbrales.csv
 *   G2-4 → data/g2_g3_g4_merge_casos.csv
 *   G5-7 → data/g5_g6_g7_quick_pivotes.csv
 *   G8-10 → data/g8_g9_g10_t1_vs_t2.csv
 *   G11-12 → data/g11_g12_busqueda.csv
 *   G13  → data/g13_quickselect.csv
 *
 * SUPUESTOS sobre algoritmos.h (ajusta los nombres si difieren):
 *   bubbleSort(arr, n)
 *   insertionSort(arr, n)
 *   selectionSort(arr, n)
 *   cocktailShakerSort(arr, n)
 *   mergeSort(arr, lo, hi)
 *   mergeSortOptimizado(arr, lo, hi, umbral)
 *   quickSort(arr, lo, hi, tipoPivote)   1=ultimo 2=primero 3=aleatorio 4=mediana3
 *   busquedaSecuencial(arr, n, target)
 *   busquedaBinariaIterativa(arr, lo, hi, target)
 *   busquedaBinariaRecursiva(arr, lo, hi, target)
 *   busquedaBinariaRangos(arr, n, target, *primero, *ultimo)
 *   busquedaExponencial(arr, n, target)
 *   busquedaInterpolacion(arr, n, target)
 *   quickSelect(arr, lo, hi, k)
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
        int target_promedio = arr[idx_random].puntaje;

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