CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJS = main.o deportista.o menu.o ordenamiento.o busqueda.o
TARGET = proyecto1

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c deportista.h menu.h ordenamiento.h busqueda.h
	$(CC) $(CFLAGS) -c main.c -o main.o

deportista.o: deportista.c deportista.h
	$(CC) $(CFLAGS) -c deportista.c -o deportista.o

menu.o: menu.c menu.h
	$(CC) $(CFLAGS) -c menu.c -o menu.o

ordenamiento.o: ordenamiento.c ordenamiento.h deportista.h
	$(CC) $(CFLAGS) -c ordenamiento.c -o ordenamiento.o

busqueda.o: busqueda.c busqueda.h deportista.h
	$(CC) $(CFLAGS) -c busqueda.c -o busqueda.o

clean:
	rm -f *.o $(TARGET)
