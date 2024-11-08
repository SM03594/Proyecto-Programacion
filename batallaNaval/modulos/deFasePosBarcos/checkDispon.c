#include <stdio.h>
#include "../../header.h"

int checkDisp(int ***matriz, int coordsVec[3], int longBarco, int jugador)
{
    int eje, fila, col, celdaOcupacion, disponible;

    eje = coordsVec[0];
 	fila = coordsVec[1];
 	col = coordsVec[2];

    disponible = 1;

    for(int i=0; i < longBarco; i++)
    {
        if(eje==0)
        {
            celdaOcupacion = matriz[fila][col+i][0];
        }   
        else
        {
            celdaOcupacion = matriz[fila+i][col][0];
        }

        if(celdaOcupacion==1)
        {
            disponible = 0;

            if(jugador==1)
            {
                if(eje==0)
                {
                    printf("ERROR: celda en fila: %d, col: %d esta ocupada. \n", fila, col+i);
                }
                else
                {
                    printf("ERROR: celda en fila: %d, col: %d esta ocupada. \n", fila+i, col);
                }
            }
        }          
    }

    return disponible;
}


