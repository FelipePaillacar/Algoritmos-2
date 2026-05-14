#include "busqueda.h"

int busqueda_secuencial(Deportista arr[], int n, int id_buscado) {
    for (int i = 0; i < n; i++) {
        if (arr[i].id == id_buscado) {
            return i;
        }
    }
    return -1; // No encontrado
}

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