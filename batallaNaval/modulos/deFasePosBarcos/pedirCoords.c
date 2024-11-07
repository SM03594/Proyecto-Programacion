#include <stdio.h>
#include "../../header.h"

void pedirCoords(int coordsVec[3], int longMatriz)
{
    int eje, fila, col, valido;
    float ejeAux, filaAux, colAux;
    char chAux;

    valido = 0;

    while (valido==0)
    {
        printf("Ingrese el Eje de Posicionamiento: 0- horizontal  1- vertical \n");
        chAux = scanf("%f", &ejeAux);

        eje = ejeAux;

        if(chAux==1) 
        {
            if(((eje==0)||(eje==1))&&(eje==ejeAux))
            {
                valido=1;
                coordsVec[0]=eje;
            }
        }

        while (getchar() != '\n');

        if(valido==0)
        {
            printf("\nERROR: esa opcion no existe \n");
        }
    }

    valido = 0;

    while (valido==0)
    {
        printf("Ingrese la fila de 0 a %d \n", longMatriz-1);
        chAux = scanf("%f", &filaAux);

        fila = filaAux;

        if((chAux==1)&&(fila==filaAux)) 
        {
            if((fila>=0)&&(fila<=longMatriz-1))
            {
                valido=1;
                coordsVec[1]=fila;
            }
            else
            {
                printf("\nERROR: fila fuera de rango\n");
            }    
        }
        else
        {
            printf("\nERROR: el valor ingresado no es un numero entero\n\n");
        }

        while (getchar() != '\n');

    }

    valido = 0;

    while (valido==0)
    {
        printf("Ingrese la columna de 0 a %d \n", longMatriz-1);
        chAux = scanf("%f", &colAux);

        col = colAux;

        if((chAux==1)&&(col==colAux)) 
        {
            if((col>=0)&&(col<=longMatriz-1))
            {
                valido=1;
                coordsVec[2]=col;
            }
            else
            {
                printf("\nERROR: columna fuera de rango\n");
            }    
        }
        else
        {
            printf("\nERROR: el valor ingresado no es un numero entero\n\n");
        }

        while (getchar() != '\n');

    }
}
