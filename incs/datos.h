#ifndef DATOS_H
#define DATOS_H

#include "deportista.h"

// Funciones para generar y guardar datos
void generar_deportistas(Deportista* arreglo, int n, int tipo_generacion);
void mezclar_deportistas(Deportista* arreglo, int n);
void guardar_csv(Deportista* arreglo, int n, const char* ruta_destino);
int leer_csv(const char* ruta_destino, Deportista** arreglo);

#endif