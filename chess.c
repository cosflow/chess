#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

#define E_ILEGAL -222
#define E_COORD -111
#define CASILLAVACIA ' '

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

void imprimirTablero(char *tablero[], bool turno);
void cargarTablero(Pieza * blancas[], Pieza * negras[]);
int avancePBlancas(int fil, int col, Pieza * blancas[]);
int avancePNegras(int fil, int col, Pieza * negras[]);
int enroqueC(Pieza * fichas[]);
int movimientoPieza(char pieza, int fil, int col, Pieza * piezas[]);
int comprobarCamino(int fil, int col, Pieza * movida, char * tablero[], bool turno);
void confirmarMovimiento(int fil, int col, char * tablero[], Pieza * movida);

int main(int argc, char *argv) {

	int i,j,k;
	int fil,col;
	int index;
	bool turno = true;
	char buffer[100];
	int len;
	bool jaque = false, jaquematecontomate = false;
	Pieza * blancas[16];
	Pieza *negras[16];

	char * tablero[8];

	for (i = 0; i < 16 ; i++){
		blancas[i] = (Pieza *)malloc(sizeof( struct Pieza));
		negras[i] = (Pieza *)malloc(sizeof( struct Pieza));
	}

	for(i = 0 ; i < 8 ; i++){
		tablero[i] = (char *)malloc(sizeof(char)*8);
	}

	cargarTablero(blancas, negras);

	for (i = 0 ; i < 8 ; i++){
		for (j = 0 ; j < 8 ; j++){
			tablero[i][j] = CASILLAVACIA;
		}
	}
	for (i = 0 ; i < 16 ; i++){

		tablero[blancas[i]->fila-1][blancas[i]->columna-1] = blancas[i]->inicial;
		tablero[negras[i]->fila-1][negras[i]->columna-1] = negras[i]->inicial;
	}

	puts("-----------------------------------------------------");
	puts("-----------------------AJEDREZ-----------------------");
	puts("-----------------------------------------------------\n\n");



	while(!jaquematecontomate){

		imprimirTablero(tablero, turno);
		
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
				if (turno) index = avancePBlancas(fil, col, blancas);
				else index = avancePNegras(fil, col, negras);
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
				}
				if(turno) index = movimientoPieza(buffer[0], fil, col,blancas);
				else index = movimientoPieza(buffer[0], fil, col,negras);
			break;
			case 4: //CAPTURAS,PROMOCIONES, MOV COMPLEJOS, JAQUES
			break;
			case 5: //ENROQ LARGO, CAPTURAS COMPLEJAS,
			break;
			case 6: //CAPTURAS COMPLEJAS DOBLES 
		}
		if(index>=0){
			if(turno){
				if(comprobarCamino(fil, col, blancas[index], tablero, turno) != E_ILEGAL){
					confirmarMovimiento(fil, col, tablero, blancas[index]);
					turno = false;
				}
			} 
			else{
				if(comprobarCamino(fil, col, negras[index], tablero, turno) != E_ILEGAL){
					confirmarMovimiento(fil, col, tablero, negras[index]);
					turno = true;
				}
			}
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
	negras[0]->inicial = 'r';
	blancas[1]->inicial = 'D';
	negras[1]->inicial = 'd';

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
		negras[3*i+2]->inicial = 't';

		blancas[3*i+3]->inicial = 'C';
		negras[3*i+3]->inicial = 'c';

		blancas[3*i+4]->inicial = 'A';
		negras[3*i+4]->inicial = 'a';

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
		negras[i+8]->inicial = 'p';
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

void imprimirTablero(char * tablero[], bool turno)
{
	int i,j;
	if ((turno)){
		puts(" \t  -------Turno --> BLANCAS---------\n");
		for (i = 7 ; i >= 0; i--){
			puts("\t  ---------------------------------");
			printf(" \t%d | ", i+1);
			for(j = 0 ; j < 8 ; j++){
				switch(tablero[i][j]){
					case 'P':
						printf("%s | ", PEONB);
						break;
					case 'p':
						printf("%s | ", PEONN);
						break;
					case 'T':
						printf("%s | ", TORREB);
						break;
					case 't':
						printf("%s | ", TORREN);
						break;
					case 'C':
						printf("%s | ", CABALLOB);
						break;
					case 'c':
						printf("%s | ", CABALLON);
						break;
					case 'A':
						printf("%s | ", ALFILB);
						break;
					case 'a':
						printf("%s | ", ALFILN);
						break;
					case 'D':
						printf("%s | ", DAMAB);
						break;
					case 'd':
						printf("%s | ", DAMAN);
						break;
					case 'R':
						printf("%s | ", REYB);
						break;
					case 'r':
						printf("%s | ", REYN);
						break;
					default:
						printf("  | ");
						break;
				}
			}
			puts("");
		}
		puts("\t  ---------------------------------");
		printf("\t    A   B   C   D   E   F   G   H \n\n");
	}
	else{
		puts(" \t  -------Turno --> NEGRAS----------\n");
		for (i = 0 ; i < 8 ; i++){
			puts("\t  ---------------------------------");
			printf(" \t%d | ", i+1);
			for(j = 7 ; j >= 0 ; j--){
				switch(tablero[i][j]){
					case 'P':
						printf("%s | ", PEONB);
						break;
					case 'p':
						printf("%s | ", PEONN);
						break;
					case 'T':
						printf("%s | ", TORREB);
						break;
					case 't':
						printf("%s | ", TORREN);
						break;
					case 'C':
						printf("%s | ", CABALLOB);
						break;
					case 'c':
						printf("%s | ", CABALLON);
						break;
					case 'A':
						printf("%s | ", ALFILB);
						break;
					case 'a':
						printf("%s | ", ALFILN);
						break;
					case 'D':
						printf("%s | ", DAMAB);
						break;
					case 'd':
						printf("%s | ", DAMAN);
						break;
					case 'R':
						printf("%s | ", REYB);
						break;
					case 'r':
						printf("%s | ", REYN);
						break;
					default:
						printf("  | ");
						break;
				}
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
			if(fdif == 2 && blancas[i]->movida==false){
				return i;
				break;
			}
			if (fdif == 1){
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
			fdif = negras[i]->fila -fil; 

			if (fdif < 1 || fdif > 2){
				return E_COORD;
			}
			if(fdif == 2 && negras[i]->movida==false){
				return i;
				break;
			}
			if (fdif == 1){
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

int movimientoPieza(char pieza, int fil, int col, Pieza * piezas[]){

	int i;
	int cdif, fdif;
	switch (toupper(pieza))
	{
	case 'A':
		for(i = 0 ; i < 2 ; i++){
			if(!piezas[3*i+4]->M){
				cdif = piezas[3*i+4]->columna - col;
				fdif = piezas[3*i+4]->fila - fil;
				if(cdif == fdif || cdif == fdif*(-1)){
					if(cdif = 0) return E_COORD;
					return (3*i+4);
				}
			}
		}
		return E_ILEGAL;
		break;
	case 'C':
		for(i = 0 ; i < 2 ; i++){
			if(!piezas[3*i+3]->M){
				cdif = piezas[3*i+3]->columna - col;
				fdif = piezas[3*i+3]->fila - fil;
				fdif *=fdif;
				cdif *=cdif;
				if((fdif == 4 && cdif == 1)||(fdif == 1 && cdif == 4))
				{
					return (3*i+3);
				}
			}
		}
		return E_ILEGAL;
		break;
	case 'T':
		for(i = 0 ; i < 2 ; i++){
			if(!piezas[3*i+2]->M){
				if((fil == piezas[3*i+2]->fila)^(col == piezas[3*i+2]->columna))
				{
					if(!piezas[3*i+2]->movida) piezas[0]->movida = true;
					return (3*i+2);
				}
			}
		}
		return E_ILEGAL;
		break;
	case 'D':
		if ((piezas[1]->fila == fil)^piezas[1]->columna == col){
			return 1;
		}
		cdif = piezas[1]->columna - col;
		fdif = piezas[1]->fila - fil;
		fdif *=fdif;
		cdif *=cdif;
		
		if((cdif == fdif || (cdif > 0 && fdif == 0) || (fdif > 0 && cdif == 0))){
			return 1;
		}
		return E_ILEGAL;
		break;
	case 'R':
		cdif = piezas[0]->columna - col;
		fdif = piezas[0]->fila - fil;
		fdif *=fdif;
		cdif *=cdif;
		if(cdif + fdif <= 1){
			return 0;
		}
		return E_ILEGAL;
		break;
	default:
		return E_COORD;
		break;
	}
	return E_COORD;
}

int comprobarCamino(int fil, int col, Pieza * movida, char * tablero[], bool turno){

	int i, j, fdif, cdif;

	// printf("\n%d, %d --> %d, %d\n", movida->fila, movida->columna, fil,col);
	fdif = fil - movida->fila;
	cdif = col - movida->columna;

	// printf("fdif->%d\ncdif->%d", fdif, cdif);
	switch(toupper(movida->inicial)){
		case 'P':
			if (tablero[movida->fila-1+fdif][movida->columna-1] != CASILLAVACIA)
			{
				return E_ILEGAL;
			}
			else return 0;

		break;
		case 'A':
			if (fdif > 0 && cdif > 0){
				j = movida->columna-1 +1;
				for(i = movida->fila-1 +1 ; i <= movida->fila+fdif -1; i++){
					if (tablero[i][j] != CASILLAVACIA){
						return E_ILEGAL;
					}
					j++;
				}
			}
			else if (fdif < 0 && cdif > 0){
				j = movida->columna-1 +1;
				for(i = movida->fila-1 -1 ; i >= movida->fila+fdif -1; i--){
					if (tablero[i][j] != CASILLAVACIA){
						return E_ILEGAL;
					}
					j++;
				}
			}
			else if (fdif > 0 && cdif < 0){
				j = movida->columna-1 -1;
				for(i = movida->fila-1 +1 ; i <= movida->fila+fdif -1; i++){
					if (tablero[i][j] != CASILLAVACIA){
						return E_ILEGAL;
					}
					j--;
				}
			}
			else{
				j = movida->columna-1 -1;
				for(i = movida->fila-1 -1 ; i >= movida->fila+fdif -1; i--){
					printf("\n%d, %d", i, j);
					if (tablero[i][j] != CASILLAVACIA){
						printf("%c", tablero[i][j]);
						return E_ILEGAL;
					}
					j--;
				}
			}
			return 0;
		break;
		case 'C':
			if (tablero[fil-1][col-1] != CASILLAVACIA)
			{
				return E_ILEGAL;
			}
			else return 0;
		break;
		case 'T':
			if (fdif == 0 && cdif < 0){

				for (i = movida->columna-1; i >= col -1 ; i--){
					if (tablero[fil-1][i] != CASILLAVACIA){
						return E_ILEGAL;
					}
				}
			}
			if (fdif == 0 && cdif > 0){

				for (i = movida->columna-1; i <= col -1 ; i++){
					if (tablero[fil-1][i] != CASILLAVACIA){
						return E_ILEGAL;
					}
				}
			}

			if (fdif < 0 && cdif == 0){

				for (i = movida->fila-1; i >= fil -1 ; i--){
					if (tablero[i][col-1] != CASILLAVACIA){
						return E_ILEGAL;
					}
				}
			}
			if (fdif > 0 && cdif == 0){

				for (i = movida->fila-1; i <= fil -1 ; i++){
					if (tablero[i][col-1] != CASILLAVACIA){
						return E_ILEGAL;
					}
				}
			}
		break;
		case 'D':
			if (fdif > 0 && cdif > 0){
				j = movida->columna-1 +1;
				for(i = movida->fila-1 +1 ; i <= movida->fila+fdif -1; i++){
					if (tablero[i][j] != CASILLAVACIA){
						return E_ILEGAL;
					}
					j++;
				}
			}
			else if (fdif < 0 && cdif > 0){
				j = movida->columna-1 +1;
				for(i = movida->fila-1 -1 ; i >= movida->fila+fdif -1; i--){
					if (tablero[i][j] != CASILLAVACIA){
						return E_ILEGAL;
					}
					j++;
				}
			}
			else if (fdif > 0 && cdif < 0){
				j = movida->columna-1 -1;
				for(i = movida->fila-1 +1 ; i <= movida->fila+fdif -1; i++){
					if (tablero[i][j] != CASILLAVACIA){
						return E_ILEGAL;
					}
					j--;
				}
			}
			else if (fdif == 0 && cdif < 0){

				for (i = movida->columna-1; i >= col -1 ; i--){
					if (tablero[fil-1][i] != CASILLAVACIA){
						return E_ILEGAL;
					}
				}
			}
			else if (fdif == 0 && cdif > 0){

				for (i = movida->columna-1; i <= col -1 ; i++){
					if (tablero[fil-1][i] != CASILLAVACIA){
						return E_ILEGAL;
					}
				}
			}

			else if (fdif < 0 && cdif == 0){

				for (i = movida->fila-1; i >= fil -1 ; i--){
					if (tablero[i][col-1] != CASILLAVACIA){
						return E_ILEGAL;
					}
				}
			}

			else if (fdif > 0 && cdif == 0){

				for (i = movida->fila-1; i <= fil -1 ; i++){
					if (tablero[i][col-1] != CASILLAVACIA){
						return E_ILEGAL;
					}
				}
			}
			else {
				j = movida->columna-1 -1;
				for(i = movida->fila-1 -1 ; i >= movida->fila+fdif -1; i--){
					if (tablero[i][j] != CASILLAVACIA){
						return E_ILEGAL;
					}
					j--;
				}
			}
			return 0;
		break;
		case 'R':
			if (tablero[fil-1][col-1] != CASILLAVACIA)
			{
				return E_ILEGAL;
			}
			else return 0;
		break;
	}

}

void confirmarMovimiento(int fil, int col, char * tablero[], Pieza * movida){
	tablero[movida->fila-1][movida->columna-1] = CASILLAVACIA;
	movida->fila = fil;
	movida->columna = col;
	tablero[movida->fila-1][movida->columna-1] = movida->inicial;
	movida->movida = true;
}