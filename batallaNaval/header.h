#ifndef HEADER_H
#define HEADER_H

//Funciones Compartidas: 
int numAleatorio(int min, int max);
int*** crearMat3D(int filas, int cols, int celdas);
void pedirDimMat(int *filas, int *cols);
void definirBarcos(int filas, int cols, int *numBarcos, int *vecBarcos, int *puntosVic);

#include "modulos/compartido/numAleatorio.c"
#include "modulos/compartido/crearMat3D.c"
#include "modulos/compartido/pedirDimMat.c"
#include "modulos/compartido/definirBarcos.c"

//de archivos:
void guardarPuntuacion(char *nombre, int movimientos);
void mostrarPuntuaciones();

#include "modulos/compartido/guardarPuntuacion.c"
#include "modulos/compartido/mostrarPuntuaciones.c"

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

//structs:
struct memoriaComp
{
    int compRacha;
    int cantPosBlancos;
    int ***vecPosBlancos;
    int ultDirTomada[2];
    int coordsUltAcierto[3]; 
    int coordsPrimerAciertoRacha[3];
};

//Funciones In Game:
void atacarMatriz(int ***matiz, int filas, int cols, int *puntaje, int turno);
void pedirCoordsAtaque(int coordsAtaque[2], int filas, int cols);
void marcarPosBlancos(int ***matriz ,int ***vecPosBlancos, int fila, int col, int *cantPosBlancos, int puntaje, int filas, int cols);
void ataqueComp(int ***matriz, int filas, int cols, int *puntaje, struct memoriaComp *memoria, int marca);
void printMesa(int ***matrizJug, int ***matrizComp, int filas, int cols);
void inGame(int ***matrizJug, int ***matrizComp, int puntosVic, int filas, int cols);


#include "modulos/deInGame/atacarMatriz.c"
#include "modulos/deInGame/pedirCoordsAtaque.c"
#include "modulos/deInGame/marcarPosBlancos.c"
#include "modulos/deInGame/ataqueComp.c"
#include "modulos/deInGame/printMesa.c"
#include "modulos/inGame.c"


//batallaNavalFunc:
void batallaNavalFunc(void);

#include "batallaNavalFunc.c"


//menu:
void menuPrincipal(void);

#include "menuPrincipal.c"



#endif

