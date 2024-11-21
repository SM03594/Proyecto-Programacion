#include <stdio.h>
#include "../../header.h"

void pedirCoordsAtaque(int coordsAtaque[2], int filas, int cols)
{
    int valido, fila, col;
    float inputValido, filaAux, colAux;
    char auxChar[5];

    valido = 0;

    while (valido==0)
    {
        printf("Ingrese la fila de 0 a %d: ", filas-1);
        inputValido = scanf("%f", &filaAux);

        if(inputValido == 1)
        {
            fila = filaAux;

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
        else
        {
            printf("\nERROR: esa opcion no existe \n");
        }

        while (getchar() != '\n'); //limpiar buffer de entrada   
    }
    
    valido = 0;

    while (valido==0)
    {
        printf("Ingrese la columna de 0 a %d: ", cols-1);
        inputValido = scanf("%f", &colAux);

        if(inputValido == 1)
        {
            col = colAux;

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
        else
        {
            printf("\nERROR: esa opcion no existe \n");
        }

        while (getchar() != '\n'); //limpiar buffer de entrada 
    }
}

