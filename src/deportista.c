#include <stdio.h>
#include "deportista.h"

void imprimirDeportistas(Deportista arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf(
            "ID: %d | Nombre: %s | Equipo: %s | Puntaje: %.2f | Competencias: %d\n",
            arr[i].id,
            arr[i].nombre,
            arr[i].equipo,
            arr[i].puntaje,
            arr[i].competencias
        );

    }
}