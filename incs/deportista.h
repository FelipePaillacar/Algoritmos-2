#ifndef DEPORTISTA_H
#define DEPORTISTA_H

typedef struct {
    int id;
    char nombre[50];
    float puntaje;
} Deportista;

void imprimirDeportistas(Deportista arr[], int n);

#endif