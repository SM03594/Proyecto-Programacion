#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "../../../header.h"


int main(void)
{
    srand(time(NULL));

    int filas, cols, puntosVic;

    filas = 10;
    cols = 10;
    puntosVic = 15;

    int ***matriz = crearMat3D(filas, cols, 2);

    //----------------------------------------------------

    //Poner barcos:
    
    matriz[1][0][0] = 1;
    matriz[1][1][0] = 1;
    matriz[1][2][0] = 1;
    matriz[1][3][0] = 1;
    matriz[1][4][0] = 1;
    matriz[1][5][0] = 1;
    matriz[1][6][0] = 1;
    matriz[1][7][0] = 1;
    matriz[1][8][0] = 1;
    matriz[1][9][0] = 1;

    matriz[3][0][0] = 1;
    matriz[3][1][0] = 1;
    matriz[3][2][0] = 1;
    matriz[3][3][0] = 1;
    matriz[3][4][0] = 1;
    matriz[3][5][0] = 1;
    matriz[3][6][0] = 1;
    matriz[3][7][0] = 1;
    matriz[3][8][0] = 1;
    matriz[3][9][0] = 1;
    
    matriz[5][1][0] = 1;
    matriz[6][1][0] = 1;
    matriz[7][1][0] = 1;
    matriz[8][1][0] = 1;
    matriz[9][1][0] = 1;

    matriz[5][5][0] = 1;
    matriz[6][5][0] = 1;
    matriz[7][5][0] = 1;
    matriz[8][5][0] = 1;
    matriz[9][5][0] = 1;

    matriz[5][8][0] = 1;
    matriz[6][8][0] = 1;
    matriz[7][8][0] = 1;
    matriz[8][8][0] = 1;
    matriz[9][8][0] = 1;

    // matriz[5][1][0] = 1;
    // matriz[6][1][0] = 1;
    // matriz[7][1][0] = 1;
    // matriz[8][1][0] = 1;

    
    // matriz[9][2][0] = 1;
    // matriz[9][3][0] = 1;
    // matriz[9][4][0] = 1;

    // matriz[1][8][0] = 1;
    // matriz[1][9][0] = 1;

    // matriz[3][7][0] = 1;

    
    //----------------------------------------------------
    //Marcar posiciones como atacadas:

    // matriz[9][2][1] = 1;
    // matriz[9][3][1] = 1;
    // matriz[9][4][1] = 1;

    //al rededor de (5; 5)
    // matriz[4][5][1] = 1;
    // matriz[5][4][1] = 1;
    // matriz[5][6][1] = 1;
    // matriz[6][5][1] = 1;

    //al rededor de (0; 9)
    // matriz[0][8][1] = 1;
    // matriz[1][9][1] = 1;

    //ariva de (9;5)
    // matriz[8][5][1] = 1;

    //derecha de (9;0)
    // matriz[9][1][1] = 1;


    //----------------------------------------------------
    //----------------------------------------------------
    //----------------------------------------------------
    //----------------------------------------------------


    int ronda, continuar, puntaje;

    ronda = 0;
    continuar = 1;
    puntaje = 0;

    struct memoriaComp memoria;
    memoria.compRacha = 0;
    memoria.cantPosBlancos = 0;
    memoria.vecPosBlancos = crearMat3D(100, 4, 3); ////////////
    

    while (continuar != 0)
    {
        if(ronda == 0)
        {
            printf("*********************************\n\n");
            printf("ESTADO INICIAL: \n\n");

            printMatriz(matriz, filas, cols);
            
            ronda+=1;
        }
        else
        {
            printf("\n\n*********************************\n\n");
            printf("RONDA %d: \n\n", ronda);

            printf("---------------\n");

            printf("Puntaje: %d \n", puntaje);
            printf("compRacha: %d \n", memoria.compRacha);
            printf("cantPosBlancos: %d \n", memoria.cantPosBlancos);
            //printf("vecPosBlancos: ")
            if(puntaje > 0)
            {
                printf("ultDirTomada: %d en %d puntos \n", memoria.ultDirTomada[0], memoria.ultDirTomada[1]);
                printf("coordsUltAcierto: (%d, %d) en %d puntos \n",memoria.coordsUltAcierto[0], memoria.coordsUltAcierto[1], memoria.coordsUltAcierto[2]+1);
                printf("coordsPrimerAciertoRacha: (%d, %d) hace %d rondas \n", memoria.coordsPrimerAciertoRacha[0], memoria.coordsPrimerAciertoRacha[1], memoria.coordsPrimerAciertoRacha[2]+1);
            }

            printf("---------------\n");

            ataqueComp(matriz, filas, cols, &puntaje, &memoria, ronda+1); ///////////////////////////////////////

            abc(matriz, filas, cols);

            ronda+=1;

            printf("\n\nCONTINUAR? ");
            scanf("%d", &continuar);
        }
    }
}

//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------

void abc(int ***matriz, int filas, int cols)
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
                    if(matriz[i][x][1] > 1)
                    {
                        printf("+%d", matriz[i][x][1]);
                    }
                    else
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
                }
                else //si no hay barco
                {
                    if(matriz[i][x][1] > 1)
                    {
                        printf("-%d", matriz[i][x][1]);
                    }
                    else
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

