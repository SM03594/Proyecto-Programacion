#include <stdio.h>

#include "../../header.h"

void pedirDimMat(int *filas, int *cols)
{
    int valido, dimension, limMax, limMin;
    float inputValido, dimensionAux;
    char auxChar[5];

    limMax = 20;
    limMin = 5;

    valido = 0;

    while (valido==0)
    {
        printf("Ingrese la dimension de la matriz de %d a %d: ", limMin, limMax);
        inputValido = scanf("%f", &dimensionAux);

        if(inputValido == 1)
        {
            dimension = dimensionAux;

            if((dimension >= limMin) && (dimension <= limMax))
            {
                valido = 1;
                *filas = dimension;
                *cols = dimension;
            }
            else
            {
                printf("ERROR: dimension fuera de rango \n\n");
            }
        }
        else
        {
            printf("\nERROR: esa opcion no existe \n");
        }

        while (getchar() != '\n'); //limpiar buffer de entrada   
    }
}

