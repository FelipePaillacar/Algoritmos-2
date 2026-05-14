#ifndef ALGORITMOS_H
#define ALGORITMOS_H

typedef struct {
    int id;
    char nombre[50];
    int edad;
    int puntaje;
} Deportista;

// --- Utilidades ---
void swap(Deportista* a, Deportista* b);
void imprimirArreglo(Deportista arr[], int n);
void imprimirDeportista(Deportista d);

// --- Algoritmos de Ordenamiento (Orden Descendente por Puntaje) ---
void insertionSort(Deportista arr[], int left, int right);

void bubbleSort(Deportista arr[], int n);
void selectionSort(Deportista arr[], int n);

// Merge Sort Clásico y Optimizado
void merge(Deportista arr[], int left, int mid, int right);
void mergeSort(Deportista arr[], int left, int right);
void mergeSortOptimizado(Deportista arr[], int left, int right, int umbral);

// Quick Sort con Esquema Lomuto y Variantes de Pivote
int particionLomuto(Deportista arr[], int low, int high, int tipoPivote);
void quickSort(Deportista arr[], int low, int high, int tipoPivote);

// --- Algoritmos de Selección ---
Deportista quickSelect(Deportista arr[], int low, int high, int k);

// --- Algoritmos de Búsqueda ---
int busquedaBinariaRecursiva(Deportista arr[], int left, int right, int target);
void busquedaBinariaRangos(Deportista arr[], int n, int target, int* inicio, int* fin);
int busquedaExponencial(Deportista arr[], int n, int target);
int busquedaInterpolacion(Deportista arr[], int n, int target);

#endif