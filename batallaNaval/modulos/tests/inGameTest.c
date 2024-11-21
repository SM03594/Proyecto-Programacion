#include <stdio.h>

#include "../../header.h"

int main(void)
{
    srand(time(NULL));

    int filas, cols, puntosVic;

    filas = 10;
    cols = 10;
    puntosVic = 1; ////
    //puntosVic = 15;

    int ***matrizJug = crearMat3D(filas, cols, 2),
        ***matrizComp = crearMat3D(filas, cols, 2)
    ;

    //-------------------------------------------

    matrizJug[0][1][0] = 1;
    matrizJug[0][2][0] = 1;
    matrizJug[0][3][0] = 1;
    matrizJug[0][4][0] = 1;
    matrizJug[0][5][0] = 1;

    matrizJug[5][1][0] = 1;
    matrizJug[6][1][0] = 1;
    matrizJug[7][1][0] = 1;
    matrizJug[8][1][0] = 1;
    
    matrizJug[9][2][0] = 1;
    matrizJug[9][3][0] = 1;
    matrizJug[9][4][0] = 1;

    matrizJug[1][8][0] = 1;
    matrizJug[1][9][0] = 1;

    matrizJug[3][7][0] = 1;

    //-------------------------------------------

    matrizComp[0][1][0] = 1;
    matrizComp[0][2][0] = 1;
    matrizComp[0][3][0] = 1;
    matrizComp[0][4][0] = 1;
    matrizComp[0][5][0] = 1;

    matrizComp[5][1][0] = 1;
    matrizComp[6][1][0] = 1;
    matrizComp[7][1][0] = 1;
    matrizComp[8][1][0] = 1;
    
    matrizComp[9][2][0] = 1;
    matrizComp[9][3][0] = 1;
    matrizComp[9][4][0] = 1;

    matrizComp[1][8][0] = 1;
    matrizComp[1][9][0] = 1;

    matrizComp[3][7][0] = 1;

    //-------------------------------------------

    inGame(matrizJug, matrizComp, puntosVic, filas, cols);
    
    return 0;
}

