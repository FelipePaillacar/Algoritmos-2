CC = gcc
CFLAGS = -Wall -Iinclude

SRC_DIR = src
BUILD_DIR = build

# Encuentra todos los archivos .c en la carpeta src
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# El nombre del ejecutable final
TARGET = $(BUILD_DIR)/programa

all: $(TARGET)

$(TARGET): $(SOURCES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Compilación exitosa. Ejecutable generado en $(TARGET)"

clean:
	rm -rf $(BUILD_DIR)/*
	@echo "Archivos compilados eliminados."

run: $(TARGET)
	./$(TARGET)
