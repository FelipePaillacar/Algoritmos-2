# Proyecto 2: Algoritmos de Divide y Vencerás

Este repositorio contiene la implementación y el análisis experimental de diversos algoritmos de ordenamiento, búsqueda y selección basados en la estrategia **Divide y Vencerás**, aplicados a un Sistema de Deportistas en lenguaje C.

## Características y Funcionalidades

El proyecto se divide en dos enfoques principales:

1. **Aplicación Práctica (Interactiva):** Un menú donde se puede simular el comportamiento de una base de datos con deportistas, permitiendo ordenar y buscar según diferentes criterios midiendo sus tiempos en tiempo real.
2. **Análisis Experimental (Tester Automatizado):** Un generador de *benchmarks* que evalúa los algoritmos mediante miles de ejecuciones aleatorias, variando N desde 10,000 hasta 100,000, y exportando los tiempos a archivos `CSV` para graficarlos con Gnuplot.

### Algoritmos Implementados
- **Ordenamiento:** MergeSort (clásico y optimizado), QuickSort (Lomuto con múltiples opciones de pivote), BubbleSort, SelectionSort, InsertionSort.
- **Selección:** QuickSelect (Top N, k-ésimo elemento).
- **Búsqueda:** Binaria (recursiva y de rangos), Exponencial, Interpolación.

---

## Estructura del Proyecto

```text
Algoritmos-2-main/
├── Makefile                # Reglas de compilación automatizadas
├── README.md               # Este documento
├── src/
│   ├── main.c              # Menú interactivo (Aplicación Práctica)
│   ├── analisis_experimental.c # Generador automatizado de tiempos
│   ├── algoritmos.c        # Lógica matemática e implementación
│   └── algoritmos.h        # Declaraciones y Doxygen API
├── data/                   # Archivos .csv de resultados (autogenerados)
└── plots/                  # Scripts de Gnuplot e imágenes .png de salida
```

---

## Instrucciones de Uso

### Prerrequisitos
Necesitas tener instalados en tu entorno Linux/WSL:
- Compilador `gcc` y herramientas `make`
- `gnuplot` (Para generar los gráficos)

### 1. Compilación
Desde la raíz del proyecto, ejecuta:
```bash
make clean
make
```
Esto creará dos ejecutables: `./sistema` y `./tester`.

### 2. Ejecutar Menú Interactivo
```bash
./sistema
```

### 3. Generar Gráficos y Reportes .CSV de un solo golpe
```bash
make graficos
```
Este comando automatizado correrá las pruebas de tiempo, generará los archivos en la carpeta `data/` y llamará a `gnuplot` para procesar las imágenes resultantes en la carpeta `plots/`.