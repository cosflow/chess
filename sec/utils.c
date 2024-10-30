#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int comprobarCasilla(int x, int y, Pieza * blancas[], Pieza * negras[]){
    int i;

    for (i = 0 ; i < 16 ; i++){
        if(blancas[i]->x == x && blancas[i]->y == y && !blancas[i]->M) return i;
        if(negras[i]->x == x && negras[i]->y == y && !negras[i]->M) return i;
    }
    return 0;
}

int legal(int xdes, int ydes, Pieza * p){
    int fdif = xdes - p->x;
	int cdif = ydes - p->y;
    switch((toupper(p->inicial))){
        case 'P':
            if(fdif != 0) return -1;
            if(p->color && fdif <= 1) return -1;
            if(!p->color && fdif >= 1) return -1;
            if(!p->movida){
                if(abs(fdif) < 1 || abs(fdif) > 2) return -1;
            }
            if(p->movida && fdif != 1) return -1;
        break;
        case 'A':
            if(abs(fdif) != abs(cdif)) return -1;
        break;
        case 'C':
            if(abs(fdif * cdif)!= 2) return -1;
        break;
        case 'T':
            if(cdif != 0 && fdif != 0) return -1;
            if(cdif == 0 && fdif == 0) return -1;
        break;
        case 'D':
            if(abs(cdif) != abs(fdif)){
                if(cdif != 0 && fdif != 0) return -1;
                if(cdif == 0 && fdif == 0) return -1;
            }
        break;
        case 'R':
            if(cdif * fdif != 0 && abs(cdif) * abs(fdif) != 1) return -1;
        break;
    }
    return 0;
}

int comprobarCamino(int xdes, int ydes, Pieza * p, Pieza * blancas[], Pieza * negras[]){
    int i;
    int fdif = xdes - p->x;
	int cdif = ydes - p->y;
    switch((toupper(p->inicial))){
        case 'P':
            for(i = 1; i <= fdif; i++){
                if (comprobarCasilla(xdes, (ydes+i), blancas, negras) != 0) return -1;
            }
        break;
        case 'A':
            int diag = abs(fdif);
            int vx = fdif / abs(fdif);
            int vy = cdif / abs(cdif);
            for (i = 1; i <= diag; i++){
                if (comprobarCasilla(xdes+i*vx, ydes+i*vy, blancas, negras) != 0) return -1;
            }
        break;
        case 'C':
            if (comprobarCasilla(xdes, ydes, blancas, negras) != 0) return -1;
        break;
        case 'T':
            if(cdif != 0){
                int vy = cdif / abs(cdif);
                for (i = 1; i <= abs(cdif); i++){
                    if (comprobarCasilla(xdes, ydes+i*vy, blancas, negras) != 0) return -1;
                }
            }
            else{
                int vx = fdif / abs(fdif);
                for (i = 1; i <= abs(fdif); i++){
                    if (comprobarCasilla(xdes+i*vx, ydes, blancas, negras) != 0) return -1;
                }
            }
        break;
        case 'D':
            if(cdif != 0 && fdif == 0){
                int vy = cdif / abs(cdif);
                for (i = 1; i <= abs(cdif); i++){
                    if (comprobarCasilla(xdes, ydes+i*vy, blancas, negras) != 0) return -1;
                }
            }
            else if (cdif == 0 && fdif== 0) {
                int vx = fdif / abs(fdif);
                for (i = 1; i <= abs(fdif); i++){
                    if (comprobarCasilla(xdes+i*vx, ydes, blancas, negras) != 0) return -1;
                }
            }
            else {
                int diag = abs(fdif);
                int vx = fdif / abs(fdif);
                int vy = cdif / abs(cdif);
                for (i = 1; i <= diag; i++){
                    if (comprobarCasilla(xdes+i*vx, ydes+i*vy, blancas, negras) != 0) return -1;
                }
            }
        break;
        case 'R':
            if (comprobarCasilla(xdes, ydes, blancas, negras) != 0) return -1;
        break;
    }
    return 0;
}
