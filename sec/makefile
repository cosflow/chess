# Variables
CC = gcc
CFLAGS = -Wall -g
SRC = chess2.c carga.c utils.c io.c dyn.c
OBJ = $(SRC:.c=.o)
TARGET = chess_program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.exe

.PHONY: all clean

