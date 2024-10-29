// carga.h
#ifndef CARGA_H
#define CARGA_H
struct Pieza {
	char inicial;
	bool color;
	char* codigo;
	int fila;
	char columna;
	bool M;
	bool movida;
};
typedef struct Pieza Pieza;
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

void cargar(Pieza ** tablero);

#endif