CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

all: sistema tester

# Programa interactivo para el Estudiante 1 (Aplicacion Practica)
sistema: src/main.c src/algoritmos.c
	$(CC) $(CFLAGS) -o sistema src/main.c src/algoritmos.c

# Programa automatizado para el Estudiante 2 (Medicion de Tiempos)
tester: src/analisis_experimental.c src/algoritmos.c
	$(CC) $(CFLAGS) -o tester src/analisis_experimental.c src/algoritmos.c

# Regla para que el Estudiante 3 genere sus graficos con un solo comando
graficos: tester
	mkdir -p data plots
	./tester
	@echo "Generando gráficos con Gnuplot..."
	gnuplot plots/graficos.gp
clean:
	rm -f sistema tester
	rm -f data/*.csv plots/*.png
