#include <stdio.h>
#include "../../header.h"

void printMatriz(int matriz[10][10][2])
{
    int longitud, i, x, j;
    longitud = 10;

    for(i=-1; i<=longitud-1; i++)
    {
        if(i==-1)
        {
            printf("  ");
            
            for(j=0; j<longitud; j++) //indicar indices de columnas
            {
                printf(" %d", j);
            }
            printf("\n");
        }
        else
        {
            printf("%d ", i); //indicar indices de filas

            for(x=0; x<longitud; x++)
            {
                if(matriz[i][x][0]==1) //si hay barco
                {
                    if(matriz[i][x][1]==1)
                    {
                        printf(" X"); //X si hay un barco y la celda fue atacada
                    }
                    else
                    {
                        printf(" #"); //# si hay un barco y la celda no fue atacada
                    }
                }
                else //si no hay barco
                {
                    if(matriz[i][x][1]==1)
                    {
                        printf(" &"); //& si agua y la celda fue atacada
                    }
                    else
                    {
                        printf(" O"); //O si agua y la celda no fue atacada
                    }
                }
            }
            printf("\n"); //para romper linea
        }
    }
}

