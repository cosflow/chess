#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "carga.h"
#include "io.h"
#include "utils.h"

int main(int argc, char ** argv) {

	int i;
	int turno = 1;
	// int jaque = 0, jaquematecontomate = 0;
	Pieza * blancas[16];
	Pieza *negras[16];

	for (i = 0; i < 16 ; i++){
		blancas[i] = (Pieza *)malloc(sizeof( struct Pieza));
		negras[i] = (Pieza *)malloc(sizeof( struct Pieza));
	}

	cargar(blancas, negras);
	bienvenida();
	imprimirTablero(blancas,negras,turno);
	
	int fil = 0, col = 0;
	int m;

	do{
		puts("Introduce la coordenadas de la pieza que quieras mover:");
		recibirCoord(&fil, &col);
		m = comprobarCasilla(fil, col, blancas, negras);
	} while (m == 0);
		
	puts("Introduce las coordenadas donde quieras colocar la pieza:");
	recibirCoord(&fil, &col);

	for(i = 0; i < 16 ; i++){
		free(blancas[i]);
		free(negras[i]);
	}
}