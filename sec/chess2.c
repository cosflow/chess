#include <stdio.h>
#include "data.h"
#include "carga.h"
#include "io.h"

int main(int argc, char *argv) {

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
	imprimirTablero(blancas,negras,turno);
}