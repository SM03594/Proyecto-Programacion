#include <stdio.h>
#include "../../header.h"

void pedirCoordsAtaque(int coordsAtaque[2], int filas, int cols)
{
    int valido, fila, col, esEntero;
    char auxChar[5];

    valido = 0;

    while (valido==0)
    {
        printf("Ingrese la fila de 0 a %d: ", filas-1);
        //scanf("%s", auxChar);
        scanf("%d", &fila);

        //esEntero = verificarSiEntero(auxChar);

        if((fila >= 0) && (fila <= filas-1))
        {
            valido = 1;
            coordsAtaque[0] = fila;
        }
        else
        {
            printf("ERROR: fila fuera de rango \n\n");
        }
    }
    
    valido = 0;

    while (valido==0)
    {
        printf("\nIngrese la columna de 0 a %d: ", cols-1);
        //scanf("%s", auxChar);
        scanf("%d", &col);

        //esEntero = verificarSiEntero(auxChar);

        if((col >= 0) && (col <= cols-1))
        {
            valido = 1;
            coordsAtaque[1] = col;
        }
        else
        {
            printf("ERROR: columna fuera de rango \n\n");
        }
    }
}

