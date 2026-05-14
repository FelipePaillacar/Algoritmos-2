/**
 * @file algoritmos.h
 * @brief Definiciones y prototipos para los algoritmos de ordenamiento, búsqueda y selección.
 * 
 * Este archivo contiene las estructuras de datos principales y las firmas de las funciones
 * utilizadas en el sistema de deportistas basadas en estrategias "Divide y Vencerás".
 */

#ifndef ALGORITMOS_H
#define ALGORITMOS_H

/**
 * @struct Deportista
 * @brief Estructura que representa a un deportista dentro del sistema.
 */
typedef struct {
    int id;             /**< Identificador único del deportista */
    char nombre[50];    /**< Nombre del deportista */
    int edad;           /**< Edad del deportista */
    int puntaje;        /**< Puntaje de rendimiento (0 - 1000) */
} Deportista;

// --- Utilidades ---
/**
 * @brief Intercambia dos elementos de tipo Deportista en memoria.
 * @param a Puntero al primer deportista.
 * @param b Puntero al segundo deportista.
 */
void swap(Deportista* a, Deportista* b);

/**
 * @brief Imprime los elementos de un arreglo de deportistas.
 * @param arr Arreglo de deportistas a imprimir.
 * @param n Número de elementos a imprimir.
 */
void imprimirArreglo(Deportista arr[], int n);

/**
 * @brief Imprime la información de un solo deportista.
 * @param d Deportista a imprimir.
 */
void imprimirDeportista(Deportista d);

// --- Algoritmos de Ordenamiento (Orden Descendente por Puntaje) ---

/**
 * @brief Ordena un subarreglo usando Insertion Sort (Orden descendente).
 * @param arr Arreglo de deportistas.
 * @param left Índice izquierdo del subarreglo.
 * @param right Índice derecho del subarreglo.
 */
void insertionSort(Deportista arr[], int left, int right);

void bubbleSort(Deportista arr[], int n);
void selectionSort(Deportista arr[], int n);

// Merge Sort Clásico y Optimizado
void merge(Deportista arr[], int left, int mid, int right);

/**
 * @brief Ordena un arreglo usando el algoritmo Merge Sort clásico.
 * @param arr Arreglo de deportistas.
 * @param left Índice inicial.
 * @param right Índice final.
 */
void mergeSort(Deportista arr[], int left, int right);

/**
 * @brief Ordena un arreglo usando Merge Sort optimizado (híbrido con Insertion Sort).
 * @param arr Arreglo de deportistas.
 * @param left Índice inicial.
 * @param right Índice final.
 * @param umbral Tamaño máximo del subarreglo para cambiar a Insertion Sort.
 */
void mergeSortOptimizado(Deportista arr[], int left, int right, int umbral);

// Quick Sort con Esquema Lomuto y Variantes de Pivote
int particionLomuto(Deportista arr[], int low, int high, int tipoPivote);

/**
 * @brief Ordena un arreglo usando Quick Sort con partición de Lomuto y variante de pivote.
 * @param arr Arreglo a ordenar.
 * @param low Índice inferior.
 * @param high Índice superior.
 * @param tipoPivote Define el pivote (1=Último, 2=Primero, 3=Aleatorio, 4=Mediana de 3).
 */
void quickSort(Deportista arr[], int low, int high, int tipoPivote);

// --- Algoritmos de Selección ---
/**
 * @brief Encuentra el k-ésimo mejor deportista sin ordenar todo el arreglo.
 * @param arr Arreglo de deportistas.
 * @param low Índice inferior.
 * @param high Índice superior.
 * @param k Posición k-ésima a buscar (índice real k-1).
 * @return Deportista que ocupa la posición k.
 */
Deportista quickSelect(Deportista arr[], int low, int high, int k);

// --- Algoritmos de Búsqueda ---

int busquedaBinariaRecursiva(Deportista arr[], int left, int right, int target);

/**
 * @brief Busca los índices de inicio y fin para un puntaje repetido usando Búsqueda Binaria.
 * @param arr Arreglo ordenado descendentemente.
 * @param n Tamaño del arreglo.
 * @param target Puntaje objetivo a buscar.
 * @param inicio Puntero para retornar el índice inicial encontrado.
 * @param fin Puntero para retornar el índice final encontrado.
 */
void busquedaBinariaRangos(Deportista arr[], int n, int target, int* inicio, int* fin);

int busquedaExponencial(Deportista arr[], int n, int target);
int busquedaInterpolacion(Deportista arr[], int n, int target);

#endif