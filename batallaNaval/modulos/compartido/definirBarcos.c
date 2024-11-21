#include <stdio.h>
#include <math.h>

#include "../../header.h"


void definirBarcos(int filas, int cols, int *numBarcos, int *vecBarcos, int *puntosVic)
{
    int longBarcoActual, contVuelta;
    int totalCeldas = ceil((filas * cols)/6);
    
    contVuelta = 5;

    while (*puntosVic != totalCeldas)
    {
        if(contVuelta <= (totalCeldas - *puntosVic))
        {
            vecBarcos[*numBarcos] = contVuelta;
            *numBarcos += 1;
            *puntosVic += contVuelta;
        }

        if(contVuelta > 1)
            contVuelta -=1;
        else
            contVuelta = 5;
        ;
    }
}





