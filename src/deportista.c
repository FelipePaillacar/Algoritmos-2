#include <stdio.h>
#include "deportista.h"

void imprimirDeportistas(Deportista arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("ID: %d | Nombre: %s | Puntaje: %.2f\n",
               arr[i].id,
               arr[i].nombre,
               arr[i].puntaje);
    }
}