/**
 * @file algoritmos.c
 * @brief Implementación de algoritmos de ordenamiento y búsqueda para el sistema de deportistas.
 */
#include <stdio.h>
#include <stdlib.h>
#include "algoritmos.h"

/**
 * @brief Intercambia el contenido de dos punteros de Deportistas.
 * @param a Puntero al primer deportista.
 * @param b Puntero al segundo deportista.
 */
void swap(Deportista* a, Deportista* b) {
    Deportista temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Imprime los detalles individuales de un deportista.
 * @param d Estructura de tipo Deportista a mostrar.
 */
void imprimirDeportista(Deportista d) {
    printf("ID: %d | Nombre: %-15s | Edad: %d | Puntaje: %d\n", d.id, d.nombre, d.edad, d.puntaje);
}

/**
 * @brief Imprime un arreglo completo de deportistas.
 * @param arr Arreglo de deportistas a imprimir.
 * @param n Cantidad de elementos a mostrar.
 */
void imprimirArreglo(Deportista arr[], int n) {
    for (int i = 0; i < n; i++) {
        imprimirDeportista(arr[i]);
    }
}

/**
 * @brief Ordenamiento de Burbuja optimizado (con validación de arreglo ya ordenado).
 * @param arr Arreglo de deportistas.
 * @param n Tamaño del arreglo.
 */
void bubbleSort(Deportista arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;                          /* <-- flag nuevo */
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].puntaje < arr[j+1].puntaje) {
                swap(&arr[j], &arr[j+1]);
                swapped = 1;
            }
        }
        if (!swapped) break;  /* arreglo ya ordenado → salir antes */
    }
}

/**
 * @brief Ordenamiento por Selección con minimización de swaps redundantes.
 * @param arr Arreglo de deportistas.
 * @param n Tamaño del arreglo.
 */
void selectionSort(Deportista arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].puntaje > arr[max_idx].puntaje)
                max_idx = j;
        }
        if (max_idx != i)          /* <-- optimización: no swapear si ya está */
            swap(&arr[max_idx], &arr[i]);
    }
}

/**
 * @brief Variante bidireccional del Bubble Sort (Cocktail Shaker Sort).
 * @param arr Arreglo de deportistas.
 * @param n Tamaño del arreglo.
 */
void cocktailShakerSort(Deportista arr[], int n) {
    int inicio = 0, fin = n - 1;
    int swapped = 1;
 
    while (swapped) {
        swapped = 0;
 
        /* Pasada izquierda → derecha: burbujea el mínimo hacia el final */
        for (int i = inicio; i < fin; i++) {
            if (arr[i].puntaje < arr[i+1].puntaje) {
                swap(&arr[i], &arr[i+1]);
                swapped = 1;
            }
        }
        if (!swapped) break;
        fin--;
 
        swapped = 0;
        /* Pasada derecha → izquierda: burbujea el máximo hacia el inicio */
        for (int i = fin; i > inicio; i--) {
            if (arr[i].puntaje > arr[i-1].puntaje) {
                swap(&arr[i], &arr[i-1]);
                swapped = 1;
            }
        }
        inicio++;
    }
}

/**
 * @brief Ordenamiento por inserción interno (usado como sub-rutina de optimización para Merge Sort).
 * @param arr Arreglo de deportistas.
 * @param left Índice inferior del subarreglo.
 * @param right Índice superior del subarreglo.
 */
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

/**
 * @brief Wrapper de invocación para Insertion Sort desde algoritmos standalone.
 * @param arr Arreglo de deportistas.
 * @param n Tamaño del arreglo.
 */
void insertionSortN(Deportista arr[], int n) {
    insertionSort(arr, 0, n - 1);
}

/**
 * @brief Búsqueda Lineal/Secuencial iterativa. O(n) garantizado.
 * @param arr Arreglo de deportistas.
 * @param n Tamaño del arreglo.
 * @param target Puntaje buscado.
 * @return Índice donde fue encontrado o -1 si no existe.
 */
int busquedaSecuencial(Deportista arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i].puntaje == target) return i;
    }
    return -1;
}

/**
 * @brief Búsqueda Binaria de forma Iterativa para elementos en arreglo ordenado.
 * @param arr Arreglo de deportistas ordenado.
 * @param lo Límite inferior.
 * @param hi Límite superior.
 * @param target Puntaje buscado.
 * @return Índice donde fue encontrado o -1 si no existe.
 */
int busquedaBinariaIterativa(Deportista arr[], int lo, int hi, int target) {
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid].puntaje == target) return mid;
        /* descendente: si mid es menor que target, target está a la izquierda */
        if (arr[mid].puntaje < target) hi = mid - 1;
        else                           lo = mid + 1;
    }
    return -1;
}

/**
 * @brief Fusiona subarreglos ordenados previamente separados de Merge Sort.
 * @param arr Arreglo de deportistas principal.
 * @param left Límite de inicio.
 * @param mid Posición de división (centro).
 * @param right Límite superior.
 */
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

/**
 * @brief Ordenamiento por mezcla clásico (Merge Sort).
 * @param arr Arreglo a ordenar.
 * @param left Límite inferior.
 * @param right Límite superior.
 */
void mergeSort(Deportista arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

/**
 * @brief Merge Sort Optimizado con Insertion Sort para subarreglos del tamaño del umbral especificado.
 * @param arr Arreglo a ordenar.
 * @param left Límite inferior.
 * @param right Límite superior.
 * @param umbral Tamaño máximo en que se activa insertionSort.
 */
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

/**
 * @brief Esquema de partición Lomuto para Quick Sort, adaptable por tipos de pivotes.
 * @param arr Arreglo a particionar.
 * @param low Índice bajo.
 * @param high Índice alto.
 * @param tipoPivote Define el índice a usar como pivote.
 * @return Índice final donde fue consolidado el pivote elegido.
 */
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

/**
 * @brief Ordenamiento Quick Sort con esquema de particionamiento personalizable.
 * @param arr Arreglo a ordenar.
 * @param low Límite inferior de indexación.
 * @param high Límite superior de indexación.
 * @param tipoPivote Bandera de comportamiento del pivote.
 */
void quickSort(Deportista arr[], int low, int high, int tipoPivote) {
    if (low < high) {
        int pi = particionLomuto(arr, low, high, tipoPivote);
        quickSort(arr, low, pi - 1, tipoPivote);
        quickSort(arr, pi + 1, high, tipoPivote);
    }
}

/**
 * @brief Encuentra el K-ésimo mejor deportista (sin requerir ordenar el arreglo por completo). 
 * Variación algorítmica de Quick Sort. Utiliza pivote aleatorio por defecto.
 * @param arr Arreglo base.
 * @param low Límite inferior.
 * @param high Límite superior.
 * @param k Posición lógica solicitada a buscar.
 * @return Estructura del k-ésimo deportista.
 */
Deportista quickSelect(Deportista arr[], int low, int high, int k) {
    if (low == high) return arr[low];
    
    int pi = particionLomuto(arr, low, high, 3); // Pivote aleatorio por defecto
    
    if (k == pi) return arr[pi];
    else if (k < pi) return quickSelect(arr, low, pi - 1, k);
    else return quickSelect(arr, pi + 1, high, k);
}

/**
 * @brief Variante de QuickSelect forzando el pivote último, usada en validaciones de peores casos experimentales.
 * @param arr Arreglo base.
 * @param low Límite inferior.
 * @param high Límite superior.
 * @param k Posición lógica.
 * @return Estructura del k-ésimo deportista.
 */
Deportista quickSelectUltimo(Deportista arr[], int low, int high, int k) {
    if (low == high) return arr[low];
 
    int pi = particionLomuto(arr, low, high, 1); /* pivote = último elemento */
 
    if (k == pi)      return arr[pi];
    else if (k < pi)  return quickSelectUltimo(arr, low, pi - 1, k);
    else              return quickSelectUltimo(arr, pi + 1, high, k);
}

/**
 * @brief Realiza una Búsqueda Binaria puramente Recursiva en arreglos ordenados ascendentemente (o descendentemente).
 * @param arr Arreglo donde se buscará el target.
 * @param left Puntero base izquierdo.
 * @param right Puntero máximo derecho.
 * @param target Puntaje u objetivo esperado.
 * @return Índice o -1.
 */
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

/**
 * @brief Ubica la primera y última aparición de un puntaje objetivo permitiendo definir su "rango" en tablas que pueden tener duplicados.
 * @param arr Arreglo ordenado.
 * @param n Cantidad total de elementos.
 * @param target Puntaje objetivo del que se obtendrán límites.
 * @param inicio Parámetro por referencia que almacenará el índice en que inicia.
 * @param fin Parámetro por referencia que almacenará el índice final de presencia.
 */
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

/**
 * @brief Búsqueda Exponencial recomendada cuando no hay límites superiores rígidos o si el índice es predecible a la brevedad.
 * @param arr Arreglo fuente.
 * @param n Límite actual de elementos.
 * @param target Objetivo de puntaje esperado.
 * @return Índice u error en -1.
 */
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

/**
 * @brief Búsqueda de interpolación, estima las posiciones mediante proporción matemática.
 * @param arr Arreglo uniformemente distribuido.
 * @param n Cantidad de posiciones.
 * @param target Puntaje a buscar.
 * @return Índice u error si no existe.
 */
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