#include <stdio.h>
#include <stdlib.h>

// --- INCLUDES DE TU PROYECTO ---
#include "deportista.h"
#include "datos.h" // Para generar_deportistas, cargar_datos, etc.
#include "merge_sort.h"
#include "quick_sort.h"
// #include "busqueda.h" // Agrega aquí tus otros headers
// #include "seleccion.h"

// --- PROTOTIPOS DE FUNCIONES DE MENÚ ---
void mostrar_menu_principal();
void menu_generacion_datos(Deportista** deportistas_ptr, int* n_ptr);
void menu_ordenamiento(Deportista* deportistas, int n);
void menu_busqueda(Deportista* deportistas, int n);
void menu_seleccion_kesimo(Deportista* deportistas, int n);
void submenu_merge_sort(Deportista* deportistas, int n);
void submenu_quick_sort(Deportista* deportistas, int n);

/*
   Aquí deberías tener los prototipos de tus implementaciones.
   Ejemplo:
   void ejecutar_mergesort_clasico(Deportista arr[], int n, int campo);
   void ejecutar_quicksort(Deportista arr[], int n, int campo, int tipo_pivote);
   void ejecutar_busqueda_binaria(Deportista arr[], int n, int id_buscar);
   void ejecutar_quickselect(Deportista arr[], int n, int k);
*/

int main() {
    int opcion;
    Deportista* deportistas = NULL;
    int n = 0;

    do {
        // system("clear || cls"); // Limpia la consola en Linux/Mac o Windows
        mostrar_menu_principal();

        if (scanf("%d", &opcion) != 1) {
            printf("Error: Entrada no válida. Debe ingresar un número.\n");
            while (getchar() != '\n'); // Limpiar buffer de entrada
            opcion = 0; // Resetear opción
        }

        switch (opcion) {
            case 1:
                menu_generacion_datos(&deportistas, &n);
                break;
            case 2:
                printf("Funcionalidad: Cargar datos desde archivo...\n");
                // Aquí llamarías a tu función para cargar datos
                // cargar_datos(&deportistas, &n, "ruta/al/archivo.csv");
                break;
            case 3:
                if (deportistas != NULL && n > 0) {
                    printf("Mostrando %d registros...\n", n);
                    imprimirDeportistas(deportistas, n);
                } else {
                    printf("No hay datos para mostrar. Use la opción 1 o 2 para cargar datos.\n");
                }
                break;
            case 4:
                menu_ordenamiento(deportistas, n);
                break;
            case 5:
                menu_busqueda(deportistas, n);
                break;
            case 6:
                menu_seleccion_kesimo(deportistas, n);
                break;
            case 7:
                printf("Saliendo del programa. ¡Éxito en la tarea!\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
                break;
        }

        if (opcion != 7) {
            printf("\nPresione Enter para continuar...");
            while (getchar() != '\n');
            getchar();
        }

    } while (opcion != 7);

    // Liberar memoria si fue alocada
    if (deportistas != NULL) {
        free(deportistas);
    }
    return 0;
}

void mostrar_menu_principal() {
    printf("\n=============== ANALISIS DE ALGORITMOS ===============\n");
    printf("1. Generar datos (Mejor/Peor/Promedio Caso)\n");
    printf("2. Cargar datos desde archivo\n");
    printf("3. Mostrar registros actuales\n");
    printf("4. Algoritmos de Ordenamiento\n");
    printf("5. Algoritmos de Búsqueda\n");
    printf("6. Algoritmo de Selección (Quick Select)\n");
    printf("7. Salir\n");
    printf("======================================================\n");
    printf("Seleccione una opción: ");
}

void menu_generacion_datos(Deportista** deportistas_ptr, int* n_ptr) {
    int cantidad;
    int opcion_gen;

    printf("\n--- GENERACION DE DATOS PARA ANALISIS ---\n");
    printf("Ingrese la cantidad de deportistas a generar: ");
    if (scanf("%d", &cantidad) != 1 || cantidad <= 0) {
        printf("Error: Cantidad no válida.\n");
        while (getchar() != '\n'); // Limpiar buffer
        return;
    }

    printf("1. Generar datos aleatorios (Caso Promedio)\n");
    printf("2. Generar datos ordenados por ID (Mejor Caso para algunos alg.)\n");
    printf("3. Generar datos inversamente ordenados por ID (Peor Caso para algunos alg.)\n");
    printf("Seleccione tipo de generación: ");
    if (scanf("%d", &opcion_gen) != 1 || opcion_gen < 1 || opcion_gen > 3) {
        printf("Error: Opción de generación no válida.\n");
        while (getchar() != '\n'); // Limpiar buffer
        return;
    }

    // Liberar memoria anterior si existe
    if (*deportistas_ptr != NULL) {
        free(*deportistas_ptr);
    }

    *deportistas_ptr = malloc(cantidad * sizeof(Deportista));
    if (*deportistas_ptr == NULL) {
        printf("Error fatal: No se pudo asignar memoria para los deportistas.\n");
        *n_ptr = 0;
        return;
    }

    *n_ptr = cantidad;

    // Asumimos que generar_deportistas fue adaptada para recibir el tipo de generación
    generar_deportistas(*deportistas_ptr, *n_ptr, opcion_gen);
    printf("\nSe generaron y cargaron en memoria %d registros de deportistas.\n", *n_ptr);

    // Guardar en CSV para verificación
    guardar_csv(*deportistas_ptr, *n_ptr, "db/deportistas_generados.csv");
    printf("Los datos también fueron guardados en 'db/deportistas_generados.csv'.\n");
}

void menu_ordenamiento(Deportista* deportistas, int n) {
    if (deportistas == NULL || n == 0) {
        printf("No hay datos cargados para ordenar. Use la opción 1 o 2 del menú principal.\n");
        return;
    }
    int opcion;
    printf("\n--- ALGORITMOS DE ORDENAMIENTO ---\n");
    printf("1. Merge Sort\n");
    printf("2. Quick Sort\n");
    printf("3. Volver al menú principal\n");
    printf("Seleccione una opción: ");
    if (scanf("%d", &opcion) != 1) {
        opcion = 0; // Invalida la opción si la entrada no es un número
        while (getchar() != '\n'); // Limpia el buffer
    }

    switch (opcion) {
        case 1:
            submenu_merge_sort(deportistas, n);
            break;
        case 2:
            submenu_quick_sort(deportistas, n);
            break;
        case 3:
            break;
        default:
            printf("Opción no válida.\n");
    }
}

void submenu_merge_sort(Deportista* deportistas, int n) {
    (void)deportistas; // Parámetro sin usar por ahora
    (void)n;           // Parámetro sin usar por ahora
    int opcion;

    printf("\n--- VARIANTES DE MERGE SORT ---\n");
    printf("1. Versión Clásica\n");
    printf("2. Versión Optimizada (con umbral para Insertion Sort)\n");
    printf("Seleccione una variante: ");
    if (scanf("%d", &opcion) != 1) {
        opcion = 0;
        while (getchar() != '\n');
    }

    if (opcion == 1) {
        printf("Ejecutando Merge Sort Clásico...\n");
        // Aquí se podría crear una copia para no alterar el original, o informar al usuario.
        // Deportista* copia = malloc(n * sizeof(Deportista));
        // memcpy(copia, deportistas, n * sizeof(Deportista));
        // mergeSort(copia, 0, n - 1, campo_a_ordenar);
        // printf("Datos ordenados. Puede verlos con la opción 3 del menú principal.\n");
        // free(copia);
    } else if (opcion == 2) {
        printf("Ejecutando Merge Sort Optimizado...\n");
        // Aquí pides el umbral y llamas a tu función optimizada
        // int umbral; ... scanf ...
        // mergeSortOptimizado(copia, 0, n - 1, umbral, campo_a_ordenar);
    } else {
        printf("Opción no válida.\n");
    }
    // free(copia);
}

void submenu_quick_sort(Deportista* deportistas, int n) {
    (void)deportistas; // Parámetro sin usar por ahora
    (void)n;           // Parámetro sin usar por ahora
    int opcion;
    printf("\n--- VARIANTES DE QUICK SORT (SELECCION DE PIVOTE) ---\n");
    printf("1. Usar último elemento como pivote\n");
    printf("2. Usar primer elemento como pivote\n");
    printf("3. Usar un elemento aleatorio como pivote\n");
    printf("4. Usar la mediana de tres como pivote\n");
    printf("Seleccione una variante: ");
    if (scanf("%d", &opcion) != 1) {
        opcion = 0;
        while (getchar() != '\n');
    }

    if (opcion >= 1 && opcion <= 4) {
        printf("Ejecutando Quick Sort con pivote tipo %d...\n", opcion);
        // Aquí llamas a tu función de Quick Sort pasándole la opción del pivote
        // quickSort(deportistas, 0, n - 1, campo_a_ordenar, opcion);
        // printf("Datos ordenados. Puede verlos con la opción 3 del menú principal.\n");
    } else {
        printf("Opción no válida.\n");
    }
}

void menu_busqueda(Deportista* deportistas, int n) {
    if (deportistas == NULL || n == 0) {
        printf("No hay datos cargados para buscar. Use la opción 1 o 2 del menú principal.\n");
        return;
    }
    printf("\n--- ALGORITMOS DE BUSQUEDA ---\n");
    printf("IMPORTANTE: Los datos deben estar previamente ordenados.\n");
    printf("1. Búsqueda Binaria (recursiva)\n");
    printf("2. Búsqueda Binaria para Rangos\n");
    printf("3. Búsqueda Exponencial\n");
    printf("4. Búsqueda por Interpolación\n");
    printf("Seleccione un algoritmo: ");
    int opcion;
    if (scanf("%d", &opcion) != 1) {
        opcion = 0;
        while (getchar() != '\n');
    }
    printf("Ejecutando algoritmo de búsqueda %d...\n", opcion);
}

void menu_seleccion_kesimo(Deportista* deportistas, int n) {
    if (deportistas == NULL || n == 0) {
        printf("No hay datos cargados. Use la opción 1 o 2 del menú principal.\n");
        return;
    }
    printf("\n--- BUSQUEDA DEL K-ESIMO ELEMENTO (QUICK SELECT) ---\n");
    printf("Ingrese el valor de 'k': ");
    int k;
    if (scanf("%d", &k) != 1) {
        k = 0; // Valor inválido
        while (getchar() != '\n');
    }
    printf("Ejecutando Quick Select para encontrar el %d-ésimo elemento...\n", k);
    // quickSelect(deportistas, 0, n-1, k);
}