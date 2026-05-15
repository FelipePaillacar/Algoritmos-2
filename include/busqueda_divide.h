#ifndef BUSQUEDA_DIVIDE_H
#define BUSQUEDA_DIVIDE_H

#include "deportista.h"

int busqueda_binaria_recursiva(Deportista arr[], int l, int r, int id_buscado);
void busqueda_binaria_rango(Deportista arr[], int n, float valor_buscado);
int busqueda_exponencial(Deportista arr[], int n, int id_buscado);
int busqueda_interpolacion(Deportista arr[], int n, int id_buscado);

void busqueda_rango_min_max(Deportista arr[], int n, float min_pts, float max_pts);

// Selección: Retorna el k-ésimo mejor (requiere array y k)
Deportista quick_select(Deportista arr[], int low, int high, int k, int campo);

#endif // BUSQUEDA_DIVIDE_H