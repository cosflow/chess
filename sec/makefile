# Variables
CC = gcc
CFLAGS = -Wall -g
SRC = chess2.c carga.c io.c
OBJ = $(SRC:.c=.o)
TARGET = chess_program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

