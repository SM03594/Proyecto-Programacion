#include <stdio.h>
#include "../../header.h"
//#include "pedirCoordsAtaque.c"


void atacarMatriz(int ***matiz, int filas, int cols, int *puntaje, int turno)
{
    int fila, col, coordsAtaque[2], posPrevAtacada, celdaAtaqueStatus, hayBarco;

    posPrevAtacada = 1;

    while (posPrevAtacada==1)
    {
        if(turno==0) //turno == 0 es turno del jugador
        {
            printf("\nIngrese las coordenadas de ataque \n");

            pedirCoordsAtaque(coordsAtaque, filas, cols);

            fila = coordsAtaque[0];
 			col = coordsAtaque[1];
        }
        else //turno de computadora
        {
            fila = numAleatorio(0, filas-1);
            col = numAleatorio(0, cols-1);
        }

        celdaAtaqueStatus = matiz[fila][col][1];

        if(celdaAtaqueStatus==0)
        {
            posPrevAtacada = 0;

            matiz[fila][col][1] = 1; //marcar atque en matriz

            hayBarco = matiz[fila][col][0]; // sera 1 si hay barco y 0 si no lo hay

            if(hayBarco==1)
            {
                (*puntaje)+=1;
            }

            printf("\n");
        }
        else
        {
            printf("\nERROR: la celda ubicada en ( %d, %d ) ya fue atacada \n", fila, col);
        }
    }
}

