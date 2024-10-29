#include "carga.h"
#include <stdio.h>

void cargar(Pieza * blancas[], Pieza * negras[]){
    
	int i;

	blancas[0]->codigo = REYB;
	negras[0]->codigo = REYN;
	blancas[1]->codigo = DAMAB;
	negras[1]->codigo = DAMAN;

	blancas[0]->y = 5;
	blancas[0]->x = 1;
	blancas[0]->M =0;
	negras[0]->y = 5;
	negras[0]->x = 8;
	negras[0]->M = 0;

	blancas[1]->y = 4;
	negras[1]->y = 4;
	blancas[1]->x = 1;
	negras[1]->x = 8;

	negras[1]->M = 0;
	blancas[1]->M = 0;

	for(i = 0 ; i < 2 ; i++){

		blancas[3*i+2]->codigo = TORREB;
		negras[3*i+2]->codigo = TORREN;

		blancas[3*i+3]->codigo = CABALLOB;
		negras[3*i+3]->codigo = CABALLON;

		blancas[3*i+4]->codigo = ALFILB;
		negras[3*i+4]->codigo = ALFILN;

		blancas[3*i+2]->y = 7*i+1;
		negras[3*i+2]->y = 7*i+1;

		blancas[3*i+2]->x = 1;
		negras[3*i+2]->x = 8;


		blancas[3*i+3]->y = i*5+2;
		negras[3*i+3]->y = i*5+2;

		blancas[3*i+3]->x = 1;
		negras[3*i+3]->x = 8;

		blancas[3*i+4]->y = 3 + 3*i;
		negras[3*i+4]->y = 3 + 3*i;
		
		blancas[3*i+4]->x = 1;
		negras[3*i+4]->x = 8;

		blancas[3*i+2]->M = 0;
		blancas[3*i+3]->M = 0;
		blancas[3*i+4]->M = 0;
		negras[3*i+2]->M = 0;
		negras[3*i+3]->M = 0;
		negras[3*i+4]->M = 0;
	}
	for(i = 0 ; i < 8 ; i++){
		blancas[i+8]->codigo = PEONB;
		negras[i+8]->codigo = PEONN;
		blancas[i+8]->y = i+1;
		blancas[i+8]->x = 2;
		negras[i+8]->y = i+1;
		negras[i+8]->x = 7;
		blancas[i+8]->M = 0;
		negras[i+8]->M = 0;
		blancas[i+8]->movida = 0;
		negras[i+8]->movida = 0;
    }
    for (i = 0; i < 16 ; i++){
        blancas[i]->color = 1;
        negras[i]->color = 0;  
    }
}
