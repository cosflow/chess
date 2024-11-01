#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"
#include "carga.h"
#include "io.h"
#include "utils.h"
#include "dyn.h"

int main(int argc, char ** argv) {

	int i;
	int turno = 1;
	// int jaque = 0, jaquematecontomate = 0;
	Pieza * piezas[32];
	
	for (i = 0; i < 32 ; i++){
		piezas[i] = (Pieza *)malloc(sizeof(struct Pieza));
	}
	cargar(piezas);
	bienvenida();
	imprimirTablero(piezas,turno);
	
	int fil = 0, col = 0, salir = 0;
	int m;

	while(1){
		salir = 0;
		do{
			puts("Introduce la coordenadas de la pieza que quieras mover:");
			recibirCoord(&fil, &col);
			m = comprobarCasilla(col, fil, piezas);
			if (m!=-1){
				if(turno == piezas[m]->color) salir = 1;
				else printf("Escoge una pieza de tu color.\n");
			}
			else salir = 0;
			// printf("%d %d", piezas[m]->x, piezas[m]->y);
		} while (salir == 0);

		salir = 0;
		do{
			printf("Introduce las coordenadas donde quieras colocar ");
			switch(toupper(piezas[m]->inicial)){
				case 'P': puts("el peón:"); break;
				case 'A': puts("el alfil:"); break;
				case 'C': puts("el caballo:"); break;
				case 'T': puts("la torre:"); break;
				case 'D': puts("la dama:"); break;
				case 'R': puts("el rey:"); break;
			}
			recibirCoord(&fil, &col);
			// printf("%d %d", fil, col);
			if(legal(fil, col, piezas [m], piezas) != -1){
				if(comprobarCamino(fil, col, piezas[m], piezas) == 0) salir = 1;
				else printf("Camino bloquiado.\n");
			}
			else printf("Movimiento ilegal.\n");
			// printf("%d %d", piezas[m]->x, piezas[m]->y);
		} while (salir == 0);
		mover(fil, col, piezas[m]);
		turno = cambiarTurno(turno);
		imprimirTablero(piezas, turno);
	}

	for(i = 0; i < 32 ; i++){
		free(piezas[i]);
	}
}