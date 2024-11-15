#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "../../header.h"

int main(void)
{   
    srand(time(NULL));

    int numBarcos = 5, filas = 12, cols = 12;

    int vecBarcos[numBarcos],
        ***matrizJug = crearMat(filas, cols) ,
        ***matrizComp = crearMat(filas, cols)
    ;

    for(int i=0; i<numBarcos; i++)
    {
        vecBarcos[i] = numBarcos - i;
    }

    fasePosBarcos(filas, cols, numBarcos, vecBarcos, matrizJug, matrizComp);

    return 0;
}

