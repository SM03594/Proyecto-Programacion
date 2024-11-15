#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "../../header.h"

int main(void)
{   
    srand(time(NULL));

    int numBarcos = 5, filas = 12, cols = 12, celdas = 3;

    int vecBarcos[numBarcos],
        ***matrizJug = crearMat3D(filas, cols, celdas) ,
        ***matrizComp = crearMat3D(filas, cols, celdas)
    ;

    for(int i=0; i<numBarcos; i++)
    {
        vecBarcos[i] = numBarcos - i;
    }

    fasePosBarcos(filas, cols, numBarcos, vecBarcos, matrizJug, matrizComp);

    return 0;
}

