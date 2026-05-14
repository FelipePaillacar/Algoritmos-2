/**
 * @file busqueda.c
 * @brief Implementación de algoritmos de búsqueda clásicos (Tarea 1).
 */
#include "busqueda.h"

/**
 * @brief Búsqueda Secuencial: Itera linealmente elemento a elemento hasta hallar coincidencia.
 * Utilizable independientemente de si el arreglo está ordenado o no.
 * @param arr Arreglo de deportistas donde realizar la búsqueda.
 * @param n Cantidad total de deportistas.
 * @param id_buscado El ID objetivo.
 * @return int Retorna el índice donde se ubica el elemento, o -1 en caso de no encontrarse.
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
 * @brief Búsqueda Binaria Iterativa: Estrategia de reducción de ventanas a la mitad mediante bucle while.
 * Require de forma estricta un arreglo ordenado para su correcto funcionamiento.
 * @param arr Arreglo de deportistas.
 * @param n Cantidad total de deportistas.
 * @param id_buscado El ID objetivo.
 * @return int Retorna el índice exacto, o -1 en caso de no encontrarse.
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