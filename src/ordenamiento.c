/**
 * @file ordenamiento.c
 * @brief Implementación de algoritmos de ordenamiento clásicos (Tarea 1).
 */
#include "ordenamiento.h"
#include <string.h> // Para strcmp

/**
 * @brief Función de comparación genérica para algoritmos de ordenamiento iterativos.
 * @param a Primer deportista a evaluar.
 * @param b Segundo deportista a evaluar.
 * @param campo Criterio de evaluación.
 * @return Valor numérico de evaluación.
 */
int comparar_deportistas(Deportista a, Deportista b, int campo) {
    switch(campo) {
        case 1: return a.id - b.id;
        case 2: return strcmp(a.nombre, b.nombre);
        case 3: return strcmp(a.equipo, b.equipo);
        case 4: return (a.puntaje > b.puntaje) - (a.puntaje < b.puntaje); // Evita problemas de truncamiento con floats
        case 5: return a.competencias - b.competencias;
        default: return 0;
    }
}

/**
 * @brief Genera un ranking ordenando el arreglo en modo descendente basándose exclusivamente en el puntaje.
 * @param arreglo Arreglo de deportistas.
 * @param cantidad Tamaño del arreglo a ordenar.
 */
void ordenar_ranking_descendente(Deportista *arreglo, int cantidad) {
    for (int i = 0; i < cantidad - 1; i++) {
        int intercambiado = 0; 
        for (int j = 0; j < cantidad - i - 1; j++) {
            if (arreglo[j].puntaje < arreglo[j + 1].puntaje) {
                Deportista temp = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = temp;
                intercambiado = 1;
            }
        }
        if (!intercambiado) break;
    }
}

/**
 * @brief Bubble Sort Optimizado: Compara pares adyacentes y detiene el proceso de forma temprana 
 * si el arreglo ya está ordenado.
 * @param arreglo Arreglo de deportistas.
 * @param cantidad Tamaño del arreglo.
 * @param campo Criterio por el cual ordenar.
 */
void bubble_sort(Deportista *arreglo, int cantidad, int campo) {
    for (int i = 0; i < cantidad - 1; i++) {
        int intercambiado = 0;
        for (int j = 0; j < cantidad - i - 1; j++) {
            if (comparar_deportistas(arreglo[j], arreglo[j + 1], campo) > 0) {
                Deportista temp = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = temp;
                intercambiado = 1;
            }
        } 
        if (!intercambiado) break; // Optimización solicitada
    }
}

/**
 * @brief Insertion Sort Estándar: Construye la lista ordenada tomando de a un elemento a la vez.
 * @param arreglo Arreglo de deportistas.
 * @param cantidad Tamaño del arreglo.
 * @param campo Criterio por el cual ordenar.
 */
void insertion_sort(Deportista *arreglo, int cantidad, int campo) {
    for (int i = 1; i < cantidad; i++) {
        Deportista clave = arreglo[i];
        int j = i - 1;
        while (j >= 0 && comparar_deportistas(arreglo[j], clave, campo) > 0) {
            arreglo[j + 1] = arreglo[j];
            j = j - 1;
        }
        arreglo[j + 1] = clave;
    }
}

/**
 * @brief Selection Sort con Intercambio Minimizado: Localiza el mínimo en cada paso para evitar intercambios redundantes.
 * @param arreglo Arreglo de deportistas.
 * @param cantidad Tamaño del arreglo.
 * @param campo Criterio por el cual ordenar.
 */
void selection_sort(Deportista *arreglo, int cantidad, int campo) {
    for (int i = 0; i < cantidad - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < cantidad; j++) {
            if (comparar_deportistas(arreglo[j], arreglo[min_idx], campo) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) { // Optimización solicitada
            Deportista temp = arreglo[i];
            arreglo[i] = arreglo[min_idx];
            arreglo[min_idx] = temp;
        }
    }
}

/**
 * @brief Cocktail Shaker Sort: Variante bidireccional del Bubble Sort.
 * @param arreglo Arreglo de deportistas.
 * @param cantidad Tamaño del arreglo.
 * @param campo Criterio por el cual ordenar.
 */
void cocktail_shaker_sort(Deportista *arreglo, int cantidad, int campo) {
    int intercambiado = 1;
    int inicio = 0;
    int fin = cantidad - 1;
    while (intercambiado) {
        intercambiado = 0;
        for (int i = inicio; i < fin; ++i) { // De izquierda a derecha
            if (comparar_deportistas(arreglo[i], arreglo[i + 1], campo) > 0) {
                Deportista temp = arreglo[i];
                arreglo[i] = arreglo[i + 1];
                arreglo[i + 1] = temp;
                intercambiado = 1;
            }
        }
        if (!intercambiado) break;
        intercambiado = 0;
        fin--;
        for (int i = fin - 1; i >= inicio; --i) { // De derecha a izquierda
            if (comparar_deportistas(arreglo[i], arreglo[i + 1], campo) > 0) {
                Deportista temp = arreglo[i];
                arreglo[i] = arreglo[i + 1];
                arreglo[i + 1] = temp;
                intercambiado = 1;
            }
        }
        inicio++;
    }
}