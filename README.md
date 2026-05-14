Este proyecto en C implementa diversos algoritmos de ordenamiento y búsqueda para gestionar una base de datos de deportistas. El sistema permite generar millones de registros, guardarlos en archivos `.csv` y analizar el rendimiento de distintos algoritmos bajo diferentes casos (Mejor, Peor y Caso Promedio).

El código fuente está organizado de forma modular 

- `src/`: Contiene todo el código fuente (`.c`).
- `include/`: Contiene los archivos de cabecera (`.h`).
- `data/`: Carpeta destinada a la persistencia de datos (ej. `datos.csv`).
- `build/`: Directorio donde se genera el ejecutable compilado.
- `Makefile`: Script para automatizar la compilación del proyecto.



Tutorial de Uso (Menú Interactivo)

El programa cuenta con un menú interactivo en consola. Al iniciar, verás el **Menú Principal**, que divide los algoritmos en dos enfoques de programación:

- Tarea 1 (Ordenamientos Clásicos): Incluye algoritmos iterativos tradicionales.
- Tarea 2 (Divide y Vencerás): Incluye algoritmos recursivos 

Gestión de Datos 
Antes de probar cualquier algoritmo, necesitas datos. En este submenú puedes:
- Generar deportistas aleatorios:Crea un set de datos desordenado (Caso promedio).
- Generar datos ordenados o inversamente ordenados: Útil para evaluar cómo reaccionan los algoritmos en su Mejor o Peor caso.
- Cargar desde CSV:** Carga a la memoria el archivo `data/datos.csv` previamente guardado.

Algoritmos de Ordenamiento
Una vez que tengas datos cargados, puedes ordenarlos eligiendo el campo (ID, Nombre, Equipo, Puntaje o Competencias).
- En la Tarea 1** podrás probar algoritmos como: *Bubble Sort, Insertion Sort, Selection Sort y Cocktail Shaker Sort*.
-En la Tarea 2** podrás probar enfoques más rápidos como: *Merge Sort (Clásico y Optimizado)* y *Quick Sort* (eligiendo distintas estrategias de pivote como el Último, Primer, Aleatorio o Mediana de 3).
El programa te mostrará por pantalla el tiempo exacto (en segundos) que tardó en ordenar.*

Algoritmos de Búsqueda
Al igual que con el ordenamiento, los métodos varían:
- En la Tarea 1:Búsqueda Secuencial (lenta pero no requiere orden) y *Búsqueda Binaria Iterativa*.
- En la Tarea 2:*Opciones avanzadas como *Búsqueda Binaria Recursiva, Exponencial, por Interpolación* y *Búsqueda Binaria de Rangos* (para buscar a todos los deportistas con cierto puntaje).
*Nota: La mayoría de búsquedas ordenarán la lista automáticamente por el campo requerido antes de buscar.*

Ranking y Selección 
Este submenú permite extraer estadísticas valiosas de los deportistas:
- Quick Select:Permite encontrar al "k-ésimo" mejor deportista (por puntaje) **sin tener que ordenar toda la lista**, haciéndolo extremadamente rápido.
- Ranking Top N: Ordena los puntajes y te muestra en pantalla a los "N" mejores deportistas de la base de datos.
