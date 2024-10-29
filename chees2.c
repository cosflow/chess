#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "carga.h"


int main(int argc, char *argv) {

	int i,j,k;
	int fil,col;
	int index;
	bool turno = true;
	char buffer[100];
	int len;
	bool jaque = false, jaquematecontomate = false;

	Pieza ** tablero[8][8];
	for(i = 0; i < 8 ; i++){
		for(j = 0; j < 8 ; j++){
			tablero[i][j] = (Pieza *)malloc(sizeof( struct Pieza));
		}
	}
}