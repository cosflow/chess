#include "io.h"
#include <stdio.h>

void bienvenida(){
	puts("-----------------------------------------------------");
	puts("-----------------------AJEDREZ-----------------------");
	puts("-----------------------------------------------------\n\n");
}
int recibirCoord(int * fil, int * col)
{
	int salir = 0;
	puts("-----------------------------------------------------\n\n");
	while(!salir){
		printf("Primero la fila -> ");
		scanf("%d", fil);
		puts("");
		while (fil < 1 || fil > 8)		{
			printf("Números válidos, del 1 al 8 -> ");
			scanf("%d", fil);
			puts("");
		}
		printf("Ahora, la columna -> ");
		scanf("%d", col);
		while (col < 1 || col > 8){
			printf("Números válidos, del 1 al 8 -> ");
			scanf("%d", col);
			puts("");
		}
		printf("Las coordenadas introducidas son: %d, %d. ¿Estás conforme (1) o quieres repetir(0)?");
		puts("-----------------------------------------------------\n\n");
		scanf("%d", &salir);
	}
	fil-= 1;
	col-= 1;
}

void imprimirTablero(Pieza * blancas[], Pieza * negras[], int turno)
{
	int i,j;
    char * tablero[8][8];
    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            tablero[i][j] = ' \0';
        }
    }

    for (i = 0; i < 16; i++){
        tablero[blancas[i]->x-1][blancas[i]->y-1] = blancas[i]->codigo;
        tablero[negras[i]->x-1][negras[i]->y-1] = negras[i]->codigo;
    }

	if ((turno)){
		puts(" \t  -------Turno --> BLANCAS---------\n");
		for (i = 7 ; i >= 0; i--){
			puts("\t  ---------------------------------");
			printf(" \t%d | ", i+1);
			for(j = 0 ; j < 8 ; j++){
                printf("%s | ", tablero[i][j]);
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
				printf("%s | ", tablero[i][j]);
			}
			puts("");
		}
		puts("\t  ---------------------------------");
		printf("\t    H   G   F   E   D   C   B   A \n\n");

	}
}
