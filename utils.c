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
        if(piezas[i]->M == 0){
            // printf("%d", i);
            if(piezas[i]->c == x && piezas[i]->f == y) return i;
        }
    }
    return -1;
}

int legal(int ydes, int xdes, Pieza * p, Pieza * piezas[]){
    int fdif = ydes - p->f;
	int cdif = xdes - p->c;
    switch(toupper(p->inicial)){
        case 'P':
            if(fdif == 0) return -1;
            if(cdif != 0) {
                if(abs(cdif) == 1){
                    if(comprobarCasilla(xdes, ydes, piezas) == -1) return -1;
                }
                else return -1;
            }
            if(abs(fdif) < 1) return -1;
            if(!p->movida){
                if(abs(fdif) != 1 && abs(fdif) != 2) return -1;
            }
            if(p->movida && abs(fdif) != 1) return -1;
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
    int i, m;
    int fdif = ydes - p->f;
	int cdif = xdes - p->c;
    if(fdif == 0 && cdif == 0) return -1;
    switch((toupper(p->inicial))){
        case 'P':
            switch(p->color){
                case 1:
                if (abs(fdif) == abs(cdif) && abs(fdif == 1)){
                    m = comprobarCasilla(xdes, ydes, piezas);
                    if (m != -1) {
                        if(piezas[m]->M == 0) {    
                            if(piezas[m]->color == p->color) {
                                puts("NOJIAEFIOAMKWF");
                                return -1;
                            }
                        }
                    }
                    //falta codear AL PASO
                }
                else{
                    for(i = 1; i <= fdif; i++){
                        if (comprobarCasilla(p->c, p->f+i, piezas) != -1) return -1;
                    }
                }
                break;
                case 0:
                if (abs(fdif) == abs(cdif) && abs(fdif == 1)){
                    m = comprobarCasilla(xdes, ydes, piezas);
                    if (m != -1) {
                        if(piezas[m]->M == 0) {    
                            if(piezas[m]->color == p->color) return -1;
                        }
                    }
                    //falta codear AL PASO
                }
                else{
                    for(i = 1; i <= abs(fdif); i++){
                        if (comprobarCasilla(p->c, p->f-i, piezas) != -1) return -1;
                    }
                }
                break;
            }
        break;
        case 'A':
            int diag = abs(fdif);
            int vx = cdif / abs(cdif);
            int vy = fdif / abs(fdif);
            for (i = 1; i <= diag; i++){
                m = comprobarCasilla(p->c+i*vx, p->f+i*vy, piezas);
                if (m != -1) {
                    if(i != diag) return -1;
                    if(piezas[m]->M == 0) {    
                        if(piezas[m]->color == p->color) return -1;
                    }
                }
            }
        break;
        case 'C':
            m = comprobarCasilla(xdes, ydes, piezas);
            if (m != -1) {
                if(piezas[m]->M == 0) {    
                    if(piezas[m]->color == p->color) return -1;
                }
            }
        break;
        case 'T':
            if(fdif != 0){
                int vy = fdif / abs(fdif);
                for (i = 1; i <= abs(fdif); i++){
                    m = comprobarCasilla(p->c, p->f+i*vy, piezas);
                    if (m != -1) {
                        if (i != abs(fdif)) return -1;
                        else {
                            if(piezas[m]->M == 0) {    
                                if(piezas[m]->color == p->color) return -1;
                            }
                        }
                    }
                }
            }
            else{
                int vx = cdif / abs(cdif);
                for (i = 1; i <= abs(cdif); i++){
                    m = comprobarCasilla(p->c+i*vx, p->f, piezas);
                    if (m != -1) {
                        if (i != abs(cdif)) return -1;
                        else {
                            if(piezas[m]->M == 0) {    
                                if(piezas[m]->color == p->color) return -1;
                            }
                        }
                    }
                }
            }
        break;
        case 'D':
            if(fdif != 0 && cdif == 0){
                int vy = fdif / abs(fdif);
                for (i = 1; i <= abs(fdif); i++){
                    m = comprobarCasilla(p->c, p->f+i*vy, piezas);
                    if (m != -1) {
                        if (i != abs(fdif)) return -1;
                        else {
                            if(piezas[m]->M == 0) {    
                                if(piezas[m]->color == p->color) return -1;
                            }
                        }
                    }
                }
            }
            else if (cdif != 0 && fdif== 0) {
                int vx = cdif / abs(cdif);
                for (i = 1; i <= abs(cdif); i++){
                    m = comprobarCasilla(p->c+i*vx, p->f, piezas);
                    if (m != -1) {
                        if (i != abs(cdif)) return -1;
                        else {
                            if(piezas[m]->M == 0) {    
                                if(piezas[m]->color == p->color) return -1;
                            }
                        }
                    }
                }
            }
            else if (abs(cdif) == abs(fdif)){
                int diag = abs(fdif);
                int vx = cdif / abs(cdif);
                int vy = fdif / abs(fdif);
                for (i = 1; i <= diag; i++){
                    m = comprobarCasilla(p->c+i*vx, p->f+i*vy, piezas);
                    if (m != -1) {
                        if(i != diag) return -1;
                        else {
                            if(piezas[m]->M == 0) {    
                                if(piezas[m]->color == p->color) return -1;
                            }
                        }
                    }
                }
            }
        break;
        case 'R':
            if (comprobarCasilla(p->c, p->f, piezas) != -1) return -1;
        break;
    }
    return 0;
}
