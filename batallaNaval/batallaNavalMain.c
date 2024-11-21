#include <stdio.h>

#include "header.h"


int main(void)
{
    srand(time(NULL));

    int filas, cols, celdas;

    //filas = 10;
    //cols = 10;

    pedirDimMat(&filas, &cols);
    celdas = 2;


    int ***matrizJug = crearMat3D(filas, cols, celdas),
        ***matrizComp = crearMat3D(filas, cols, celdas)
    ;

    int numBarcos, puntosVic;

    numBarcos = 5;

    int vecBarcos[numBarcos];

    for(int i=0; i<numBarcos; i++)
    {
        vecBarcos[i] = numBarcos - i;
        puntosVic+= numBarcos-i;
    }


    fasePosBarcos(filas, cols, numBarcos, vecBarcos, matrizJug, matrizComp);

    inGame(matrizJug, matrizComp, puntosVic, filas, cols);

    return 0; 
}

