/**
 * @file busqueda_divide.c
 * @brief Algoritmos de búsqueda basados en Divide y Vencerás y otras estrategias matemáticas.
 */
#include "busqueda_divide.h"
#include "ordenamiento_divide.h" // Para reutilizar partition_lomuto
#include <stdio.h>

/**
 * @brief Búsqueda Binaria Recursiva: Encuentra un ID dividiendo el arreglo a la mitad en cada llamada.
 * @param arr Arreglo de deportistas (Debe encontrarse ordenado previamente por ID).
 * @param l Índice inferior de búsqueda.
 * @param r Índice superior de búsqueda.
 * @param id_buscado El número de ID exacto a localizar.
 * @return int Índice del deportista encontrado, o -1 si no existe en el arreglo.
 */
int busqueda_binaria_recursiva(Deportista arr[], int l, int r, int id_buscado) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid].id == id_buscado) return mid;
        if (arr[mid].id > id_buscado) return busqueda_binaria_recursiva(arr, l, mid - 1, id_buscado);
        return busqueda_binaria_recursiva(arr, mid + 1, r, id_buscado);
    }
    return -1;
}

/**
 * @brief Búsqueda Binaria para Rango: Obtiene el límite inferior y superior de ocurrencias de un puntaje.
 * Imprime los índices límite directamente en consola.
 * @param arr Arreglo de deportistas (Debe encontrarse ordenado previamente por Puntaje).
 * @param n Tamaño total del arreglo.
 * @param valor_buscado El puntaje flotante objetivo del rango.
 */
void busqueda_binaria_rango(Deportista arr[], int n, float valor_buscado) {
    int low = 0, high = n - 1;
    int primera = -1, ultima = -1;

    // Búsqueda de la primera aparición
    while(low <= high) {
        int mid = low + (high - low)/2;
        if(arr[mid].puntaje == valor_buscado) { primera = mid; high = mid - 1; }
        else if(arr[mid].puntaje < valor_buscado) low = mid + 1;
        else high = mid - 1;
    }

    // Búsqueda de la última aparición (Optimizada)
    // Si encontramos la primera, empezamos a buscar desde ahí en lugar del índice 0
    if (primera != -1) { low = primera; } else { low = 0; }
    high = n - 1;
    while(low <= high) {
        int mid = low + (high - low)/2;
        if(arr[mid].puntaje == valor_buscado) { ultima = mid; low = mid + 1; }
        else if(arr[mid].puntaje < valor_buscado) low = mid + 1;
        else high = mid - 1;
    }

    if (primera != -1) {
        printf("El valor se encontró en el rango de índices: [%d, %d]\n", primera, ultima);
    } else {
        printf("Valor no encontrado en el arreglo.\n");
    }
}

/**
 * @brief Encuentra e imprime los deportistas dentro de un rango de puntajes (min - max).
 * Utiliza búsqueda binaria para ubicar los extremos del rango en O(log n).
 */
void busqueda_rango_min_max(Deportista arr[], int n, float min_pts, float max_pts) {
    int left = 0, right = n - 1;
    int start_idx = -1, end_idx = -1;

    // 1. Buscar el primer elemento que sea MAYOR O IGUAL a min_pts
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].puntaje >= min_pts) {
            start_idx = mid;
            right = mid - 1; // Seguimos buscando hacia la izquierda para encontrar el primero
        } else {
            left = mid + 1;
        }
    }

    // 2. Buscar el último elemento que sea MENOR O IGUAL a max_pts
    left = 0; right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].puntaje <= max_pts) {
            end_idx = mid;
            left = mid + 1; // Seguimos buscando hacia la derecha para encontrar el último
        } else {
            right = mid - 1;
        }
    }

    // 3. Validar e imprimir resultados
    if (start_idx != -1 && end_idx != -1 && start_idx <= end_idx) {
        printf("\n--- DEPORTISTAS EN EL RANGO [%.2f - %.2f] ---\n", min_pts, max_pts);
        for (int i = start_idx; i <= end_idx; i++) {
            imprimir_deportista(arr[i]); 
        }
    } else {
        printf("\nNo se encontraron deportistas en ese rango de puntajes.\n");
    }
}

/**
 * @brief Búsqueda Exponencial: Aumenta exponencialmente el límite hasta hallar un subrango válido.
 * @param arr Arreglo de deportistas (Debe encontrarse ordenado).
 * @param n Tamaño total del arreglo.
 * @param id_buscado El número de ID a localizar.
 * @return int Índice del deportista, o -1 en caso de no existir.
 */
int busqueda_exponencial(Deportista arr[], int n, int id_buscado) {
    if (arr[0].id == id_buscado) return 0;
    int i = 1;
    while (i < n && arr[i].id <= id_buscado) i = i * 2;
    
    int r = (i < n - 1) ? i : (n - 1);
    return busqueda_binaria_recursiva(arr, i / 2, r, id_buscado);
}

/**
 * @brief Búsqueda por Interpolación: Estima linealmente la posición basándose en el ID mínimo y máximo del rango.
 * Recomendada para arreglos uniformemente distribuidos.
 * @param arr Arreglo de deportistas (Debe encontrarse ordenado).
 * @param n Tamaño total del arreglo.
 * @param id_buscado El número de ID a localizar.
 * @return int Índice calculado del deportista, o -1 si no existe.
 */
int busqueda_interpolacion(Deportista arr[], int n, int id_buscado) {
    int low = 0, high = (n - 1);
    while (low <= high && id_buscado >= arr[low].id && id_buscado <= arr[high].id) {
        if (low == high) {
            if (arr[low].id == id_buscado) return low;
            return -1;
        }
        // Estimación matemática basada en el valor ID
        int pos = low + (((double)(high - low) / (arr[high].id - arr[low].id)) * (id_buscado - arr[low].id));
        
        if (arr[pos].id == id_buscado) return pos;
        if (arr[pos].id < id_buscado) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

/**
 * @brief Algoritmo Quick Select: Encuentra el K-ésimo elemento más grande/pequeño sin ordenar el arreglo total.
 * @param arr Arreglo sobre el cual iterar (sufre modificaciones de posiciones internas por el particionamiento).
 * @param low Índice de inicio.
 * @param high Índice final.
 * @param k La posición K a buscar (basada en el índice partiendo desde 0).
 * @param campo Criterio por el cual realizar la evaluación.
 * @return Deportista que ocuparía la k-ésima posición en un arreglo totalmente ordenado.
 */
Deportista quick_select(Deportista arr[], int low, int high, int k, int campo) {
    if (low == high) return arr[low];
    
    int pivot_idx = partition_lomuto(arr, low, high, PIVOT_ULTIMO, campo);
    if (k == pivot_idx) return arr[k];
    else if (k < pivot_idx) return quick_select(arr, low, pivot_idx - 1, k, campo);
    else return quick_select(arr, pivot_idx + 1, high, k, campo);
}