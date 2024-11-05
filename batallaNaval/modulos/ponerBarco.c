#include <stdio.h>
#include "../header.h"

void ponerBarco(int matriz[10][10][2], int coordsVec[3], int longBarco)
{
    int eje, fila, col;

    eje = coordsVec[0];
    fila = coordsVec[1];
    col = coordsVec[2];

    for(int i=0; i<longBarco; i++)
    {
        if(eje == 0) //eje = 0 es horizontal, eje = 1 es vertical
        {
            matriz[fila][col+i][0] = 1;
        }
        else
        {
            matriz[fila+i][col][0] = 1;
        }
    }
}


