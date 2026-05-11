// En src/datos.c, tu función debería verse así:
#include "datos.h"
#include "deportista.h"
#include <stdlib.h> // para rand()
#include <string.h> // para strcpy()
#include <stdio.h>

// ... otros includes que necesites ...

void generar_deportistas(Deportista* arreglo, int n, int tipo_generacion) {
    // Lógica de generación base
    for (int i = 0; i < n; i++) {
        // Generación aleatoria como caso base (promedio)
        arreglo[i].id = i + 1; // O un ID aleatorio si lo prefieres
        sprintf(arreglo[i].nombre, "Deportista_%d", i + 1);
        sprintf(arreglo[i].equipo, "Equipo_%d", (i % 10) + 1);
        arreglo[i].puntaje = (rand() % 1000) + 1;
        arreglo[i].competencias = (rand() % 20) + 1;
    }

    // Ajustes según el tipo de generación solicitado
    switch (tipo_generacion) {
        case 1:
            // Caso Promedio: Ya está hecho (o puedes mezclarlo más si quieres)
            // Aquí podrías implementar un shuffle (ej. Fisher-Yates) si los IDs son secuenciales
            printf("Generando caso promedio (aleatorio).\n");
            break;
        case 2:
            // Mejor Caso: Datos ya ordenados por ID.
            // Si los IDs se generan secuencialmente (como arriba), no hay que hacer nada más.
            printf("Generando mejor caso (ordenado por ID).\n");
            break;
        case 3:
            // Peor Caso: Datos inversamente ordenados por ID.
            printf("Generando peor caso (inversamente ordenado por ID).\n");
            for (int i = 0; i < n; i++) {
                arreglo[i].id = n - i;
            }
            break;
    }
}
void guardar_csv(Deportista* arreglo, int n, const char* ruta_destino) {
    FILE* archivo = fopen(ruta_destino, "w");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo '%s' para escritura.\n", ruta_destino);
        return;
    }

    // Escribir la cabecera del CSV
    fprintf(archivo, "id,nombre,equipo,puntaje,competencias\n");

    // Escribir los datos de cada deportista
    for (int i = 0; i < n; i++) {
        fprintf(archivo, "%d,%s,%s,%f,%d\n",
                arreglo[i].id,
                arreglo[i].nombre,
                arreglo[i].equipo,
                arreglo[i].puntaje,
                arreglo[i].competencias);
    }

    fclose(archivo);
}
