#ifndef HEADER_H
#define HEADER_H

//Funciones Fase de Posicionamiento:
void printMatriz(int ***matriz, int filas, int cols);
void ponerBarco(int ***matriz, int coordsVec[3], int longBarco);
int checkDisp(int ***matriz, int coordsVec[3], int longBarco, int jugador);
int posEnRango(int coordsVec[3], int longBarco, int filas, int cols, int jugador);
void pedirCoords(int coordsVec[3], int filas, int cols);
char* darNombreBarco(int longBarco);
void fasePosBarcos(int filas, int cols, int numBarcos, int vecBarcos[5], int ***matrizJug, int ***matrizComp);

//----------------------------------------------------------------------------------

//Funciones In Game:


//----------------------------------------------------------------------------------

//Funciones Compartidas: 
int numAleatorio(int min, int max);
int*** crearMat(int filas, int cols);


#endif