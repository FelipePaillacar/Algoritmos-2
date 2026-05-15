/**
 * @file main.c
 * @brief Punto de entrada principal para el menú de prueba de todo el sistema.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmos.h"

/**
 * @brief Inicializa un arreglo de deportistas con datos pseudoaleatorios.
 * @param arr Arreglo de deportistas a inicializar.
 * @param n Cantidad de elementos a generar internamente.
 */
void generarDatosSistema(Deportista arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i].id = i + 1;
        sprintf(arr[i].nombre, "Deportista%d", i + 1);
        arr[i].edad = 18 + rand() % 20;
        arr[i].puntaje = rand() % 1001;
    }
}

/**
 * @brief Función principal que lanza el sistema interactivo de comprobación algorítmica.
 * @return Estado en que ha finalizado el loop.
 */
int main() {
    srand(time(NULL));
    int num_deportistas = 1000;
    Deportista* sistema = (Deportista*)malloc(num_deportistas * sizeof(Deportista));
    int opcion;

    do {
        generarDatosSistema(sistema, num_deportistas); // Recargamos los miles de datos
        
        printf("\n=== SISTEMA DE DEPORTISTAS (PROYECTO 2) ===\n");
        printf("1. Cambiar cantidad de deportistas (Actual: %d)\n", num_deportistas);
        printf("2. Ordenar datos por puntaje (MergeSort)\n");
        printf("3. Ordenar datos por puntaje (QuickSort - Pivote Mediana 3)\n");
        printf("4. Encontrar el K-esimo mejor deportista (QuickSelect)\n");
        printf("5. Top N mejores deportistas\n");
        printf("6. Buscar deportistas por puntaje exacto (Rango Binario)\n");
        printf("7. Buscar puntaje exacto (Busqueda Exponencial)\n");
        printf("8. Buscar puntaje exacto (Busqueda Interpolacion)\n");
        printf("9. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: {
                int nueva_cantidad;
                printf("Ingrese la nueva cantidad de deportistas: ");
                scanf("%d", &nueva_cantidad);
                if (nueva_cantidad > 0) {
                    num_deportistas = nueva_cantidad;
                    free(sistema);
                    sistema = (Deportista*)malloc(num_deportistas * sizeof(Deportista));
                    printf("Cantidad de deportistas actualizada a %d.\n", num_deportistas);
                } else {
                    printf("Cantidad invalida.\n");
                }
                break;
            }
            case 2: {
                printf("\n--- Ordenando con MergeSort Optimizado ---\n");
                clock_t start = clock();
                mergeSortOptimizado(sistema, 0, num_deportistas - 1, 3); // Umbral de 3
                clock_t end = clock();
                printf("Mostrando el Top 15 para visualizar...\n");
                imprimirArreglo(sistema, num_deportistas < 15 ? num_deportistas : 15);
                printf("\nTiempo de ejecucion (MergeSort): %.3f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);
                break;
            }
                
            case 3: {
                printf("\n--- Ordenando con QuickSort (Pivote: Mediana de 3) ---\n");
                clock_t start = clock();
                quickSort(sistema, 0, num_deportistas - 1, 4);
                clock_t end = clock();
                printf("Mostrando el Top 15 para visualizar...\n");
                imprimirArreglo(sistema, num_deportistas < 15 ? num_deportistas : 15);
                printf("\nTiempo de ejecucion (QuickSort): %.3f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);
                break;
            }
                
            case 4: {
                int k;
                printf("Ingrese el valor de K (1 para el mejor, 2 para el segundo, etc): ");
                scanf("%d", &k);
                if(k > 0 && k <= num_deportistas) {
                    clock_t start = clock();
                    Deportista k_esimo = quickSelect(sistema, 0, num_deportistas - 1, k - 1);
                    clock_t end = clock();
                    printf("\nEl %d-esimo mejor deportista es:\n", k);
                    imprimirDeportista(k_esimo);
                    printf("\nTiempo de ejecucion (QuickSelect): %.3f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);
                } else {
                    printf("K invalido.\n");
                }
                break;
            }
            case 5: {
                int n;
                printf("Ingrese la cantidad (N) para el Top Ranking: ");
                scanf("%d", &n);
                if(n > 0 && n <= num_deportistas) {
                    clock_t start = clock();
                    quickSort(sistema, 0, num_deportistas - 1, 3);
                    clock_t end = clock();
                    printf("\n--- TOP %d DEPORTISTAS ---\n", n);
                    imprimirArreglo(sistema, n);
                    printf("\nTiempo de ejecucion (Ordenamiento): %.3f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);
                }
                break;
            }
            case 6: {
                int pts, inicio, fin;
                mergeSort(sistema, 0, num_deportistas - 1);
                
                printf("Arreglo actual ordenado por puntaje:\n");
                imprimirArreglo(sistema, num_deportistas < 5 ? num_deportistas : 5);
                
                printf("\nIngrese el puntaje exacto a buscar: ");
                scanf("%d", &pts);
                
                clock_t start = clock();
                busquedaBinariaRangos(sistema, num_deportistas, pts, &inicio, &fin);
                clock_t end = clock();

                if(inicio != -1) {
                    printf("\nDeportistas encontrados con %d puntos (Indices %d a %d):\n", pts, inicio, fin);
                    for(int i = inicio; i <= fin; i++) {
                        imprimirDeportista(sistema[i]);
                    }
                } else {
                    printf("No se encontraron deportistas con ese puntaje.\n");
                }
                printf("\nTiempo de ejecucion (Busqueda Binaria Rangos): %.5f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);
                break;
            }
            case 7: {
                int pts;
                mergeSort(sistema, 0, num_deportistas - 1);
                printf("\nIngrese el puntaje a buscar: ");
                scanf("%d", &pts);

                clock_t start = clock();
                int pos = busquedaExponencial(sistema, num_deportistas, pts);
                clock_t end = clock();

                if(pos != -1) {
                    printf("\nEncontrado mediante Busqueda Exponencial:\n");
                    imprimirDeportista(sistema[pos]);
                } else {
                    printf("\nNo se encontro el puntaje.\n");
                }
                printf("\nTiempo de ejecucion (Busqueda Exponencial): %.5f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);
                break;
            }
            case 8: {
                int pts;
                mergeSort(sistema, 0, num_deportistas - 1);
                printf("\nIngrese el puntaje a buscar: ");
                scanf("%d", &pts);
                
                clock_t start = clock();
                int pos = busquedaInterpolacion(sistema, num_deportistas, pts);
                clock_t end = clock();
                
                if(pos != -1) {
                    printf("\nEncontrado mediante Busqueda de Interpolacion:\n");
                    imprimirDeportista(sistema[pos]);
                } else {
                    printf("\nNo se encontro el puntaje.\n");
                }
                printf("\nTiempo de ejecucion (Busqueda Interpolacion): %.5f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);
                break;
            }
            case 9:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while(opcion != 9);

    free(sistema);
    return 0;
}