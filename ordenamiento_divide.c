/**
 * @file ordenamiento_divide.c
 * @brief Algoritmos de ordenamiento mediante Divide y Vencerás (Merge Sort y Quick Sort).
 */
#include "ordenamiento_divide.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

/**
 * @brief Compara dos deportistas según un campo específico utilizando punteros.
 * @param a Puntero constante al primer deportista.
 * @param b Puntero constante al segundo deportista.
 * @param campo Criterio de comparación (1: ID, 2: Nombre, 3: Equipo, 4: Puntaje, 5: Competencias).
 * @return Mayor a 0 si a > b, menor a 0 si a < b, o 0 si son equivalentes.
 */
static int comparar_deportistas_divide(const Deportista *a, const Deportista *b, int campo) {
    switch(campo) {
        case 1: return a->id - b->id;
        case 2: return strcmp(a->nombre, b->nombre);
        case 3: return strcmp(a->equipo, b->equipo);
        case 4: return (a->puntaje > b->puntaje) - (a->puntaje < b->puntaje);
        case 5: return a->competencias - b->competencias;
        default: return a->id - b->id;
    }
}

/**
 * @brief Intercambia los valores de dos estructuras de tipo Deportista.
 * @param a Puntero al primer deportista.
 * @param b Puntero al segundo deportista.
 */
void swap(Deportista *a, Deportista *b) {
    Deportista temp = *a;
    *a = *b;
    *b = temp;
}

//                MERGE SORT

/**
 * @brief Combina dos subarreglos previamente ordenados en un solo arreglo ordenado.
 * @param arr Arreglo principal de deportistas.
 * @param l Índice inferior del primer subarreglo.
 * @param m Índice medio que divide los subarreglos.
 * @param r Índice superior del segundo subarreglo.
 * @param campo Criterio de ordenamiento a utilizar en la mezcla.
 */
void merge(Deportista arr[], int l, int m, int r, int campo) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Deportista *L = (Deportista *)malloc(n1 * sizeof(Deportista));
    Deportista *R = (Deportista *)malloc(n2 * sizeof(Deportista));
    
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (comparar_deportistas_divide(&L[i], &R[j], campo) <= 0) { arr[k] = L[i]; i++; } 
        else { arr[k] = R[j]; j++; }
        k++;
    }
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }
    free(L); free(R);
}

/**
 * @brief Implementación clásica de Merge Sort (Divide y Vencerás).
 * @param arr Arreglo a ordenar.
 * @param l Índice límite inferior.
 * @param r Índice límite superior.
 * @param campo Criterio de ordenamiento.
 */
void merge_sort(Deportista arr[], int l, int r, int campo) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m, campo);
        merge_sort(arr, m + 1, r, campo);
        merge(arr, l, m, r, campo);
    }
}

/**
 * @brief Variante local de Insertion Sort para ordenar un subarreglo muy pequeño (Umbral).
 * @param arr Arreglo principal.
 * @param l Índice inicial del subarreglo.
 * @param r Índice final del subarreglo.
 * @param campo Criterio de ordenamiento.
 */
void insertion_sort_subarray(Deportista arr[], int l, int r, int campo) {
    for (int i = l + 1; i <= r; i++) {
        Deportista key = arr[i];
        int j = i - 1;
        while (j >= l && comparar_deportistas_divide(&arr[j], &key, campo) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/**
 * @brief Merge Sort Optimizado: Utiliza Insertion Sort cuando el subarreglo es menor o igual a un umbral.
 * @param arr Arreglo a ordenar.
 * @param l Índice límite inferior.
 * @param r Índice límite superior.
 * @param campo Criterio de ordenamiento.
 * @param umbral Tamaño máximo de subarreglo sobre el cual se aplicará Insertion Sort.
 */
void merge_sort_optimizado(Deportista arr[], int l, int r, int campo, int umbral) {
    if (r - l + 1 <= umbral) {
        insertion_sort_subarray(arr, l, r, campo);
        return;
    }
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_optimizado(arr, l, m, campo, umbral);
        merge_sort_optimizado(arr, m + 1, r, campo, umbral);
        merge(arr, l, m, r, campo);
    }
}

/**
 * @brief Selecciona un índice como pivote dependiendo de la estrategia configurada por el usuario.
 * @param arr Arreglo principal.
 * @param low Índice más bajo.
 * @param high Índice más alto.
 * @param tipo_pivote Constante que define la estrategia (Primer, Último, Aleatorio o Mediana).
 * @param campo Criterio de comparación.
 * @return Índice seleccionado como pivote.
 */
int obtener_indice_pivote(Deportista arr[], int low, int high, int tipo_pivote, int campo) {
    switch (tipo_pivote) {
        case PIVOT_PRIMER: return low;
        case PIVOT_ALEATORIO: return low + rand() % (high - low + 1);
        case PIVOT_MEDIANA: {
            int mid = low + (high - low) / 2;
            int idx[3] = {low, mid, high};
            if (comparar_deportistas_divide(&arr[idx[0]], &arr[idx[1]], campo) > 0) swap(&arr[idx[0]], &arr[idx[1]]);
            if (comparar_deportistas_divide(&arr[idx[1]], &arr[idx[2]], campo) > 0) swap(&arr[idx[1]], &arr[idx[2]]);
            if (comparar_deportistas_divide(&arr[idx[0]], &arr[idx[1]], campo) > 0) swap(&arr[idx[0]], &arr[idx[1]]);
            return idx[1];
        }
        case PIVOT_ULTIMO: default: return high;
    }
}

/**
 * @brief Esquema de Partición de Lomuto para reorganizar el subarreglo alrededor de un pivote.
 * @param arr Arreglo a particionar.
 * @param low Índice límite inferior.
 * @param high Índice límite superior.
 * @param tipo_pivote Estrategia para elegir dinámicamente el pivote.
 * @param campo Criterio de comparación.
 * @return Índice final donde ha sido colocado el pivote.
 */
int partition_lomuto(Deportista arr[], int low, int high, int tipo_pivote, int campo) {
    int pivot_idx = obtener_indice_pivote(arr, low, high, tipo_pivote, campo);
    swap(&arr[pivot_idx], &arr[high]); // Lomuto siempre requiere el pivote al final
    
    Deportista pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (comparar_deportistas_divide(&arr[j], &pivot, campo) <= 0) { i++; swap(&arr[i], &arr[j]); }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/**
 * @brief Implementación de Quick Sort mediante el esquema de partición de Lomuto.
 * @param arr Arreglo a ordenar.
 * @param low Índice inicial.
 * @param high Índice final.
 * @param tipo_pivote Estrategia de pivote a utilizar para el particionamiento.
 * @param campo Criterio de comparación.
 */
void quick_sort_lomuto(Deportista arr[], int low, int high, int tipo_pivote, int campo) {
    if (low < high) {
        int pi = partition_lomuto(arr, low, high, tipo_pivote, campo);
        quick_sort_lomuto(arr, low, pi - 1, tipo_pivote, campo);
        quick_sort_lomuto(arr, pi + 1, high, tipo_pivote, campo);
    }
}