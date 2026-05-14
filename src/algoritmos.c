#include <stdio.h>
#include <stdlib.h>
#include "algoritmos.h"

void swap(Deportista* a, Deportista* b) {
    Deportista temp = *a;
    *a = *b;
    *b = temp;
}

void imprimirDeportista(Deportista d) {
    printf("ID: %d | Nombre: %-15s | Edad: %d | Puntaje: %d\n", d.id, d.nombre, d.edad, d.puntaje);
}

void imprimirArreglo(Deportista arr[], int n) {
    for (int i = 0; i < n; i++) {
        imprimirDeportista(arr[i]);
    }
}

// --- INSERTION SORT (Para optimizar MergeSort) ---
void insertionSort(Deportista arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        Deportista key = arr[i];
        int j = i - 1;
        // Orden descendente
        while (j >= left && arr[j].puntaje < key.puntaje) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// --- BUBBLE SORT Y SELECTION SORT (Para comparar con Tarea 1) ---
void bubbleSort(Deportista arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].puntaje < arr[j+1].puntaje) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void selectionSort(Deportista arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].puntaje > arr[max_idx].puntaje) {
                max_idx = j;
            }
        }
        swap(&arr[max_idx], &arr[i]);
    }
}

// --- MERGE SORT ---
void merge(Deportista arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    Deportista* L = (Deportista*)malloc(n1 * sizeof(Deportista));
    Deportista* R = (Deportista*)malloc(n2 * sizeof(Deportista));
    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].puntaje >= R[j].puntaje) { 
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    free(L);
    free(R);
}

void mergeSort(Deportista arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSortOptimizado(Deportista arr[], int left, int right, int umbral) {
    if (left < right) {
        if (right - left + 1 <= umbral) {
            insertionSort(arr, left, right);
        } else {
            int mid = left + (right - left) / 2;
            mergeSortOptimizado(arr, left, mid, umbral);
            mergeSortOptimizado(arr, mid + 1, right, umbral);
            merge(arr, left, mid, right);
        }
    }
}

// --- QUICK SORT ---
int particionLomuto(Deportista arr[], int low, int high, int tipoPivote) {
    int pIndex = high; 
    if (tipoPivote == 2) pIndex = low;
    else if (tipoPivote == 3) pIndex = low + rand() % (high - low + 1);
    else if (tipoPivote == 4) {
        int mid = low + (high - low) / 2;
        if ((arr[low].puntaje > arr[mid].puntaje) ^ (arr[low].puntaje > arr[high].puntaje)) pIndex = low;
        else if ((arr[mid].puntaje < arr[low].puntaje) ^ (arr[mid].puntaje < arr[high].puntaje)) pIndex = mid;
        else pIndex = high;
    }
    
    swap(&arr[pIndex], &arr[high]);
    int pivot = arr[high].puntaje;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j].puntaje >= pivot) { // Descendente
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(Deportista arr[], int low, int high, int tipoPivote) {
    if (low < high) {
        int pi = particionLomuto(arr, low, high, tipoPivote);
        quickSort(arr, low, pi - 1, tipoPivote);
        quickSort(arr, pi + 1, high, tipoPivote);
    }
}

// --- QUICK SELECT ---
Deportista quickSelect(Deportista arr[], int low, int high, int k) {
    if (low == high) return arr[low];
    
    int pi = particionLomuto(arr, low, high, 3); // Pivote aleatorio por defecto
    
    if (k == pi) return arr[pi];
    else if (k < pi) return quickSelect(arr, low, pi - 1, k);
    else return quickSelect(arr, pi + 1, high, k);
}

// --- BÚSQUEDAS (Asumiendo arreglo ordenado de mayor a menor) ---
int busquedaBinariaRecursiva(Deportista arr[], int left, int right, int target) {
    if (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].puntaje == target) return mid;
        // Como es descendente, si el target es mayor, está a la izquierda
        if (arr[mid].puntaje < target) return busquedaBinariaRecursiva(arr, left, mid - 1, target);
        return busquedaBinariaRecursiva(arr, mid + 1, right, target);
    }
    return -1;
}

void busquedaBinariaRangos(Deportista arr[], int n, int target, int* inicio, int* fin) {
    *inicio = -1; *fin = -1;
    int low = 0, high = n - 1;
    
    // Encontrar primera aparición
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid].puntaje == target) {
            *inicio = mid;
            high = mid - 1; // Seguir buscando hacia la izquierda
        } else if (arr[mid].puntaje < target) high = mid - 1;
        else low = mid + 1;
    }
    
    // Encontrar última aparición
    low = 0; high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid].puntaje == target) {
            *fin = mid;
            low = mid + 1; // Seguir buscando hacia la derecha
        } else if (arr[mid].puntaje < target) high = mid - 1;
        else low = mid + 1;
    }
}

int busquedaExponencial(Deportista arr[], int n, int target) {
    if (n == 0) return -1;
    if (arr[0].puntaje == target) return 0;
    
    int i = 1;
    // Recordar: Arreglo está descendente, así que la condición es al revés
    while (i < n && arr[i].puntaje >= target) {
        i *= 2;
    }
    
    int right = (i < n) ? i : n - 1;
    int left = i / 2;
    return busquedaBinariaRecursiva(arr, left, right, target);
}

int busquedaInterpolacion(Deportista arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high && target <= arr[low].puntaje && target >= arr[high].puntaje) {
        if (low == high) {
            if (arr[low].puntaje == target) return low;
            return -1;
        }
        double prop = (double)(arr[low].puntaje - target) / (arr[low].puntaje - arr[high].puntaje);
        int pos = low + prop * (high - low);

        if (arr[pos].puntaje == target) return pos;
        if (arr[pos].puntaje < target) high = pos - 1; // Descendente: target es mayor, buscar izquierda
        else low = pos + 1; // Descendente: target es menor, buscar derecha
    }
    return -1;
}