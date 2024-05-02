#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

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
};

typedef struct Pieza Pieza;

int main(int argc, char *argv) {

	int i,j,k;
	char *move;
	int fil, col;
	bool jaque, jaquematecontomate;
	int encontrado = 0;
	Pieza blancas[16];
	Pieza negras[16];

	int cont = 0;
	blancas[0].codigo = REYB;
	negras[0].codigo = REYN;
	blancas[1].codigo = DAMAB;
	negras[1].codigo = DAMAN;

	blancas[0].inicial = 'R';
	negras[0].inicial = 'R';
	blancas[1].inicial = 'D';
	negras[1].inicial = 'D';

	blancas[0].columna = cE;
	blancas[0].fila = 1;
	negras[0].columna = cE;
	negras[0].fila = 8;
	negras[0].M = false;
	blancas[0].M =false;

	blancas[1].columna = cD;
	negras[1].columna = cD;
	blancas[1].fila = 1;
	negras[1].fila = 8;

	negras[1].M = false;
	blancas[1].M = false;

	for(i = 0 ; i < 2 ; i++){

		blancas[3*i+2].codigo = TORREB;
		negras[3*i+2].codigo = TORREN;

		blancas[3*i+3].codigo = CABALLOB;
		negras[3*i+3].codigo = CABALLON;

		blancas[3*i+4].codigo = ALFILB;
		negras[3*i+4].codigo = ALFILN;

		blancas[3*i+2].inicial = 'T';
		negras[3*i+2].inicial = 'T';

		blancas[3*i+3].inicial = 'C';
		negras[3*i+3].inicial = 'C';

		blancas[3*i+4].inicial = 'A';
		negras[3*i+4].inicial = 'A';

		blancas[3*i+2].columna = 7*i+1;
		negras[3*i+2].columna = 7*i+1;

		blancas[3*i+2].fila = 1;
		negras[3*i+2].fila = 8;


		blancas[3*i+3].columna = i*5+2;
		negras[3*i+3].columna = i*5+2;

		blancas[3*i+3].fila = 1;
		negras[3*i+3].fila = 8;

		blancas[3*i+4].columna = 3 + 3*i;
		negras[3*i+4].columna = 3 + 3*i;
		
		blancas[3*i+4].fila = 1;
		negras[3*i+4].fila = 8;

		blancas[3*i+2].M = false;
		blancas[3*i+3].M = false;
		blancas[3*i+4].M = false;
		negras[3*i+2].M = false;
		negras[3*i+3].M = false;
		negras[3*i+4].M = false;
	}

	for(i = 0 ; i < 8 ; i++){
		blancas[i+8].codigo = PEONB;
		negras[i+8].codigo = PEONN;
		blancas[i+8].inicial = 'P';
		negras[i+8].inicial = 'P';
		blancas[i+8].columna = i+1;
		blancas[i+8].fila = 2;
		negras[i+8].columna = i+1;
		negras[i+8].fila = 7;
		blancas[i+8].M = false;
		negras[i+8].M = false;
	}

	puts("----------------------------------------");
	puts("----------------AJEDREZ-----------------");
	puts("----------------------------------------\n\n");



	puts("Juegan BLANCAS");

	for (i = 8 ; i >= 1; i--){
		puts("\t  -----------------");
		printf(" \t%d |", i);
		for(j = 1 ; j <= 8 ; j++){
			for(k = 0; k < 16; k++){
				if (blancas[k].columna == j && blancas[k].fila == i){
					encontrado = 1;
					printf("%s|", blancas[k].codigo);
					break;
				}
				if (negras[k].columna == j && negras[k].fila == i){
					encontrado = 1;
					printf("%s|", negras[k].codigo);
					break;
				}
				encontrado = 0;
			}
			if (!encontrado) printf(" |");
		}
		puts("");

	}
	  puts("\t  -----------------");
	printf("\t   A B C D E F G H\n");

	puts("");

	scanf("Jugador blanco, introduzca un movimiento: %s", &move);

	return 0;
}