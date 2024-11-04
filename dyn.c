#include "dyn.h"
#include "utils.h"

void mover(int y, int x, Pieza * p, Pieza * piezas[]){
    int m = comprobarCasilla(x, y, piezas);
    if (m != -1) piezas[m]->M = 1;
    p->f = y;
    p->c = x;
    p->movida=1;
}