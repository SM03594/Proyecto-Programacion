#ifndef HEADER_H
#define HEADER_H

//Funciones Fase de Posicionamiento:
void printMatriz(int matriz[10][10][2]);
void ponerBarco(int matriz[10][10][2], int coordsVec[3], int longBarco);
int checkDisp(int matriz[10][10][2], int coordsVec[3], int longBarco, int jugador);
int posEnRango(int coordsVec[3], int longBarco, int longitud, int jugador);
void pedirCoords(int coordsVec[3], int longMatriz);
char* darNombreBarco(int longBarco);
void fasePosBarcos(int longMatriz, int numBarcos, int vecBarcos[5], int matrizJug[10][10][2], int matrizComp[10][10][2]);

//----------------------------------------------------------------------------------

//Funciones In Game:


//----------------------------------------------------------------------------------

//Funciones Compartidas: 
int numAleatorio(int min, int max);


#endif