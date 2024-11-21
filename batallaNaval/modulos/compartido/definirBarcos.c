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
        printf("\n\n || contVuelta: %d, totalCeldas: %d, *puntosVic: %d|| \n\n", contVuelta, totalCeldas, *puntosVic);

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

        printf("\n\n ## contVuelta: %d, totalCeldas: %d, *puntosVic: %d, vecBarcos[*numBarcos]: %d ## \n\n", contVuelta, totalCeldas, *puntosVic, vecBarcos[*numBarcos-1]);
    }
}





