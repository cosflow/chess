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
int movB(char pieza, int fil, int col, Pieza * blancas[]);
int movN(char pieza, int fil, int col, Pieza * negras[]);


int main(int argc, char *argv) {

	int i,j,k;
	int fil,col;
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
				if(avancePBlancas(fil, col, blancas) == 0) turno = false;
			}
			else{
				if(avancePNegras(fil, col, negras) == 0) turno = true;
			}
			break;
			case 3: //PIEZAS y ENROQ CORTO
				if(buffer[0] == 'O' && buffer[1] == '-' && buffer[2] == buffer[0]){
					if(turno){
						if(enroqueC(blancas) == 0) turno = false;
					}
					else{
						if(enroqueC(negras) == 0) turno = true;
					}
				}
				col = (int) buffer[1] - 96;
				if(col < 1 || col > 8){
					puts("Error coordenada");
				}
				fil = buffer[2] - '0';

				if(fil < 1 || fil > 8){
					puts("Error coordenada");
				}
				if(turno){
					if(movB(buffer[0], fil, col, blancas) == 0) turno = false; 
				}
				else{
					if(movN(buffer[0], fil, col, negras) == 0) turno = true;
				}
			break;
			case 4: //CAPTURAS,PROMOCIONES, MOV COMPLEJOS, JAQUES
			break;
			case 5: //ENROQ LARGO, CAPTURAS COMPLEJAS,
			break;
			case 6: //CAPTURAS COMPLEJAS DOBLES 
		}
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

	int i;

	for (i=8 ; i < 16 ; i++){
		if(blancas[i]->columna == col){
			if(fil == blancas[i]->fila+2 && blancas[i]->movida==false){
				blancas[i]->fila +=2;
				blancas[i]->movida = true;
				break;
			}
			if (fil == blancas[i]->fila+1){
				blancas[i]->fila++;
				blancas[i]->movida = true;
				break;
			}
			else return -3;
		}
	}			
	return 0;
}

int avancePNegras(int fil, int col, Pieza * negras[]){

	int i;

	for (i=8 ; i < 16 ; i++){
		if(negras[i]->columna == col){
			if(fil == negras[i]->fila-2 && negras[i]->movida==false){
				negras[i]->fila -=2;
				negras[i]->movida = true;
				break;
			}
			if (fil == negras[i]->fila-1){
				negras[i]->fila--;
				negras[i]->movida = true;
				break;
			}
			else exit -1;
		}
	}
		
	return 0;
}

int avanceCBlancas(const char *buffer, Pieza * blancas[]){

}

int avanceCNegras(const char * buffer, Pieza * negras){

}

int enroqueC(Pieza * piezas[]){

}

int movB(char pieza, int fil, int col, Pieza * blancas[]){

	int i;
	int cdif, fdif;
	switch (pieza)
	{
	case 'A':
		for(i = 0 ; i < 2 ; i++){
			if(!blancas[3*i+4]->M && blancas[3*i+4]->inicial == 'A'){
				cdif = blancas[3*i+4]->columna - col;
				fdif = blancas[3*i+4]->fila - fil;
				if(cdif == fdif || cdif == fdif*(-1)){
					blancas[3*i+4]->fila = fil;
					blancas[3*i+4]->columna = col;
					return 0;
				}
			}
		}
		break;
	case 'C':
		for(i = 0 ; i < 2 ; i++){
			if(!blancas[3*i+3]->M && blancas[3*i+3]->inicial == 'C'){
				cdif = blancas[3*i+3]->columna - col;
				fdif = blancas[3*i+3]->fila - fil;
				fdif *=fdif;
				cdif *=cdif;
				if((fdif == 4 && cdif == 1)||(fdif == 1 && cdif == 4))
				{
					blancas[3*i+3]->fila = fil;
					blancas[3*i+3]->columna = col;
					return 0;
				}
			}
		}
		break;
	case 'T':
		for(i = 0 ; i < 2 ; i++){
			if(!blancas[3*i+2]->M && blancas[3*i+2]->inicial == 'T'){
				if((fil == blancas[3*i+2]->fila)^(col == blancas[3*i+2]->columna))
				{
					blancas[3*i+2]->fila = fil;
					blancas[3*i+2]->columna = col;
					return 0;
				}
			}
		}
		break;
	case 'D':
		break;
	case 'R':
		break;
	default:
		return -1;
		break;
	}
	return -2;
}

int movN(char pieza, int fil, int col, Pieza * negras[]){

	return 0;
}
