#ifndef HEADER_H
#define HEADER_H

//Funciones Fase de Posicionamiento:
void printMatriz(int matriz[10][10][2]);
void ponerBarco(int matriz[10][10][2], int coordsVec[3], int longBarco);
int checkDisp(int matriz[10][10][2], int coordsVec[3], int longBarco, int jugador);
int posEnRango(int coordsVec[3], int longBarco, int longitud, int jugador);
void pedirCoords(int coordsVec[3], int longMatriz);

//----------------------------------------------------------------------------------

//Funciones In Game:


#endif