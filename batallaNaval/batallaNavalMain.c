#include <stdio.h>

#include "header.h"


int main(void)
{
    srand(time(NULL));

    int filas, cols, celdas;

    pedirDimMat(&filas, &cols);
    celdas = 2;

    int ***matrizJug = crearMat3D(filas, cols, celdas),
        ***matrizComp = crearMat3D(filas, cols, celdas)
    ;

    int numBarcos, puntosVic, vecBarcos[70];

    puntosVic = 0;
    numBarcos = 0;

    definirBarcos(filas, cols, &numBarcos, vecBarcos, &puntosVic);

    fasePosBarcos(filas, cols, numBarcos, vecBarcos, matrizJug, matrizComp);

    inGame(matrizJug, matrizComp, puntosVic, filas, cols);

    return 0; 
}

