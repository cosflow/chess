#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int cambiarTurno(int turno){
    if (turno) return 0;
    else return 1;
}

int comprobarCasilla(int x, int y, Pieza * piezas[]){
    int i;
    for (i = 0 ; i < 32 ; i++){
        if(!piezas[i]->M){
            // printf("%d", i);
            if(piezas[i]->c == x && piezas[i]->f == y) return i;
        }
    }
    return -1;
}

int legal(int ydes, int xdes, Pieza * p){
    int fdif = ydes - p->f;
	int cdif = xdes - p->c;
    switch(toupper(p->inicial)){
        case 'P':
            if(fdif == 0) return -1;
            if(cdif != 0) return -1;
            if(p->color && fdif < 1) return -1;
            if(!p->color && fdif > -1) return -1;
            if(!p->movida){
                if(abs(fdif) != 1 && abs(fdif) != 2) return -1;
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

int comprobarCamino(int ydes, int xdes, Pieza * p, Pieza * piezas[]){
    int i;
    int fdif = ydes - p->f;
	int cdif = xdes - p->c;
    switch((toupper(p->inicial))){
        case 'P':
            switch(p->color){
                case 1:
                for(i = 1; i <= fdif; i++){
                    if (comprobarCasilla(p->c, p->f+i, piezas) != -1) return -1;
                }
                break;
                case 0:
                for(i = 1; i <= abs(fdif); i++){
                    if (comprobarCasilla(p->c, p->f-i, piezas) != -1) return -1;
                }
                break;
            }
        break;
        case 'A':
            int diag = abs(fdif);
            int vx = cdif / abs(cdif);
            int vy = fdif / abs(fdif);
            for (i = 1; i <= diag; i++){
                if (comprobarCasilla(p->c+i*vx, p->f+i*vy, piezas) != -1) return -1;
            }
        break;
        case 'C':
            if (comprobarCasilla(p->c, p->f, piezas) != -1) return -1;
        break;
        case 'T':
            if(cdif != 0){
                int vy = cdif / abs(cdif);
                for (i = 1; i <= abs(cdif); i++){
                    if (comprobarCasilla(p->c, p->f+i*vy, piezas) != -1) return -1;
                }
            }
            else{
                int vx = fdif / abs(fdif);
                for (i = 1; i <= abs(fdif); i++){
                    if (comprobarCasilla(p->c+i*vx, p->f, piezas) != -1) return -1;
                }
            }
        break;
        case 'D':
            if(fdif != 0 && cdif == 0){
                int vy = fdif / abs(fdif);
                for (i = 1; i <= abs(fdif); i++){
                    if (comprobarCasilla(p->c, p->f+i*vy, piezas) != -1) return -1;
                }
            }
            else if (cdif != 0 && fdif== 0) {
                int vx = cdif / abs(cdif);
                for (i = 1; i <= abs(cdif); i++){
                    if (comprobarCasilla(p->c+i*vx, p->f, piezas) != -1) return -1;
                }
            }
            else if (abs(cdif) == abs(fdif)){
                int diag = abs(fdif);
                int vx = cdif / abs(cdif);
                int vy = fdif / abs(fdif);
                for (i = 1; i <= diag; i++){
                    if (comprobarCasilla(p->c+i*vx, p->f+i*vy, piezas) != -1) return -1;
                }
            }
        break;
        case 'R':
            if (comprobarCasilla(p->c, p->f, piezas) != -1) return -1;
        break;
    }
    return 0;
}
