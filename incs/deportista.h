#ifndef DEPORTISTA_H
#define DEPORTISTA_H
#define MAX_NOMBRE 50
#define MAX_EQUIPO 50

typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    char equipo[MAX_EQUIPO];
    float puntaje;
    int competencias;
} Deportista;

void imprimirDeportistas(Deportista arr[], int n);

#endif