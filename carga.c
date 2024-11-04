#include "carga.h"
#include <stdio.h>
#include <stdlib.h>

void cargar(Pieza * piezas[]){
	int i;
	
	piezas[0]->codigo = REYB;
	piezas[16]->codigo = REYN;
	piezas[1]->codigo = DAMAB;
	piezas[17]->codigo = DAMAN;
	piezas[0]->inicial = 'R';
	piezas[0+16]->inicial = 'r';
	piezas[1]->inicial = 'D';
	piezas[1+16]->inicial = 'd';

	piezas[0]->c = 5;
	piezas[0]->f = 1;
	piezas[16]->c = 5;
	piezas[16]->f = 8;
	piezas[1]->c = 4;
	piezas[17]->c = 4;
	piezas[1]->f = 1;
	piezas[17]->f = 8;

	for(i = 0 ; i < 2 ; i++){
		piezas[3*i+2]->codigo = TORREB;
		piezas[3*i+2+16]->codigo = TORREN;
		piezas[3*i+3]->codigo = CABALLOB;
		piezas[3*i+3+16]->codigo = CABALLON;
		piezas[3*i+4]->codigo = ALFILB;
		piezas[3*i+4+16]->codigo = ALFILN;
		piezas[3*i+2]->inicial = 'T';
		piezas[3*i+2+16]->inicial = 't';
		piezas[3*i+3]->inicial = 'C';
		piezas[3*i+3+16]->inicial = 'c';
		piezas[3*i+4]->inicial = 'A';
		piezas[3*i+4+16]->inicial = 'a';
		piezas[3*i+2]->c = 7*i+1;
		piezas[3*i+2+16]->c = 7*i+1;
		piezas[3*i+2]->f = 1;
		piezas[3*i+2+16]->f = 8;
		piezas[3*i+3]->c = i*5+2;
		piezas[3*i+3+16]->c = i*5+2;
		piezas[3*i+3]->f = 1;
		piezas[3*i+3+16]->f = 8;
		piezas[3*i+4]->c = 3 + 3*i;
		piezas[3*i+4+16]->c = 3 + 3*i;
		piezas[3*i+4]->f = 1;
		piezas[3*i+4+16]->f = 8;
	}

	for(i = 0 ; i < 8 ; i++){
		piezas[i+8]->codigo = PEONB;
		piezas[i+8+16]->codigo = PEONN;
		piezas[i+8]->inicial = 'P';
		piezas[i+8+16]->inicial = 'p';
		piezas[i+8]->c = i+1;
		piezas[i+8]->f = 2;
		piezas[i+8+16]->c = i+1;
		piezas[i+8+16]->f = 7;
    }
    for (i = 0; i < 32 ; i++){
		piezas[i]->M = 0;
		piezas[i]->movida = 0;
        if(i<16) piezas[i]->color = 1;
		else piezas[i]->color = 0;
		if (i > 0){
			piezas[i]->ant = piezas[i-1];
		}
		if(i<31){
			piezas[i]->sig = piezas[i+1];
		}
    }
}
