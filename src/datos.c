#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../incs/datos.h"
#include "../incs/deportista.h"

const char* equipos[] = {"RedBull", "Ferrari", "Mercedes", "McLaren", "Alpine", "AstonMartin", "Williams"};
const int num_equipos = 7;

static void inicializar_aleatoriedad(void) {
    static int inicializado = 0;

    if (!inicializado) {
        srand((unsigned int)time(NULL));
        inicializado = 1;
    }
}

static void generar_nombre(char* nombre, int longitud) {
    const char abecedario[] = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < longitud - 1; i++) {
        nombre[i] = abecedario[rand() % 26];
    }
    nombre[longitud - 1] = '\0';
}

void generar_deportistas(Deportista* arreglo, int n) {
    inicializar_aleatoriedad();

    for (int i = 0; i < n; i++) {
        arreglo[i].id = i + 1;
        generar_nombre(arreglo[i].nombre, 8);
        strcpy(arreglo[i].equipo, equipos[rand() % num_equipos]);
        arreglo[i].puntaje = (rand() % 1000) / 10.0f;
        arreglo[i].competencias = rand() % 50;
    }
}

void mezclar_deportistas(Deportista* arreglo, int n) {
    inicializar_aleatoriedad();

    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Deportista temp = arreglo[i];
        arreglo[i] = arreglo[j];
        arreglo[j] = temp;
    }
}

void guardar_csv(Deportista* arreglo, int n, const char* ruta_destino) {
    FILE* archivo = fopen(ruta_destino, "w");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "ID,Nombre,Equipo,Puntaje,Competencias\n");
    for (int i = 0; i < n; i++) {
        fprintf(archivo, "%d,%s,%s,%.1f,%d\n",
                arreglo[i].id,
                arreglo[i].nombre,
                arreglo[i].equipo,
                arreglo[i].puntaje,
                arreglo[i].competencias);
    }

    fclose(archivo);
    printf("Datos guardados en %s exitosamente.\n", ruta_destino);
}

int leer_csv(const char* ruta_destino, Deportista** arreglo) {
    FILE* archivo = fopen(ruta_destino, "r");
    char linea[256];
    int contador = 0;
    int capacidad = 100;

    if (archivo == NULL) {
        printf("Error al abrir el archivo %s para lectura.\n", ruta_destino);
        return 0;
    }

    *arreglo = (Deportista*)malloc((size_t)capacidad * sizeof(Deportista));
    if (*arreglo == NULL) {
        printf("Error al asignar memoria.\n");
        fclose(archivo);
        return 0;
    }

    if (fgets(linea, sizeof(linea), archivo) == NULL) {
        fclose(archivo);
        free(*arreglo);
        *arreglo = NULL;
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        if (contador >= capacidad) {
            Deportista* temp;

            capacidad *= 2;
            temp = realloc(*arreglo, (size_t)capacidad * sizeof(Deportista));
            if (temp == NULL) {
                printf("Error al reasignar memoria.\n");
                break;
            }
            *arreglo = temp;
        }

        if (sscanf(linea, "%d,%49[^,],%49[^,],%f,%d",
                   &(*arreglo)[contador].id,
                   (*arreglo)[contador].nombre,
                   (*arreglo)[contador].equipo,
                   &(*arreglo)[contador].puntaje,
                   &(*arreglo)[contador].competencias) == 5) {
            contador++;
        }
    }

    fclose(archivo);
    return contador;
}