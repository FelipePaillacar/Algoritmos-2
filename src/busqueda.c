/**
 * @file busqueda.c
 * @brief Implementación de algoritmos de búsqueda simples (Secuencial y Binaria de Tarea 1).
 */
#include "busqueda.h"

/**
 * @brief Realiza una búsqueda secuencial comprobando uno por uno sin depender de orden previo.
 * @param arr Arreglo de deportistas.
 * @param n Tamaño del arreglo.
 * @param id_buscado ID a localizar de forma lineal.
 * @return Índice del deportista si se encuentra, -1 en caso contrario.
 */
int busqueda_secuencial(Deportista arr[], int n, int id_buscado) {
    for (int i = 0; i < n; i++) {
        if (arr[i].id == id_buscado) {
            return i;
        }
    }
    return -1; // No encontrado
}

/**
 * @brief Realiza una iteración matemática por mitades sucesivas (Binaria no recursiva).
 * @param arr Arreglo de deportistas (debe estar ordenado previamente por ID).
 * @param n Tamaño del arreglo.
 * @param id_buscado ID a localizar en menos pasos que la secuencial.
 * @return Índice del deportista si se encuentra, -1 en caso contrario.
 */
int busqueda_binaria(Deportista arr[], int n, int id_buscado) {
    int low = 0;
    int high = n - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid].id == id_buscado) {
            return mid;
        }
        
        if (arr[mid].id < id_buscado) low = mid + 1;
        else high = mid - 1;
    }
    return -1; // No encontrado
}