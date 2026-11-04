CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRCS = src/fila_fifo.c src/lista_ord.c src/heap_max.c src/main.c
TARGET = sistema_chamados

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe
