#ifndef ORDENAMIENTO_DIVIDE_H
#define ORDENAMIENTO_DIVIDE_H

#include "deportista.h"

// Constantes para la selección del pivote en Quick Sort
#define PIVOT_ULTIMO 1
#define PIVOT_PRIMER 2
#define PIVOT_ALEATORIO 3
#define PIVOT_MEDIANA 4

void merge_sort(Deportista arr[], int l, int r, int campo);
void merge_sort_optimizado(Deportista arr[], int l, int r, int campo, int umbral);
void quick_sort_lomuto(Deportista arr[], int low, int high, int tipo_pivote, int campo);

// Función expuesta para usarla en Quick Select
int partition_lomuto(Deportista arr[], int low, int high, int tipo_pivote, int campo);

#endif 