#include <stdio.h>
#include "../../header.h"

int posEnRango(int coordsVec[3], int longBarco, int longitud, int jugador)
{
    int eje, fila, col, valido, puntoPartida;

    eje = coordsVec[0];
 	fila = coordsVec[1];
 	col = coordsVec[2];
    valido = 1;

    if(eje==0) //eje==0 es eje de posicionamiento horizontal
    {
        puntoPartida = col;
    }
    else
    {
        puntoPartida = fila;
    }

    if((puntoPartida + longBarco - 1) >= longitud)
    {
        valido = 0;

        if(jugador == 1)
        {
            printf("ERROR: posicionamiento fuera de rango. \n\n");
        }
    }

    return valido;
}

