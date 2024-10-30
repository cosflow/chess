// utils.h
#ifndef UTILS_H
#define UTILS_H
#include "data.h"

int comprobarCasilla(int x, int y, Pieza * blancas[], Pieza * negras[]);
int legal(int xdes, int ydes, Pieza * p);
int comprobarCamino(int xdes, int ydes, Pieza * p, Pieza * blancas[], Pieza * negras[]);

#endif
