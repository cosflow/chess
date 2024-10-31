// utils.h
#ifndef UTILS_H
#define UTILS_H
#include "data.h"

int cambiarTurno(int turno);
int comprobarCasilla(int x, int y, Pieza * piezas[]);
int legal(int xdes, int ydes, Pieza * p);
int comprobarCamino(int xdes, int ydes, Pieza * p, Pieza * piezas[]);

#endif
