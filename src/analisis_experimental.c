#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmos.h"

void copiarArreglo(Deportista dest[], Deportista src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void generarDatosAleatorios(Deportista arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i].id = i + 1;
        sprintf(arr[i].nombre, "Deportista%d", i + 1);
        arr[i].edad = 18 + rand() % 20;
        arr[i].puntaje = rand() % 1001;
    }
}

int main() {
    srand(time(NULL));
    int tamanos[] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);

    // Archivo 1: Comparativa General para script.gp
    FILE *file_general = fopen("data/resultados.csv", "w");
    // Archivo 2: Comparativa de pivotes de QuickSort
    FILE *file_pivotes = fopen("data/quicksort_pivotes.csv", "w");
    // Archivo 3: Comparativa de umbrales de MergeSort
    FILE *file_umbrales = fopen("data/mergesort_umbrales.csv", "w");

    if (!file_general || !file_pivotes || !file_umbrales) {
        printf("Error: No se pudieron crear los CSV. Asegurate de que la carpeta 'data/' exista.\n");
        return 1;
    }

    printf("Iniciando experimentos...\n");

    for (int i = 0; i < num_tamanos; i++) {
        int n = tamanos[i];
        printf("Midiendo tiempos para N = %d...\n", n);
        
        Deportista *original = (Deportista*)malloc(n * sizeof(Deportista));
        Deportista *copia = (Deportista*)malloc(n * sizeof(Deportista));
        
        generarDatosAleatorios(original, n);
        
        double tiempos_general[5];
        clock_t start, end;

        // 1. MergeSort (Clásico)
        copiarArreglo(copia, original, n);
        start = clock(); mergeSort(copia, 0, n - 1); end = clock();
        tiempos_general[0] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

        // 2. QuickSort (Mediana 3)
        copiarArreglo(copia, original, n);
        start = clock(); quickSort(copia, 0, n - 1, 4); end = clock();
        tiempos_general[1] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

        // 3. BubbleSort
        copiarArreglo(copia, original, n);
        start = clock(); bubbleSort(copia, n); end = clock();
        tiempos_general[2] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

        // 4. SelectionSort
        copiarArreglo(copia, original, n);
        start = clock(); selectionSort(copia, n); end = clock();
        tiempos_general[3] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

        // 5. InsertionSort
        copiarArreglo(copia, original, n);
        start = clock(); insertionSort(copia, 0, n - 1); end = clock();
        tiempos_general[4] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

        fprintf(file_general, "%d,%f,%f,%f,%f,%f\n", n, 
                tiempos_general[0], tiempos_general[1], tiempos_general[2], tiempos_general[3], tiempos_general[4]);

        // --- Análisis de QuickSort (Pivotes 1, 2, 3 y 4) ---
        double t_qs[4];
        for (int p = 1; p <= 4; p++) {
            copiarArreglo(copia, original, n);
            start = clock(); quickSort(copia, 0, n - 1, p); end = clock();
            t_qs[p-1] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
        }
        fprintf(file_pivotes, "%d,%f,%f,%f,%f\n", n, t_qs[0], t_qs[1], t_qs[2], t_qs[3]);

        // --- Análisis de MergeSort (Umbrales 1, 10 y 50) ---
        double t_ms[3];
        int umbrales[] = {1, 10, 50};
        for (int u = 0; u < 3; u++) {
            copiarArreglo(copia, original, n);
            start = clock(); mergeSortOptimizado(copia, 0, n - 1, umbrales[u]); end = clock();
            t_ms[u] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
        }
        fprintf(file_umbrales, "%d,%f,%f,%f\n", n, t_ms[0], t_ms[1], t_ms[2]);

        free(original);
        free(copia);
    }

    fclose(file_general);
    fclose(file_pivotes);
    fclose(file_umbrales);

    printf("¡Finalizado! Resultados guardados exitosamente en la carpeta 'data/'.\n");
    return 0;
}