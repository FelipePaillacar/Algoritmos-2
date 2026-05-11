#include <stdlib.h>
#include "merge_sort.h"

void merge(Deportista arr[], int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    Deportista *L = malloc(n1 * sizeof(Deportista));
    Deportista *R = malloc(n2 * sizeof(Deportista));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        // Ordenando de mayor a menor por puntaje
        if (L[i].puntaje >= R[j].puntaje) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// MERGE SORT CLASICO
void mergeSort(Deportista arr[], int left, int right) {

    if (left < right) {

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// INSERTION SORT (Para subarreglos pequeños)
void insertionSort(Deportista arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        Deportista key = arr[i];
        int j = i - 1;

        // Cambiar '<' a '>' si en el futuro quieres ordenar de menor a mayor
        // Por ahora, ordena de mayor a menor (puntaje) para ser consistente con tu merge
        while (j >= left && arr[j].puntaje < key.puntaje) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// MERGE SORT OPTIMIZADO
void mergeSortOptimizado(Deportista arr[], int left, int right, int umbral) {
    // Si el tamaño del subarreglo es menor o igual al umbral, usamos Insertion Sort
    if (right - left + 1 <= umbral) {
        insertionSort(arr, left, right);
    } else {
        // Si es más grande que el umbral, seguimos dividiendo (Merge Sort clásico)
        int mid = left + (right - left) / 2;

        mergeSortOptimizado(arr, left, mid, umbral);
        mergeSortOptimizado(arr, mid + 1, right, umbral);

        merge(arr, left, mid, right);
    }
}