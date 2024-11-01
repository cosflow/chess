#include "io.h"
#include <stdio.h>
#include <ctype.h>

void bienvenida(){
	puts("-----------------------------------------------------");
	puts("-----------------------AJEDREZ-----------------------");
	puts("-----------------------------------------------------\n\n");
}
void recibirCoord(int * fil, int * col)
{
	int salir = 0;
	int fila;
	char columna;
	puts("-----------------------------------------------------");
	while(salir==0){
		printf("Primero la columna -> ");
		scanf(" %c", &columna);
		columna = toupper(columna);
		while (columna < 'A' || columna > 'H') {
			printf("Letras válidas, de la A a la H -> ");
			scanf(" %c", &columna);
			columna = toupper(columna);
		}
		printf("Ahora, la fila -> ");
		scanf("%d", &fila);
		while (fila < 1 || fila > 8)		{
			printf("Números válidos, del 1 al 8 -> ");
			scanf("%d", &fila);
		}
		printf("Las coordenadas introducidas son: %c%d. ¿Estás conforme (1) o quieres repetir(0)?\n", columna, fila);
		scanf("%d", &salir);
		puts("-----------------------------------------------------");
	}
	*fil= fila;
	*col= columna-'A'+1;
}

void imprimirTablero(Pieza * piezas[], int turno)
{
	int i,j;
    char * tablero[8][8];
    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            tablero[i][j] = " \0";
        }
    }

    for (i = 0; i < 32; i++){
        if(!piezas[i]->M) tablero[piezas[i]->f-1][piezas[i]->c-1] = piezas[i]->codigo;
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
