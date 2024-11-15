#ifndef HEADER_H
#define HEADER_H

//Funciones Compartidas: 
int numAleatorio(int min, int max);
int*** crearMat(int filas, int cols);

#include "modulos/compartido/numAleatorio.c"
#include "modulos/compartido/crearMat.c"

//----------------------------------------------------------------------------------

//Funciones Fase de Posicionamiento:
void printMatriz(int ***matriz, int filas, int cols);
void ponerBarco(int ***matriz, int coordsVec[3], int longBarco);
int checkDisp(int ***matriz, int coordsVec[3], int longBarco, int jugador);
int posEnRango(int coordsVec[3], int longBarco, int filas, int cols, int jugador);
void pedirCoords(int coordsVec[3], int filas, int cols);
char* darNombreBarco(int longBarco);
void fasePosBarcos(int filas, int cols, int numBarcos, int vecBarcos[5], int ***matrizJug, int ***matrizComp);

#include "modulos/deFasePosBarcos/printMatriz.c"
#include "modulos/deFasePosBarcos/ponerBarco.c"
#include "modulos/deFasePosBarcos/checkDisp.c"
#include "modulos/deFasePosBarcos/posEnRango.c"
#include "modulos/deFasePosBarcos/pedirCoords.c"
#include "modulos/deFasePosBarcos/darNombreBarco.c"
#include "modulos/fasePosBarcos.c"

//----------------------------------------------------------------------------------

//Funciones In Game:
void atacarMatriz(int ***matiz, int filas, int cols, int *puntaje, int turno);
void pedirCoordsAtaque(int coordsAtaque[2], int filas, int cols);

#include "modulos/deInGame/atacarMatriz.c"
#include "modulos/deInGame/pedirCoordsAtaque.c"








#endif

