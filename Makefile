# Compilador a utilizar
CC=gcc
# Flags para el compilador: -Wall para warnings, -g para debug
CFLAGS=-Wall -g
# Archivo ejecutable final
TARGET=proyecto1
# Encuentra todos los archivos .c en el directorio actual
SOURCES=$(wildcard *.c)
# Genera los nombres de los archivos objeto (.o) a partir de los fuentes
OBJECTS=$(SOURCES:.c=.o)

# Regla principal para construir todo
all: $(TARGET)

# Regla para enlazar los archivos objeto y crear el ejecutable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Regla para compilar archivos .c a .o
# $< es el primer prerrequisito (el .c)
# $@ es el nombre del objetivo (el .o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
