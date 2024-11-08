#include <stdio.h>
#include "../header.h"
#include "deFasePosBarcos/darNombreBarco.c"
#include "deFasePosBarcos/posEnRango.c"
#include "deFasePosBarcos/pedirCoords.c"
#include "deFasePosBarcos/checkDispon.c"
#include "deFasePosBarcos/ponerBarco.c"
#include "deFasePosBarcos/printMatriz.c"
#include "compartido/numAleatorio.c"


void fasePosBarcos(int filas, int cols, int numBarcos, int vecBarcos[5], int ***matrizJug, int ***matrizComp)
{
    int coords[3], validezCoords, enRango, longBarcoActual, disponible;
    char* nombreBarco;

    for(int i=0; i<numBarcos; i++) //cilo de posicionamiento de barcos del jugador
    {
        if(i==0)
        {
            printMatriz(matrizJug, filas, cols);
        }

        longBarcoActual = vecBarcos[i];
        nombreBarco = darNombreBarco(longBarcoActual);
        validezCoords = 0;

        while (validezCoords==0)
        {
            printf("Barco a posicionar: %s, de %d celdas de longitud \n", nombreBarco,  longBarcoActual);
            
            pedirCoords(coords, filas, cols);
            printf("\n");

            enRango = posEnRango(coords, longBarcoActual, filas, cols, 1);

            if(enRango==1)
            {
                disponible = checkDisp(matrizJug, coords, longBarcoActual, 1);

                if(disponible==1)
                {
                    ponerBarco(matrizJug, coords, longBarcoActual);
                    validezCoords = 1;
                }
            }
        }

        printMatriz(matrizJug, filas, cols);
    }

    printf("//-----------------------------------------------------\n");
    printf("//-----------------------------------------------------\n\n");

    for(int x=0; x<numBarcos; x++)
    {
        if(x==0)
        {
            printMatriz(matrizComp, filas, cols);
        }

        longBarcoActual = vecBarcos[x];
        validezCoords = 0;

        while (validezCoords==0)
        {
            coords[0] = numAleatorio(0, 1);
            coords[1] = numAleatorio(0, 9);
            coords[2] = numAleatorio(0, 9);

            enRango = posEnRango(coords, longBarcoActual, filas, cols, 1);

            if(enRango==1)
            {
                disponible = checkDisp(matrizComp, coords, longBarcoActual, 1);

                if(disponible==1)
                {
                    ponerBarco(matrizComp, coords, longBarcoActual);
                    validezCoords = 1;
                }
            }
        }

        printMatriz(matrizComp, filas, cols); 
    }
}

