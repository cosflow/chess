// io.h
#ifndef IO_H
#define IO_H
#include "data.h"
void bienvenida();
void imprimirTablero(Pieza * blancas[], Pieza * negras[], int turno);
int recibirCoord(int * fil, int * col);
#endif
