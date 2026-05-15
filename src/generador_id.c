/**
 * @file generador_id.c
 * @brief Utilería aislada para la demostración y generación de IDs autoincrementales sin solapamiento.
 */
#include <stdio.h>
#include <stdlib.h>

// Estructura base para el deportista
typedef struct {
    int id;
    // Aquí irán los demás campos: nombre, equipo, puntaje, competencias
} Deportista;

/**
 * @brief Crea un deportista y le asigna un ID auto-incrementable a nivel global utilizando variables estáticas locales.
 * @return Devuelve un deportista nuevo con su ID preparado.
 */
Deportista generar_deportista_con_id() {
    // La variable estática conserva su valor entre las distintas llamadas a la función
    static int contador_id = 1;
    
    Deportista nuevo_deportista;
    nuevo_deportista.id = contador_id; // Asignamos el valor actual
    contador_id++;                     // Incrementamos para el siguiente deportista
    
    return nuevo_deportista;
}
