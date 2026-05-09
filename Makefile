# Detección del Sistema Operativo
ifeq ($(OS),Windows_NT)
    # Comandos para Windows
    RM = del /Q
    MKDIR = if not exist $(BUILD_DIR) mkdir
    EXEC = $(BUILD_DIR)\programa.exe
    FIX_PATH = $(subst /,\,$1)
    CLEAN_CMD = if exist $(BUILD_DIR) rd /s /q $(BUILD_DIR)
else
    # Comandos para Linux/macOS
    RM = rm -f
    MKDIR = mkdir -p
    EXEC = $(BUILD_DIR)/programa
    FIX_PATH = $1
    CLEAN_CMD = rm -rf $(BUILD_DIR)
endif

CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -O2
INCLUDE = -I./incs
SRC_DIR = src
BUILD_DIR = build
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

.PHONY: all clean run

all: $(EXEC)

$(EXEC): $(SRC_FILES)
	@$(MKDIR) $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC_FILES) -o $(EXEC) -lm

run: $(EXEC)
	$(call FIX_PATH,./$(EXEC))

clean:
	$(CLEAN_CMD)

folders:
ifeq ($(OS),Windows_NT)
	if not exist src mkdir src
	if not exist incs mkdir incs
	if not exist obj mkdir obj
	if not exist build mkdir build
	if not exist db mkdir db
	if not exist plots mkdir plots
	if not exist tests mkdir tests
else
	mkdir -p src incs obj build db plots tests
endif

plot:
	@echo "Generando graficos..."
	