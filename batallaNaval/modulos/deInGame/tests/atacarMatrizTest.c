#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "../../../header.h"

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

    while ((puntosJug < puntosVic) && (puntosComp < puntosVic))
    {
        printf("---------------------------------------------------------\n");
        printf("---------------------------------------------------------\n");

        printf("ronda: %d \n\n", ronda);

        printMatriz(matrizJug, filas, cols);

        printf("\n\n");

        printMatriz(matrizComp, filas, cols);

        printf("\n\n");

        if(turno==0)
        {
            atacarMatriz(matrizComp, filas, cols, &puntosJug, turno);
            turno = 1;
        }
        else
        {
            atacarMatriz(matrizJug, filas, cols, &puntosComp, turno);
            turno = 0;
        }

        ronda+=1;
    }   

    printf("\n\n");

    printf("ronda: %d \n", ronda);
    printf("puntosJug: %d \n", puntosJug);
    printf("puntosComp: %d \n\n", puntosComp);

    printMatriz(matrizJug, filas, cols);

    printf("\n\n");

    printMatriz(matrizComp, filas, cols);

    printf("\n\n");
    
    if(puntosJug == puntosVic)
    {
        printf("\n\n VICTORIA ");
    }
    else
    {
        printf("\n\n DERROTA ");
    }
    
    return 0;
}


    


