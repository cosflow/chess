#include "utils.h"

int comprobarCasilla(int x, int y, Pieza * blancas[], Pieza * negras[]){
    int i;

    for (i = 0 ; i < 16 ; i++){
        if(blancas[i]->x == x && blancas[i]->y == y && !blancas[i]->M) return i;
        if(negras[i]->x == x && negras[i]->y == y && !negras[i]->M) return i;
    }
    return 0;
}
