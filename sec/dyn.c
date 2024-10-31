#include "dyn.h"

void mover(int x, int y, Pieza * p){
    p->f = x;
    p->c = y;
    p->movida=1;
}