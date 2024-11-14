#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//#include "testHead.h"
#include "../../../header.h"
//#include "../../deFasePosBarcos/printMatriz.c"
#include "../../compartido/crearMat.c"
#include "../atacarMatriz.c"
#include "../../fasePosBarcos.c"

#define FILAS 10
#define COLS 10

int main(void) {
    
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

    int puntosJug, puntosComp, puntosVic, turno, ronda;

    turno = 0;
    puntosVic= 5 + 4 + 3 + 2 + 1;
    puntosJug=0;
    puntosComp=0;
    ronda = 0;

    while ((puntosJug < puntosVic) || (puntosComp < puntosVic))
    {
        printf("---------------------------------------------------------\n");
        printf("---------------------------------------------------------\n");

        printf("ronda: %d \n\n", ronda);

        printMatriz(matrizJug, FILAS, COLS);

        printf("\n\n");

        printMatriz(matrizComp, FILAS, COLS);

        printf("\n\n");

        if(turno==0)
        {
            atacarMatriz(matrizComp, FILAS, COLS, &puntosJug, turno);
            turno = 1;
        }
        else
        {
            atacarMatriz(matrizJug, FILAS, COLS, &puntosComp, turno);
            turno = 0;
        }

        ronda+=1;
    }   
    

    return 0;
}


    


