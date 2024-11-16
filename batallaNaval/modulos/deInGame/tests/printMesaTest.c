#include <stdio.h>

#include "../../../header.h"


int main(void)
{
    int filas=12, cols=12;


    int ***matrizJug = crearMat3D(filas, cols, 2),
        ***matrizComp = crearMat3D(filas, cols, 2)
    ;

    //Poner barcos en matrizJug:
    matrizJug[0][0][0] = 1;
    matrizJug[0][1][0] = 1;
    matrizJug[0][2][0] = 1;
    matrizJug[0][3][0] = 1;
    matrizJug[0][4][0] = 1;

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


    //Poner barcos en matrizComp:
    matrizComp[0][0][0] = 1;
    matrizComp[1][0][0] = 1;
    matrizComp[2][0][0] = 1;
    matrizComp[3][0][0] = 1;
    matrizComp[4][0][0] = 1;

    matrizComp[5][6][0] = 1;
    matrizComp[6][6][0] = 1;
    matrizComp[7][6][0] = 1;
    matrizComp[8][6][0] = 1;
    
    matrizComp[8][2][0] = 1;
    matrizComp[8][3][0] = 1;
    matrizComp[8][4][0] = 1;

    matrizComp[1][8][0] = 1;
    matrizComp[1][9][0] = 1;

    matrizComp[10][10][0] = 1;


    printMesa(matrizJug, matrizComp, 10, 10);

    return 0;
}
















