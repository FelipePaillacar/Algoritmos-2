/**
 * @file main.c
 * @brief Punto de entrada principal con selección de campo y validaciones mejoradas.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deportista.h"
#include "ordenamiento_divide.h"
#include "busqueda_divide.h"

/**
 * @brief Función para que el usuario elija qué atributo usar para la operación.
 */
int solicitarCampo() {
    int campo;
    printf("\nSeleccione el atributo:\n");
    printf("1. ID\n");
    printf("2. Nombre\n");
    printf("3. Equipo\n");
    printf("4. Puntaje\n");
    printf("5. Competencias\n");
    printf("Campo: ");
    if (scanf("%d", &campo) != 1 || campo < 1 || campo > 5) {
        printf("Campo no valido. Se usara 'Puntaje' por defecto.\n");
        while(getchar() != '\n'); 
        return 4; // Default: Puntaje
    }
    return campo;
}

void cargarDatosAleatorios(Deportista arr[], int n) {
    reiniciar_generador_id();
    for (int i = 0; i < n; i++) {
        arr[i] = generar_deportista();
    }
}

int main() {
    srand(time(NULL));
    int num_deportistas = 1000;
    Deportista* sistema = (Deportista*)malloc(num_deportistas * sizeof(Deportista));
    int opcion;

    if (sistema == NULL) return 1;

    do {
        // Se cargan datos al inicio o cuando se cambia la cantidad
        cargarDatosAleatorios(sistema, num_deportistas);
        
        printf("\n=== SISTEMA DE DEPORTISTAS (PROYECTO 2) ===\n");
        printf("1. Cambiar cantidad de deportistas (Actual: %d)\n", num_deportistas);
        printf("2. Ordenar datos (MergeSort Optimizado)\n");
        printf("3. Ordenar datos (QuickSort - Pivote Mediana)\n");
        printf("4. Encontrar el K-esimo deportista (QuickSelect)\n");
        printf("5. Ver Top N Ranking\n");
        printf("6. Buscar por rango de puntaje (Busqueda Binaria)\n"); // Título corregido
        printf("7. Buscar por ID (Busqueda Exponencial)\n");
        printf("8. Buscar por ID (Busqueda Interpolacion)\n");
        printf("9. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            while(getchar() != '\n');
            continue;
        }

        switch(opcion) {
            case 1: {
                int nueva_cantidad;
                printf("Ingrese la nueva cantidad: ");
                if (scanf("%d", &nueva_cantidad) == 1 && nueva_cantidad > 0) {
                    num_deportistas = nueva_cantidad;
                    sistema = (Deportista*)realloc(sistema, num_deportistas * sizeof(Deportista));
                    cargarDatosAleatorios(sistema, num_deportistas);
                    printf("Sistema actualizado a %d deportistas.\n", num_deportistas);
                }
                break;
            }
            case 2: {
                int campo = solicitarCampo();
                merge_sort_optimizado(sistema, 0, num_deportistas - 1, campo, 10);
                printf("\n--- ORDENADO (MERGE SORT OPTIMIZADO) ---\n");
                
                int ver = (num_deportistas < 15) ? num_deportistas : 15;
                // Si es Puntaje o Competencias, imprimimos de mayor a menor (de atrás hacia adelante)
                if (campo == 4 || campo == 5) {
                    for(int i = num_deportistas - 1; i >= num_deportistas - ver; i--) {
                        imprimir_deportista(sistema[i]);
                    }
                } else {
                    for(int i = 0; i < ver; i++) {
                        imprimir_deportista(sistema[i]);
                    }
                }
                break;
            }
            case 3: {
                int campo = solicitarCampo();
                quick_sort_lomuto(sistema, 0, num_deportistas - 1, PIVOT_MEDIANA, campo);
                printf("\n--- ORDENADO (QUICK SORT MEDIANA) ---\n");
                
                int ver = (num_deportistas < 15) ? num_deportistas : 15;
                // Si es Puntaje o Competencias, imprimimos de mayor a menor
                if (campo == 4 || campo == 5) {
                    for(int i = num_deportistas - 1; i >= num_deportistas - ver; i--) {
                        imprimir_deportista(sistema[i]);
                    }
                } else {
                    for(int i = 0; i < ver; i++) {
                        imprimir_deportista(sistema[i]);
                    }
                }
                break;
            }
            case 4: {
                int k;
                printf("Ingrese valor K (1 a %d): ", num_deportistas);
                if (scanf("%d", &k) == 1) {
                    if (k < 1 || k > num_deportistas) {
                        printf("Error: K debe estar entre 1 y %d.\n", num_deportistas);
                    } else {
                        int campo = solicitarCampo();
                        int k_index;
                        
                        // Si buscamos el "k-esimo mejor" en puntaje/competencias, 
                        // el 1er lugar está al final del arreglo.
                        if (campo == 4 || campo == 5) {
                            k_index = num_deportistas - k; 
                        } else {
                            k_index = k - 1;
                        }
                        
                        Deportista res = quick_select(sistema, 0, num_deportistas - 1, k_index, campo);
                        printf("\nResultado K-esimo (%d):\n", k);
                        imprimir_deportista(res);
                    }
                }
                break;
            }
            case 5: {
                int n;
                printf("Cantidad para el Top (max %d): ", num_deportistas);
                if (scanf("%d", &n) == 1) {
                    if (n < 1 || n > num_deportistas) {
                        printf("Error: Rango invalido.\n");
                    } else {
                        int campo_puntaje = 4;
                        int k_index = num_deportistas - n; 
                        
                        quick_select(sistema, 0, num_deportistas - 1, k_index, campo_puntaje);
                        quick_sort_lomuto(sistema, k_index, num_deportistas - 1, PIVOT_MEDIANA, campo_puntaje);
                        
                        printf("\n--- TOP %d DEPORTISTAS POR PUNTAJE ---\n", n);
                        // Imprimimos de mayor a menor
                        for(int i = num_deportistas - 1; i >= k_index; i--) {
                            imprimir_deportista(sistema[i]);
                        }
                    }
                }
                break;
            }
            case 6: {
                float min_pts, max_pts;
                printf("\n--- BUSQUEDA POR RANGO DE PUNTAJE ---\n");
                printf("Nota: Utilice punto (.) para los decimales (ej. 85.5)\n");
                
                printf("Ingrese puntaje minimo: ");
                if (scanf("%f", &min_pts) != 1) { 
                    while(getchar() != '\n'); 
                    break; 
                }
                
                printf("Ingrese puntaje maximo: ");
                if (scanf("%f", &max_pts) != 1) { 
                    while(getchar() != '\n'); 
                    break; 
                }

                if (min_pts > max_pts) {
                    printf("Error: El minimo no puede ser mayor al maximo.\n");
                } else {
                    merge_sort_optimizado(sistema, 0, num_deportistas - 1, 4, 10);
                    busqueda_rango_min_max(sistema, num_deportistas, min_pts, max_pts);
                }
                break;
            }
            case 7: {
                int id;
                printf("Ingrese ID: ");
                if (scanf("%d", &id) == 1) {
                    quick_sort_lomuto(sistema, 0, num_deportistas - 1, PIVOT_MEDIANA, 1);
                    int pos = busqueda_exponencial(sistema, num_deportistas, id);
                    if(pos != -1) imprimir_deportista(sistema[pos]);
                    else printf("No encontrado.\n");
                }
                break;
            }
            case 8: {
                int id;
                printf("Ingrese ID: ");
                if (scanf("%d", &id) == 1) {
                    quick_sort_lomuto(sistema, 0, num_deportistas - 1, PIVOT_MEDIANA, 1);
                    int pos = busqueda_interpolacion(sistema, num_deportistas, id);
                    if(pos != -1) imprimir_deportista(sistema[pos]);
                    else printf("No encontrado.\n");
                }
                break;
            }
        }
    } while(opcion != 9);

    free(sistema);
    return 0;
}