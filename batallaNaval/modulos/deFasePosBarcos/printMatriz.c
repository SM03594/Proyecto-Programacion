#include <stdio.h>
#include "../../header.h"

void printMatriz(int ***matriz, int filas, int cols)
{
    int i, x, j;

    for(i=-1; i<=filas-1; i++)
    {
        if(i==-1)
        {
            printf("  ");

            if(filas > 10)
            {
                printf(" "); //hacer un espacio para compesar el tamaño del digito extra
            }

            for(j=0; j<cols; j++) //indicar indices de columnas
            {
                printf(" %d", j);

                if((cols > 10) && (j < 10))
                {
                    printf(" "); //hacer un espacio para compesar el tamaño del digito extra
                }
            }
            printf("\n");
        }
        else
        {
            if((filas > 10) && (i < 10))
            {
                printf(" "); //hacer un espacio para compesar el tamaño del digito extra
            }

            printf("%d ", i); //indicar indices de filas

            for(x=0; x<cols; x++)
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

                if(cols > 10)
                {
                    printf(" "); //hacer un espacio para compesar el tamaño del digito extra
                }
            }
            printf("\n"); //para romper linea
        }
    }
    printf("\n");
}

