#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "deportista.h"
#include "ordenamiento_divide.h"
#include "busqueda_divide.h"
#include "ordenamiento.h"
#include "busqueda.h"

#define MAX_DEPORTISTAS 10000 
#define CANTIDAD_GENERAR 10000
#define ARCHIVO_DATOS "data/datos.csv"

// Estado global del programa
Deportista arreglo_deportistas[MAX_DEPORTISTAS];
int cantidad_actual = 0;

// --- Declaraciones de funciones de submenús ---
void mostrar_submenu_datos();
void mostrar_submenu_ordenamiento();
void mostrar_submenu_mergesort();
void mostrar_submenu_quicksort();
void mostrar_submenu_busqueda();
void mostrar_submenu_ranking();
void mostrar_datos_memoria();
void mostrar_submenu_ordenamiento_t1();
void mostrar_submenu_busqueda_t1();
void mostrar_menu_tarea1();
void mostrar_menu_tarea2();

// --- Funciones de utilidad para la interfaz ---

// Limpia la consola (compatible con Windows y Linux/macOS)
void limpiar_pantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausa la ejecución hasta que el usuario presione Enter
void pausar_pantalla() {
    printf("\nPresione Enter para continuar...");
    // Limpia el buffer de entrada para evitar problemas con scanf
    while (getchar() != '\n');
    getchar();
}

// --- Implementación de los submenús ---

void mostrar_datos_memoria() {
    if (cantidad_actual == 0) {
        printf("\nNo hay datos cargados en memoria.\n");
    } else {
        printf("\n--- REGISTROS ACTUALES ---\n");
        int limite = (cantidad_actual > 50) ? 50 : cantidad_actual;
        for (int i = 0; i < limite; i++) {
            imprimir_deportista(arreglo_deportistas[i]);
        }
        if (cantidad_actual > 50) {
            printf("... (Mostrando 50 de %d registros) ...\n", cantidad_actual);
        }
    }
    pausar_pantalla();
}

void mostrar_submenu_datos() {
    int opcion;
    int nueva_cant;
    int cantidad_a_generar = CANTIDAD_GENERAR;
    do {
        limpiar_pantalla();
        printf("== Submenú: Gestión de Datos ==\n");
        printf("1. Cambiar cantidad de deportistas a generar (Actual: %d)\n", cantidad_a_generar);
        printf("2. Generar deportistas aleatorios (Caso Promedio)\n");
        printf("3. Generar deportistas ordenados por ID (Mejor caso)\n");
        printf("4. Generar deportistas inversamente ordenados por ID (Peor caso)\n");
        printf("5. Cargar datos desde archivo '%s'\n", ARCHIVO_DATOS);
        printf("6. Mostrar deportistas cargados en memoria\n");
        printf("7. Volver al menú principal\n");
        printf("===============================\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("\nIngrese la nueva cantidad (Máx %d): ", MAX_DEPORTISTAS);
                scanf("%d", &nueva_cant);
                if (nueva_cant > 0 && nueva_cant <= MAX_DEPORTISTAS) {
                    cantidad_a_generar = nueva_cant;
                    printf("Cantidad actualizada a %d.\n", cantidad_a_generar);
                } else {
                    printf("Cantidad inválida. Debe estar entre 1 y %d.\n", MAX_DEPORTISTAS);
                }
                pausar_pantalla();
                break;
            case 2:
                printf("\nGenerando %d deportistas aleatorios...\n", cantidad_a_generar);
                for (int i = 0; i < cantidad_a_generar; i++) {
                    arreglo_deportistas[i] = generar_deportista();
                }
                cantidad_actual = cantidad_a_generar;
                mezclar_deportistas(arreglo_deportistas, cantidad_actual);
                guardar_deportistas_csv(arreglo_deportistas, cantidad_actual, ARCHIVO_DATOS);
                printf("Datos generados, mezclados y guardados en '%s'.\n", ARCHIVO_DATOS);
                pausar_pantalla();
                break;
            case 3:
                printf("\nGenerando %d deportistas ordenados por ID...\n", cantidad_a_generar);
                generar_datos_ordenados(arreglo_deportistas, cantidad_a_generar);
                cantidad_actual = cantidad_a_generar;
                guardar_deportistas_csv(arreglo_deportistas, cantidad_actual, ARCHIVO_DATOS);
                printf("Datos generados y guardados en '%s'.\n", ARCHIVO_DATOS);
                pausar_pantalla();
                break;
            case 4:
                printf("\nGenerando %d deportistas inversamente ordenados...\n", cantidad_a_generar);
                generar_datos_inversos(arreglo_deportistas, cantidad_a_generar);
                cantidad_actual = cantidad_a_generar;
                guardar_deportistas_csv(arreglo_deportistas, cantidad_actual, ARCHIVO_DATOS);
                printf("Datos generados y guardados en '%s'.\n", ARCHIVO_DATOS);
                pausar_pantalla();
                break;
            case 5:
                printf("\nCargando datos desde el archivo CSV...\n");
                cantidad_actual = leer_deportistas_csv(arreglo_deportistas, MAX_DEPORTISTAS, ARCHIVO_DATOS);
                if (cantidad_actual > 0) {
                    printf("Se cargaron %d registros exitosamente.\n", cantidad_actual);
                } else {
                    printf("No se pudo cargar o el archivo '%s' está vacío.\n", ARCHIVO_DATOS);
                }
                pausar_pantalla();
                break;
            case 6:
                mostrar_datos_memoria();
                break;
            case 7:
                printf("\nVolviendo al menú principal...\n");
                break;
            default:
                printf("\nOpción no válida. Intente de nuevo.\n");
                pausar_pantalla();
        }
    } while (opcion != 7);
}

void mostrar_submenu_mergesort() {
    int opcion;
    do {
        limpiar_pantalla();
        printf("== Submenú: Variantes de Merge Sort ==\n");
        printf("1. Ordenar usando Merge Sort (clásico)\n");
        printf("2. Ordenar usando Merge Sort (optimizado con Insertion Sort)\n");
        printf("3. Mostrar deportistas cargados en memoria\n");
        printf("4. Volver al submenú anterior\n");
        printf("========================================\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (cantidad_actual == 0) {
                    printf("\nNo hay datos para ordenar. Por favor genere o cargue datos primero.\n");
                } else {
                    int campo;
                    printf("\nSeleccione el campo a ordenar (1:ID, 2:Nombre, 3:Equipo, 4:Puntaje, 5:Competencias): ");
                    scanf("%d", &campo);
                    printf("\nEjecutando Merge Sort clásico...\n");
                    clock_t inicio = clock();
                    merge_sort(arreglo_deportistas, 0, cantidad_actual - 1, campo);
                    clock_t fin = clock();
                    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
                    guardar_deportistas_csv(arreglo_deportistas, cantidad_actual, ARCHIVO_DATOS);
                    printf("¡Ordenamiento completado en %.6f segundos y guardado en '%s'!\n", tiempo, ARCHIVO_DATOS);
                }
                pausar_pantalla();
                break;
            case 2:
                if (cantidad_actual == 0) {
                    printf("\nNo hay datos para ordenar. Por favor genere o cargue datos primero.\n");
                } else {
                    int umbral;
                    int campo;
                    printf("\nIngrese el umbral para Insertion Sort (ej. 10, 20, 50): ");
                    if (scanf("%d", &umbral) != 1) {
                        while(getchar() != '\n'); // Limpiar buffer en caso de error
                        umbral = 15; // Valor por defecto
                    }
                    printf("Seleccione el campo a ordenar (1:ID, 2:Nombre, 3:Equipo, 4:Puntaje, 5:Competencias): ");
                    scanf("%d", &campo);
                    printf("Ejecutando Merge Sort optimizado (Umbral: %d)...\n", umbral);
                    clock_t inicio = clock();
                    merge_sort_optimizado(arreglo_deportistas, 0, cantidad_actual - 1, campo, umbral);
                    clock_t fin = clock();
                    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
                    guardar_deportistas_csv(arreglo_deportistas, cantidad_actual, ARCHIVO_DATOS);
                    printf("¡Ordenamiento completado en %.6f segundos y guardado en '%s'!\n", tiempo, ARCHIVO_DATOS);
                }
                pausar_pantalla();
                break;
            case 3:
                mostrar_datos_memoria();
                break;
            case 4:
                printf("\nVolviendo al submenú anterior...\n");
                break;
            default:
                printf("\nOpción no válida. Intente de nuevo.\n");
                pausar_pantalla();
        }
    } while (opcion != 4);
}

void mostrar_submenu_quicksort() {
    int opcion;
    do {
        limpiar_pantalla();
        printf("== Submenú: Variantes de Quick Sort (Lomuto) ==\n");
        printf("1. Quick Sort (Pivote: último elemento)\n");
        printf("2. Quick Sort (Pivote: primer elemento)\n");
        printf("3. Quick Sort (Pivote: aleatorio)\n");
        printf("4. Quick Sort (Pivote: mediana de tres)\n");
        printf("5. Mostrar deportistas cargados en memoria\n");
        printf("6. Volver al submenú anterior\n");
        printf("===============================================\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
            case 2:
            case 3:
            case 4:
                if (cantidad_actual == 0) {
                    printf("\nNo hay datos para ordenar.\n");
                } else {
                    int tipo = PIVOT_ULTIMO;
                    if (opcion == 2) tipo = PIVOT_PRIMER;
                    else if (opcion == 3) tipo = PIVOT_ALEATORIO;
                    else if (opcion == 4) tipo = PIVOT_MEDIANA;
                    
                    int campo;
                    printf("\nSeleccione el campo a ordenar (1:ID, 2:Nombre, 3:Equipo, 4:Puntaje, 5:Competencias): ");
                    scanf("%d", &campo);
                    printf("\nEjecutando Quick Sort (Lomuto)...\n");
                    clock_t inicio = clock();
                    quick_sort_lomuto(arreglo_deportistas, 0, cantidad_actual - 1, tipo, campo);
                    clock_t fin = clock();
                    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
                    guardar_deportistas_csv(arreglo_deportistas, cantidad_actual, ARCHIVO_DATOS);
                    printf("¡Ordenamiento completado en %.6f segundos y guardado en '%s'!\n", tiempo, ARCHIVO_DATOS);
                }
                pausar_pantalla();
                break;
            case 5:
                mostrar_datos_memoria();
                break;
            case 6:
                printf("\nVolviendo al submenú anterior...\n");
                break;
            default:
                printf("\nOpción no válida. Intente de nuevo.\n");
                pausar_pantalla();
        }
    } while (opcion != 6);
}

void mostrar_submenu_ordenamiento() {
    int opcion;
    do {
        limpiar_pantalla();
        printf("== Submenú: Algoritmos de Ordenamiento ==\n");
        printf("1. Algoritmos Merge Sort\n");
        printf("2. Algoritmos Quick Sort\n");
        printf("3. Mostrar deportistas cargados en memoria\n");
        printf("4. Volver al menú principal\n");
        printf("=========================================\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                mostrar_submenu_mergesort();
                break;
            case 2:
                mostrar_submenu_quicksort();
                break;
            case 3:
                mostrar_datos_memoria();
                break;
            case 4:
                printf("\nVolviendo al menú principal...\n");
                break;
            default:
                printf("\nOpción no válida. Intente de nuevo.\n");
                pausar_pantalla();
        }
    } while (opcion != 4);
}

void mostrar_submenu_busqueda() {
    int opcion;
    int id_buscar;
    int idx = -1;
    do {
        limpiar_pantalla();
        printf("== Submenú: Algoritmos de Búsqueda ==\n");
        printf("1. Mostrar deportistas en rango de puntaje (Búsqueda Binaria para rangos)\n");
        printf("2. Buscar deportista por ID (Búsqueda Binaria)\n");
        printf("3. Buscar deportista (Búsqueda Exponencial)\n");
        printf("4. Buscar deportista (Búsqueda por Interpolación)\n");
        printf("5. Mostrar deportistas cargados en memoria\n");
        printf("6. Volver al menú principal\n");
        printf("=====================================\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (cantidad_actual == 0) { printf("\nNo hay datos.\n"); break; }
                float puntaje_buscar;
                printf("\nIngrese el PUNTAJE para buscar su rango (Búsqueda Binaria para Rango): ");
                scanf("%f", &puntaje_buscar);
                printf("Ordenando arreglo previamente por PUNTAJE...\n");
                merge_sort(arreglo_deportistas, 0, cantidad_actual - 1, 4); // Campo 4 = Puntaje
                // NOTA: Asegúrate de que busqueda_binaria_rango acepte un 'float' en busqueda_divide.c
                clock_t inicio1 = clock();
                busqueda_binaria_rango(arreglo_deportistas, cantidad_actual, puntaje_buscar);
                clock_t fin1 = clock();
                printf("\nTiempo de búsqueda: %.6f segundos\n", (double)(fin1 - inicio1) / CLOCKS_PER_SEC);
                pausar_pantalla();
                break;
            case 2:
                if (cantidad_actual == 0) { printf("\nNo hay datos.\n"); break; }
                printf("\nIngrese el ID a buscar (Búsqueda Binaria Recursiva): ");
                scanf("%d", &id_buscar);
                printf("Ordenando arreglo previamente por ID...\n");
                merge_sort(arreglo_deportistas, 0, cantidad_actual - 1, 1);
                clock_t inicio2 = clock();
                idx = busqueda_binaria_recursiva(arreglo_deportistas, 0, cantidad_actual - 1, id_buscar);
                clock_t fin2 = clock();
                if (idx != -1) {
                    printf("\n¡Deportista encontrado!\n");
                    imprimir_deportista(arreglo_deportistas[idx]);
                } else {
                    printf("\nDeportista con ID %d no encontrado.\n", id_buscar);
                }
                printf("\nTiempo de búsqueda: %.6f segundos\n", (double)(fin2 - inicio2) / CLOCKS_PER_SEC);
                pausar_pantalla();
                break;
            case 3:
                if (cantidad_actual == 0) { printf("\nNo hay datos.\n"); break; }
                printf("\nIngrese el ID a buscar (Búsqueda Exponencial): ");
                scanf("%d", &id_buscar);
                printf("Ordenando arreglo previamente por ID...\n");
                merge_sort(arreglo_deportistas, 0, cantidad_actual - 1, 1);
                clock_t inicio3 = clock();
                idx = busqueda_exponencial(arreglo_deportistas, cantidad_actual, id_buscar);
                clock_t fin3 = clock();
                if (idx != -1) {
                    printf("\n¡Deportista encontrado!\n");
                    imprimir_deportista(arreglo_deportistas[idx]);
                } else {
                    printf("\nDeportista con ID %d no encontrado.\n", id_buscar);
                }
                printf("\nTiempo de búsqueda: %.6f segundos\n", (double)(fin3 - inicio3) / CLOCKS_PER_SEC);
                pausar_pantalla();
                break;
            case 4:
                if (cantidad_actual == 0) { printf("\nNo hay datos.\n"); break; }
                printf("\nIngrese el ID a buscar (Búsqueda por Interpolación): ");
                scanf("%d", &id_buscar);
                printf("Ordenando arreglo previamente por ID...\n");
                merge_sort(arreglo_deportistas, 0, cantidad_actual - 1, 1);
                clock_t inicio4 = clock();
                idx = busqueda_interpolacion(arreglo_deportistas, cantidad_actual, id_buscar);
                clock_t fin4 = clock();
                if (idx != -1) {
                    printf("\n¡Deportista encontrado!\n");
                    imprimir_deportista(arreglo_deportistas[idx]);
                } else {
                    printf("\nDeportista con ID %d no encontrado.\n", id_buscar);
                }
                printf("\nTiempo de búsqueda: %.6f segundos\n", (double)(fin4 - inicio4) / CLOCKS_PER_SEC);
                pausar_pantalla();
                break;
            case 5:
                mostrar_datos_memoria();
                break;
            case 6:
                printf("\nVolviendo al menú principal...\n");
                break;
            default:
                printf("\nOpción no válida. Intente de nuevo.\n");
                pausar_pantalla();
        }
    } while (opcion != 6);
}

void mostrar_submenu_ranking() {
    int opcion;
    do {
        limpiar_pantalla();
        printf("== Submenú: Ranking y Selección ==\n");
        printf("1. Mostrar el k-ésimo mejor deportista (Quick Select)\n");
        printf("2. Generar ranking de los N mejores deportistas\n");
        printf("3. Mostrar deportistas cargados en memoria\n");
        printf("4. Volver al menú principal\n");
        printf("==================================\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (cantidad_actual == 0) { printf("\nNo hay datos cargados.\n"); pausar_pantalla(); break; }
                int k;
                printf("\nIngrese el valor de 'k' (ej. 1 para el mejor, 2 para el segundo...): ");
                scanf("%d", &k);
                if (k > 0 && k <= cantidad_actual) {
                    printf("Calculando con Quick Select basado en PUNTAJE...\n");
                    // Si tu algoritmo ordena de menor a mayor, el "k-ésimo mejor" es el (cantidad - k)
                    int indice_k = cantidad_actual - k; 
                    clock_t inicio_qs = clock();
                    Deportista d = quick_select(arreglo_deportistas, 0, cantidad_actual - 1, indice_k, 4); // 4 = Puntaje
                    clock_t fin_qs = clock();
                    printf("\nEl %d-ésimo deportista seleccionado es:\n", k);
                    imprimir_deportista(d);
                    printf("\nTiempo de selección: %.6f segundos\n", (double)(fin_qs - inicio_qs) / CLOCKS_PER_SEC);
                } else {
                    printf("\nValor 'k' inválido.\n");
                }
                pausar_pantalla();
                break;
            case 2:
                if (cantidad_actual == 0) { printf("\nNo hay datos cargados.\n"); pausar_pantalla(); break; }
                int n_top;
                printf("\nIngrese la cantidad 'N' de deportistas para el ranking: ");
                scanf("%d", &n_top);
                if (n_top > 0 && n_top <= cantidad_actual) {
                    printf("Generando Ranking por PUNTAJE...\n");
                    clock_t inicio_r = clock();
                    merge_sort(arreglo_deportistas, 0, cantidad_actual - 1, 4); // Campo 4 = Puntaje
                    clock_t fin_r = clock();
                    printf("\n--- RANKING TOP %d ---\n", n_top);
                    // Iteramos desde el final si el ordenamiento es ascendente (de menor a mayor)
                    for(int i = cantidad_actual - 1; i >= cantidad_actual - n_top; i--) {
                        imprimir_deportista(arreglo_deportistas[i]);
                    }
                    printf("\nTiempo de ordenamiento para el Ranking: %.6f segundos\n", (double)(fin_r - inicio_r) / CLOCKS_PER_SEC);
                } else {
                    printf("\nValor 'N' inválido.\n");
                }
                pausar_pantalla();
                break;
            case 3:
                mostrar_datos_memoria();
                break;
            case 4:
                printf("\nVolviendo al menú principal...\n");
                break;
            default:
                printf("\nOpción no válida. Intente de nuevo.\n");
                pausar_pantalla();
        }
    } while (opcion != 4);
}

void mostrar_submenu_ordenamiento_t1() {
    int opcion;
    do {
        limpiar_pantalla();
        printf("== Submenú: Ordenamiento Tarea 1 ==\n");
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Selection Sort\n");
        printf("4. Cocktail Shaker Sort\n");
        printf("5. Mostrar deportistas cargados en memoria\n");
        printf("6. Volver al submenú anterior\n");
        printf("===================================\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        if (opcion >= 1 && opcion <= 4) {
            if (cantidad_actual == 0) {
                printf("\nNo hay datos para ordenar. Por favor genere o cargue datos primero.\n");
                pausar_pantalla();
                continue;
            }
            int campo;
            printf("\nSeleccione el campo a ordenar (1:ID, 2:Nombre, 3:Equipo, 4:Puntaje, 5:Competencias): ");
            scanf("%d", &campo);
            
            printf("\nEjecutando algoritmo clásico...\n");
            clock_t inicio = clock();
            if (opcion == 1) bubble_sort(arreglo_deportistas, cantidad_actual, campo);
            else if (opcion == 2) insertion_sort(arreglo_deportistas, cantidad_actual, campo);
            else if (opcion == 3) selection_sort(arreglo_deportistas, cantidad_actual, campo);
            else if (opcion == 4) cocktail_shaker_sort(arreglo_deportistas, cantidad_actual, campo);
            clock_t fin = clock();
            double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
            
            guardar_deportistas_csv(arreglo_deportistas, cantidad_actual, ARCHIVO_DATOS);
            printf("¡Ordenamiento completado en %.6f segundos y guardado en '%s'!\n", tiempo, ARCHIVO_DATOS);
            pausar_pantalla();
        } else if (opcion == 5) {
            mostrar_datos_memoria();
        } else if (opcion != 6) {
            printf("\nOpción no válida. Intente de nuevo.\n");
            pausar_pantalla();
        }
    } while (opcion != 6);
}

void mostrar_submenu_busqueda_t1() {
    int opcion;
    int id_buscar;
    int idx = -1;
    do {
        limpiar_pantalla();
        printf("== Submenú: Búsqueda Tarea 1 ==\n");
        printf("1. Buscar deportista por ID (Búsqueda Secuencial)\n");
        printf("2. Buscar deportista por ID (Búsqueda Binaria Iterativa)\n");
        printf("3. Mostrar deportistas cargados en memoria\n");
        printf("4. Volver al submenú anterior\n");
        printf("===============================\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (cantidad_actual == 0) { printf("\nNo hay datos.\n"); break; }
                printf("\nIngrese el ID a buscar (Búsqueda Secuencial): ");
                scanf("%d", &id_buscar);
                clock_t inicio1 = clock();
                idx = busqueda_secuencial(arreglo_deportistas, cantidad_actual, id_buscar);
                clock_t fin1 = clock();
                if (idx != -1) {
                    printf("\n¡Deportista encontrado!\n");
                    imprimir_deportista(arreglo_deportistas[idx]);
                } else {
                    printf("\nDeportista con ID %d no encontrado.\n", id_buscar);
                }
                printf("\nTiempo de búsqueda: %.6f segundos\n", (double)(fin1 - inicio1) / CLOCKS_PER_SEC);
                pausar_pantalla();
                break;
            case 2:
                if (cantidad_actual == 0) { printf("\nNo hay datos.\n"); break; }
                printf("\nIngrese el ID a buscar (Búsqueda Binaria Iterativa): ");
                scanf("%d", &id_buscar);
                printf("Ordenando arreglo previamente por ID con Insertion Sort...\n");
                insertion_sort(arreglo_deportistas, cantidad_actual, 1);
                clock_t inicio2 = clock();
                idx = busqueda_binaria(arreglo_deportistas, cantidad_actual, id_buscar);
                clock_t fin2 = clock();
                if (idx != -1) {
                    printf("\n¡Deportista encontrado!\n");
                    imprimir_deportista(arreglo_deportistas[idx]);
                } else {
                    printf("\nDeportista con ID %d no encontrado.\n", id_buscar);
                }
                printf("\nTiempo de búsqueda: %.6f segundos\n", (double)(fin2 - inicio2) / CLOCKS_PER_SEC);
                pausar_pantalla();
                break;
            case 3: mostrar_datos_memoria(); break;
            case 4: printf("\nVolviendo al submenú anterior...\n"); break;
            default: printf("\nOpción no válida. Intente de nuevo.\n"); pausar_pantalla();
        }
    } while (opcion != 4);
}

void mostrar_menu_tarea1() {
    int opcion;
    do {
        limpiar_pantalla();
        printf("========= Menú Tarea 1 =========\n");
        printf("1. Gestión de Datos (Generar / Cargar CSV)\n");
        printf("2. Algoritmos de Ordenamiento Clásicos\n");
        printf("3. Algoritmos de Búsqueda Clásicos\n");
        printf("4. Volver al Menú Principal\n");
        printf("================================\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: mostrar_submenu_datos(); break;
            case 2: mostrar_submenu_ordenamiento_t1(); break;
            case 3: mostrar_submenu_busqueda_t1(); break;
            case 4: printf("\nVolviendo al menú principal...\n"); break;
            default: printf("\nOpción no válida. Intente de nuevo.\n"); pausar_pantalla();
        }
    } while (opcion != 4);
}

void mostrar_menu_tarea2() {
    int opcion;
    do {
        limpiar_pantalla();
        printf("========= Menú Tarea 2 =========\n");
        printf("1. Gestión de Datos (Generar / Cargar CSV)\n");
        printf("2. Algoritmos de Ordenamiento (Divide y Vencerás)\n");
        printf("3. Algoritmos de Búsqueda\n");
        printf("4. Ranking y Selección\n");
        printf("5. Volver al Menú Principal\n");
        printf("================================\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: mostrar_submenu_datos(); break;
            case 2: mostrar_submenu_ordenamiento(); break;
            case 3: mostrar_submenu_busqueda(); break;
            case 4: mostrar_submenu_ranking(); break;
            case 5: printf("\nVolviendo al menú principal...\n"); break;
            default: printf("\nOpción no válida. Intente de nuevo.\n"); pausar_pantalla();
        }
    } while (opcion != 5);
}

void iniciar_menu() {
    // Inicializar la semilla para los números aleatorios
    srand(time(NULL));

    int opcion;
    do {
        limpiar_pantalla();
        printf("========= Menú Principal =========\n");
        printf("1. Tarea 1 (Ordenamientos Clásicos)\n");
        printf("2. Tarea 2 (Divide y Vencerás)\n");
        printf("3. Salir\n");
        printf("==================================\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                mostrar_menu_tarea1();
                break;
            case 2:
                mostrar_menu_tarea2();
                break;
            case 3:
                printf("\nSaliendo del programa. ¡Hasta luego!\n");
                break;
            default:
                printf("\nOpción no válida. Intente de nuevo.\n");
                pausar_pantalla();
        }
    } while (opcion != 3);
}