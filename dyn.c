#include "dyn.h"
#include "utils.h"

int mover(int y, int x, Pieza * p, Pieza * piezas[]){
    int m = comprobarCasilla(x, y, piezas);
    int j;
    int xprev = p->c;
    int yprev = p->f;
    if (m != -1) piezas[m]->M = 1;
    p->f = y;
    p->c = x;
    if(p->color){
        j = comprobarJaque(piezas[0], piezas);
        if(j != 0){
            p->c = xprev;
            p->f = yprev;
            return j;
        }
    }
    else{
        j = comprobarJaque(piezas[16], piezas);
        if(j != 0){
            p->c = xprev;
            p->f = yprev;
            return j;
        }
    }
    p->movida=1;
    return 0;
}

int comprobarJaque(Pieza * rey, Pieza * piezas[]){
    int i;
    for (i = 0; i < 32 ; i++){
        if (!piezas[i]->M && piezas[i]->color != rey->color){
            if (legal(rey->f, rey->c, piezas[i], piezas) == 0 &&  comprobarCamino(rey->f, rey->c, piezas[i], piezas) == 0) return i;
            }
        }
    return 0;
}