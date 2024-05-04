#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REYB "\xE2\x99\x9A"
#define DAMAB "\xE2\x99\x9B"
#define TORREB "\xE2\x99\x9C"
#define ALFILB "\xE2\x99\x9D"
#define CABALLOB "\xE2\x99\x9E"
#define PEONB "\xE2\x99\x9F"

#define REYN "\xE2\x99\x94"
#define DAMAN "\xE2\x99\x95"
#define TORREN "\xE2\x99\x96"
#define ALFILN "\xE2\x99\x97"
#define CABALLON "\xE2\x99\x98"
#define PEONN "\xE2\x99\x99"

#define E_ILEGAL -22
#define E_COORD -11

#define cA 1
#define cB 2
#define cC 3
#define cD 4
#define cE 5
#define cF 6
#define cG 7
#define cH 8

struct Pieza{
	char inicial;
	bool color;
	char *codigo;
	int fila;
	char columna;
	bool M;
	bool movida;
};

typedef struct Pieza Pieza;

void imprimirTablero(Pieza * blancas[], Pieza * negras[], bool turno);
void cargarTablero(Pieza * blancas[], Pieza * negras[]);
int avancePBlancas(int fil, int col, Pieza * blancas[]);
int avancePNegras(int fil, int col, Pieza * negras[]);
int enroqueC(Pieza * fichas[]);
int movP(char pieza, int fil, int col, Pieza * piezas[]);
int * comprobarCamino(int fil, int col, Pieza * movida, Pieza * blancas[], Pieza * negras[]);

int main(int argc, char *argv) {

	int i,j,k;
	int fil,col;
	int index;
	int * coord;
	bool turno = true;
	char buffer[100];
	int len;
	bool jaque = false, jaquematecontomate = false;
	Pieza * blancas[16];
	Pieza *negras[16];

	for (i = 0; i < 16 ; i++){
		blancas[i] = (Pieza *)malloc(sizeof( struct Pieza));
		negras[i] = (Pieza *)malloc(sizeof( struct Pieza));
	}

	cargarTablero(blancas, negras);

	puts("-----------------------------------------------------");
	puts("-----------------------AJEDREZ-----------------------");
	puts("-----------------------------------------------------\n\n");



	while(!jaquematecontomate){

		imprimirTablero(blancas, negras, turno);
		
		do {
			puts("Introduzca un movimiento:");
			scanf("%s", buffer);
			len = strlen(buffer);
		} while ((len < 2) || (len > 6));

		switch (len){
			case 2: //AVANCE PEONES
			col = (int) buffer[0] - 96;
			if(col < 1 || col > 8){
				puts("Error coordenada");
			}
			fil = buffer[1] - '0';

			if(fil < 1 || fil > 8){
				puts("Error coordenada");
			}
			if(turno){
				if(index = avancePBlancas(fil, col, blancas) >= 0){
					coord = comprobarCamino(fil, col, blancas[index], blancas, negras);
					if(coord != NULL){
						blancas[index]->fila = coord[0];
						blancas[index]->columna = coord[1];
						blancas[index]->movida = true;
						turno = false;
					}
				} 
			}
			else{
				if(index = avancePNegras(fil, col, negras) >= 0){
					coord = comprobarCamino(fil, col, negras[index], blancas, negras);
					if(coord != NULL){
						printf("%d", index);
						negras[index]->fila = coord[0];
						negras[index]->columna = coord[1];
						negras[index]->movida = true;
						turno = true;
					}
				} 
			}
			break;
			case 3: //PIEZAS y ENROQ CORTO
				if(buffer[0] == 'O' && buffer[1] == '-' && buffer[2] == buffer[0]){
					if(turno){
						if(enroqueC(blancas) == 0) turno = false;
						break;
					}
					else{
						if(enroqueC(negras) == 0) turno = true;
						break;
					}
				}
				col = (int) buffer[1] - 96;
				if(col < 1 || col > 8){
					puts("Error coordenada");
					break;
				}
				fil = buffer[2] - '0';

				if(fil < 1 || fil > 8){
					puts("Error coordenada");
					break;
				}
				if(turno){
					if(movP(buffer[0], fil, col, blancas) == 0) turno = false; 
				}
				else{
					if(movP(buffer[0], fil, col, negras) == 0) turno = true;
				}
			break;
			case 4: //CAPTURAS,PROMOCIONES, MOV COMPLEJOS, JAQUES
			break;
			case 5: //ENROQ LARGO, CAPTURAS COMPLEJAS,
			break;
			case 6: //CAPTURAS COMPLEJAS DOBLES 
		}

		if(blancas[0]->M || negras[0]->M) jaquematecontomate = true;
	}

	for(i = 0; i < 16 ; i++){
		free(blancas[i]);
		free(negras[i]);
	}
	return 0;
}

void cargarTablero(Pieza * blancas[], Pieza * negras[]){

	int i;

	blancas[0]->codigo = REYB;
	negras[0]->codigo = REYN;
	blancas[1]->codigo = DAMAB;
	negras[1]->codigo = DAMAN;

	blancas[0]->inicial = 'R';
	negras[0]->inicial = 'R';
	blancas[1]->inicial = 'D';
	negras[1]->inicial = 'D';

	blancas[0]->columna = cE;
	blancas[0]->fila = 1;
	blancas[0]->M =false;
	negras[0]->columna = cE;
	negras[0]->fila = 8;
	negras[0]->M = false;

	blancas[1]->columna = cD;
	negras[1]->columna = cD;
	blancas[1]->fila = 1;
	negras[1]->fila = 8;

	negras[1]->M = false;
	blancas[1]->M = false;

	for(i = 0 ; i < 2 ; i++){

		blancas[3*i+2]->codigo = TORREB;
		negras[3*i+2]->codigo = TORREN;

		blancas[3*i+3]->codigo = CABALLOB;
		negras[3*i+3]->codigo = CABALLON;

		blancas[3*i+4]->codigo = ALFILB;
		negras[3*i+4]->codigo = ALFILN;

		blancas[3*i+2]->inicial = 'T';
		negras[3*i+2]->inicial = 'T';

		blancas[3*i+3]->inicial = 'C';
		negras[3*i+3]->inicial = 'C';

		blancas[3*i+4]->inicial = 'A';
		negras[3*i+4]->inicial = 'A';

		blancas[3*i+2]->columna = 7*i+1;
		negras[3*i+2]->columna = 7*i+1;

		blancas[3*i+2]->fila = 1;
		negras[3*i+2]->fila = 8;


		blancas[3*i+3]->columna = i*5+2;
		negras[3*i+3]->columna = i*5+2;

		blancas[3*i+3]->fila = 1;
		negras[3*i+3]->fila = 8;

		blancas[3*i+4]->columna = 3 + 3*i;
		negras[3*i+4]->columna = 3 + 3*i;
		
		blancas[3*i+4]->fila = 1;
		negras[3*i+4]->fila = 8;

		blancas[3*i+2]->M = false;
		blancas[3*i+3]->M = false;
		blancas[3*i+4]->M = false;
		negras[3*i+2]->M = false;
		negras[3*i+3]->M = false;
		negras[3*i+4]->M = false;
	}
	for(i = 0 ; i < 8 ; i++){
		blancas[i+8]->codigo = PEONB;
		negras[i+8]->codigo = PEONN;
		blancas[i+8]->inicial = 'P';
		negras[i+8]->inicial = 'P';
		blancas[i+8]->columna = i+1;
		blancas[i+8]->fila = 2;
		negras[i+8]->columna = i+1;
		negras[i+8]->fila = 7;
		blancas[i+8]->M = false;
		negras[i+8]->M = false;
		blancas[i+8]->movida = false;
		negras[i+8]->movida = false;
	}
}

void imprimirTablero(Pieza *blancas[], Pieza *negras[], bool turno)
{
	int i,j,k;
	bool encontrado = false;
	if ((turno)){
		puts(" \t  -------Turno --> BLANCAS---------\n");
		for (i = 8 ; i >= 1; i--){
			puts("\t  ---------------------------------");
			printf(" \t%d | ", i);
			for(j = 1 ; j <= 8 ; j++){
				for(k = 0; k < 16; k++){
					if (blancas[k]->columna == j && blancas[k]->fila == i){
						encontrado = 1;
						printf("%s | ", blancas[k]->codigo);
						break;
					}
					if (negras[k]->columna == j && negras[k]->fila == i){
						encontrado = 1;
						printf("%s | ", negras[k]->codigo);
						break;
					}
					encontrado = 0;
				}
				if (!encontrado) printf("  | ");
			}
			puts("");
		}
		puts("\t  ---------------------------------");
		printf("\t    A   B   C   D   E   F   G   H \n\n");
	}
	else{
		puts(" \t  -------Turno --> NEGRAS----------\n");
		for (i = 1 ; i <= 8 ; i++){
			puts("\t  ---------------------------------");
			printf(" \t%d | ", i);
			for(j = 8 ; j >= 1 ; j--){
				for(k = 0; k < 16; k++){
					if (blancas[k]->columna == j && blancas[k]->fila == i){
						encontrado = 1;
						printf("%s | ", blancas[k]->codigo);
						break;
					}
					if (negras[k]->columna == j && negras[k]->fila == i){
						encontrado = 1;
						printf("%s | ", negras[k]->codigo);
						break;
					}
					encontrado = 0;
				}
				if (!encontrado) printf("  | ");

			}
			puts("");
		}
		puts("\t  ---------------------------------");
		printf("\t    H   G   F   E   D   C   B   A \n\n");

	}
}

int avancePBlancas(int fil,int col, Pieza * blancas[]){

	int i, fdif;

	for (i=8 ; i < 16 ; i++){
		if(blancas[i]->columna == col){
			fdif = fil - blancas[i]->fila;
			if (fdif < 1 || fdif > 2){
				return E_COORD;
			}
			if(fil == blancas[i]->fila+2 && blancas[i]->movida==false){
				return i;
				break;
			}
			if (fil == blancas[i]->fila+1){
				return i;
				break;
			}
			else return E_ILEGAL;
		}
	}			
	return E_COORD;
}

int avancePNegras(int fil, int col, Pieza * negras[]){

	int i, fdif;

	for (i=8 ; i < 16 ; i++){
		if(negras[i]->columna == col){
			fdif = fil - negras[i]->fila;
			if (fdif < 1 || fdif > 2){
				return E_COORD;
			}
			if(fil == negras[i]->fila-2 && negras[i]->movida==false){
				return i;
				break;
			}
			if (fil == negras[i]->fila-1){
				return i;
				break;
			}
			else return E_ILEGAL;
		}
	}			
	return E_COORD;
}

int enroqueC(Pieza * piezas[]){
	if (!piezas[0]->movida && !piezas[5]->movida){
		piezas[0]->columna = piezas[5]->columna - 1;
		piezas[5]->columna = piezas[0]->columna - 1;
	}
	return 0;
}

int movP(char pieza, int fil, int col, Pieza * piezas[]){

	int i;
	int cdif, fdif;
	switch (pieza)
	{
	case 'A':
		for(i = 0 ; i < 2 ; i++){
			if(!piezas[3*i+4]->M && piezas[3*i+4]->inicial == 'A'){
				cdif = piezas[3*i+4]->columna - col;
				fdif = piezas[3*i+4]->fila - fil;
				if(cdif == fdif || cdif == fdif*(-1)){
					piezas[3*i+4]->fila = fil;
					piezas[3*i+4]->columna = col;
					return 0;
				}
			}
		}
		return -2;
		break;
	case 'C':
		for(i = 0 ; i < 2 ; i++){
			if(!piezas[3*i+3]->M && piezas[3*i+3]->inicial == 'C'){
				cdif = piezas[3*i+3]->columna - col;
				fdif = piezas[3*i+3]->fila - fil;
				fdif *=fdif;
				cdif *=cdif;
				if((fdif == 4 && cdif == 1)||(fdif == 1 && cdif == 4))
				{
					piezas[3*i+3]->fila = fil;
					piezas[3*i+3]->columna = col;
					return 0;
				}
			}
		}
		return -2;
		break;
	case 'T':
		for(i = 0 ; i < 2 ; i++){
			if(!piezas[3*i+2]->M && piezas[3*i+2]->inicial == 'T'){
				if((fil == piezas[3*i+2]->fila)^(col == piezas[3*i+2]->columna))
				{
					piezas[3*i+2]->fila = fil;
					piezas[3*i+2]->columna = col;
					if(!piezas[3*i+2]->movida) piezas[0]->movida = true;
					return 0;
				}
			}
		}
		return -2;
		break;
	case 'D':
		if ((piezas[1]->fila == fil)^piezas[1]->columna == col){
			piezas[1]->fila = fil;
			piezas[1]->columna = col;
			return 0;
		}
		cdif = piezas[1]->columna - col;
		fdif = piezas[1]->fila - fil;
		if(cdif == fdif || cdif == fdif*(-1)){
			piezas[1]->fila = fil;
			piezas[1]->columna = col;
			return 0;
		}
		return -2;
		break;
	case 'R':
		cdif = piezas[0]->columna - col;
		fdif = piezas[0]->fila - fil;
		fdif *=fdif;
		cdif *=cdif;
		if(cdif + fdif <= 1){
			piezas[0]-> fila = fil;
			piezas[0]-> columna = col;
			return 0;
		}
		if(!piezas[0]->movida) piezas[0]->movida = true;
		return -2;
		break;
	default:
		return -1;
		break;
	}
	return -2;
}

int * comprobarCamino(int fil, int col, Pieza * movida, Pieza * blancas[], Pieza * negras[]){

	int i;
	int * coord = malloc(sizeof(int)*2);
	switch(movida->inicial){
		case 'P':
			for(i = 0 ; i < 16 ; i ++){
				if ((blancas[i]->fila == fil) && (blancas[i]->columna == col)){
					return NULL;
				}
				if ((negras[i]->fila == fil) && (negras[i]->columna == col)){
					return NULL;
				}
			}
			coord[0] = fil; coord[1] = col;
			return coord;
		break;
		case 'A':
		break;
		case 'C':
		break;
		case 'T':
		break;
		case 'D':
		break;
		case 'R':
		break;
	}

}
