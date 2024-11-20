#include <stdio.h>
#include "../../header.h"

void apuntarEnRacha0(int *fila, int *col , int filas, int cols)
{
    *fila = numAleatorio(0, filas-1);
    *col = numAleatorio(0, cols-1);
}

void apuntarEnRacha1(int *fila, int *col, int *direc, int puntaje, int cantPosBlancos, int ***vecPosBlancos)
{
    int random = numAleatorio(0, cantPosBlancos-1);
    int indPuntaje = puntaje-1;

    *fila = vecPosBlancos[indPuntaje][random][0];
    *col = vecPosBlancos[indPuntaje][random][1];
    *direc = vecPosBlancos[indPuntaje][random][2];
}

void apuntarEnRachaMayorA1(int *fila, int *col, int *direc, int puntaje, int *cantPosBlancos, int ***vecPosBlancos, int ultDirTomada, int *ataqueValido)
{
    int indPuntaje = puntaje-1;
    int direcAux;

    printf("\n\n-----apuntarEnRachaMayorA1-----\n\n");

    for(int i=0; i<*cantPosBlancos; i++) //
    {
        direcAux = vecPosBlancos[indPuntaje][i][2];

        printf(" i: %d, direcAux: %d, ultDirTomada: %d, indPuntaje: %d, vecPosBlancos: %d, cantPosBlancos: %d \n\n", i, direcAux, ultDirTomada, indPuntaje, vecPosBlancos[indPuntaje][i][2], *cantPosBlancos);

        if(direcAux == ultDirTomada)
        {
            *fila = vecPosBlancos[indPuntaje][i][0];
            *col = vecPosBlancos[indPuntaje][i][1];
            *direc = vecPosBlancos[indPuntaje][i][2];
            *ataqueValido = 1;
            i = *cantPosBlancos;

            printf("i %d: fila: %d, col: %d, direc: %d, ataqueValido: %d,  \n", i, *fila, *col, *direc, *ataqueValido);

            printf("ººººººººººººººººººººººººººº\n");

        }
    }
}

void apuntarEnRachaNegativa(int *fila, int *col, int *ataqueValido, int *direc, int filas, int cols, int ***matriz, int puntaje, int *cantPosBlancos, int ***vecPosBlancos, int *coordsUltAcierto)
{
    int cont, filaAux, colAux, direcAux, celdaPrevAtacada, indPuntaje, random, flag;

    indPuntaje = puntaje-1;

    printf("\n\n-----apuntarEnRachaNegativa-----\n\n");

    filaAux = coordsUltAcierto[0];
    colAux = coordsUltAcierto[1];

    printf("CoordsUltAcierto: (%d; %d) \n\n", filaAux, colAux);

    marcarPosBlancos(matriz, vecPosBlancos, filaAux, colAux, cantPosBlancos, puntaje, filas, cols);

    cont = 0;

    for(int i=0; i<*cantPosBlancos; i++)
    {
        filaAux = vecPosBlancos[indPuntaje][i][0];
        colAux = vecPosBlancos[indPuntaje][i][1];

        printf("CoordsPosibleBlanco: (%d; %d) --->", filaAux, colAux);

        celdaPrevAtacada = matriz[filaAux][colAux][1];

        if(celdaPrevAtacada == 0)
            cont+=1;
            printf("No fue atacado! \n");
        ;
    }

    if(cont > 0)
    {
        random = numAleatorio(0, cont-1);
        *fila = vecPosBlancos[indPuntaje][random][0];
        *col = vecPosBlancos[indPuntaje][random][1];
        *direc = vecPosBlancos[indPuntaje][random][2];

        printf("random: %d, *(%d; %d; %d) ",random, *fila, *col, *direc);

        *ataqueValido = 1;
    }


}


void ataqueComp(int ***matriz, int filas, int cols, int *puntaje, struct memoriaComp *memoria, int marca)
{
    int fila, col, filaAux, colAux, direc, direcAux, direcOpuesta;

    int ataqueValido, celdaPrevAtacada, hayBarco, vueltaAlPrimerAciertoRacha, vueltaHecha; //flags

    int *compRachaPtr = &(memoria->compRacha),
        *coordsUltAciertoPtr = memoria->coordsUltAcierto,
        *coordsPrimerAciertoRachaPtr = memoria->coordsPrimerAciertoRacha,
        ***vecPosBlancosPtr = memoria->vecPosBlancos,
        *canPosBlancosPtr = &(memoria->cantPosBlancos), 
        *ultDirTomadaPtr = memoria->ultDirTomada
    ;

    printf("\n\n compRachaPtr: %d \n\n", *compRachaPtr);

    ataqueValido = 0;
    vueltaHecha = 0;

    while (ataqueValido == 0)
    {
        switch (*compRachaPtr)
        {
        case 0:
            celdaPrevAtacada = 1;
            while (celdaPrevAtacada > 0) // (celdaPrevAtacada == 0)
            {
                apuntarEnRacha0(&fila, &col, filas, cols);
                celdaPrevAtacada = matriz[fila][col][1];
                printf("\nCase 0 (%d ; %d) \n", fila, col);
            }
            ataqueValido = 1;
            break;

        case 1:

            if(vueltaAlPrimerAciertoRacha == 1)
            {
                filaAux = coordsPrimerAciertoRachaPtr[0];
                colAux = coordsPrimerAciertoRachaPtr[1];

                marcarPosBlancos(matriz, vecPosBlancosPtr, filaAux, colAux, canPosBlancosPtr, (*puntaje), filas, cols);
            }

            if(*canPosBlancosPtr > 0)
            {
                celdaPrevAtacada = 1;
                while (celdaPrevAtacada == 1)
                {
                    apuntarEnRacha1(&fila, &col, &direc, *puntaje, *canPosBlancosPtr, vecPosBlancosPtr);
                    celdaPrevAtacada = matriz[fila][col][1];
                    printf("\nCase 1 (%d ; %d; %d) \n", fila, col, direc);
                }   
                ataqueValido = 1;
            }
            else
            {
               *compRachaPtr = 0; 
            }
            break;

        default:

            printf("\n\n -------- Default -------- \n\n");

            if(*compRachaPtr > 1)
            {
                if(vueltaAlPrimerAciertoRacha == 1)
                {
                    filaAux = coordsPrimerAciertoRachaPtr[0];
                    colAux = coordsPrimerAciertoRachaPtr[1];
                    direcAux = ultDirTomadaPtr[0];

                    switch (direcAux)
                    {
                    case 1:
                        direcOpuesta = 2;
                        break;
                    case 2:
                        direcOpuesta = 1;
                        break;
                    case 3:
                        direcOpuesta = 4;
                        break;
                    case 4:
                        direcOpuesta = 3;
                        break;
                    default:
                        *compRachaPtr = 1;
                        break;
                    }

                    marcarPosBlancos(matriz, vecPosBlancosPtr, filaAux, colAux, canPosBlancosPtr, *puntaje, filas, cols );

                    apuntarEnRachaMayorA1(&fila, &col, &direc, *puntaje, canPosBlancosPtr, vecPosBlancosPtr, direcOpuesta, &ataqueValido);
                }
                else
                {
                    apuntarEnRachaMayorA1(&fila, &col, &direc, *puntaje, canPosBlancosPtr, vecPosBlancosPtr, (ultDirTomadaPtr[0]), &ataqueValido);
                }


                printf("\nCase 2 (%d ; %d; %d) \n", fila, col, direc);

                if(ataqueValido != 1)
                {   
                    if((*compRachaPtr > 1) && (vueltaHecha == 0))
                    {
                        vueltaAlPrimerAciertoRacha = 1;
                        vueltaHecha = 1;
                    }
                    else
                    {
                        *compRachaPtr = 0;
                        vueltaAlPrimerAciertoRacha = 0;
                    }
                }
            }
            else
            {
                if((*compRachaPtr < 0) && (*compRachaPtr > -5))
                {

                    if((*canPosBlancosPtr <= 0)) ////////////////////////////////////////////////////////////////7
                    {
                        printf("\n\n|||| Puntaje: %d ,ultDirTomadaPtr[0]: %d, ultDirTomadaPtr[1]: %d \n\n", *puntaje, ultDirTomadaPtr[0], ultDirTomadaPtr[1]);

                        if((*puntaje > 1) && (*puntaje == ultDirTomadaPtr[1]))
                        {
                            *compRachaPtr = 2;
                            vueltaAlPrimerAciertoRacha = 1;
                        }
                        else
                        {
                            *compRachaPtr = 1;
                            vueltaAlPrimerAciertoRacha = 1;
                        }
                    }
                    else
                    {
                        ataqueValido = 0;

                        apuntarEnRachaNegativa(&fila, &col, &ataqueValido, &direc, filas, cols, matriz, *puntaje, canPosBlancosPtr, vecPosBlancosPtr, coordsUltAciertoPtr);

                        if(ataqueValido == 0)
                        {
                            printf("\n\n#### Puntaje: %d ,ultDirTomadaPtr[0]: %d, ultDirTomadaPtr[1]: %d \n\n", *puntaje, ultDirTomadaPtr[0], ultDirTomadaPtr[1]);

                            if((*puntaje > 1) && (*puntaje == ultDirTomadaPtr[1]))
                            {
                                *compRachaPtr = 2;
                                vueltaAlPrimerAciertoRacha = 1;
                            }
                            else
                            {
                                *compRachaPtr = 1;
                                vueltaAlPrimerAciertoRacha = 1;
                            }
                        }
                    }
                }
                else
                {
                    *compRachaPtr = 0;
                }
            }
            break;
        }
    }


    hayBarco = matriz[fila][col][0];
    matriz[fila][col][1] = marca;


    if(hayBarco==1)
    {
        (*puntaje)+=1;

        if(*compRachaPtr > 0) ////
        {
            (*compRachaPtr)+=1; //////
            ultDirTomadaPtr[0] = direc;
            ultDirTomadaPtr[1] = *puntaje;
        }
        else
        {
            if(*compRachaPtr == 0)
            {
                coordsPrimerAciertoRachaPtr[0] = fila;
                coordsPrimerAciertoRachaPtr[1] = col;
                coordsPrimerAciertoRachaPtr[2] = 0; //rondas desde que ocurrio

                *compRachaPtr = 1;
            } 
            else
            {
                *compRachaPtr = 2;
                ultDirTomadaPtr[0] = direc;
                ultDirTomadaPtr[1] = *puntaje;
            }
        }

        coordsUltAciertoPtr[0] = fila;
        coordsUltAciertoPtr[1] = col;
        coordsUltAciertoPtr[2] = 0; //rondas desde que ocurrio

        marcarPosBlancos(matriz, vecPosBlancosPtr, fila, col, canPosBlancosPtr, (*puntaje), filas, cols);

        for(int i=0; i<(*canPosBlancosPtr); i++)
        {
            printf("\nPosible Blanco N%d: ", i+1);
            printf(" (%d , %d) dir relativa: %d\n", vecPosBlancosPtr[(*puntaje)-1][i][0], vecPosBlancosPtr[(*puntaje)-1][i][1], vecPosBlancosPtr[(*puntaje)-1][i][2]);
        }

    }
    else
    {
        if(*compRachaPtr > 0)
        {
            *compRachaPtr = -1;
        }
        else
        {
            if(*compRachaPtr < 0)
            {
                (*compRachaPtr)-=1;
            }
            else
            {
                *compRachaPtr = 0;
            }
        }

        if(*puntaje > 0)
        {
            coordsUltAciertoPtr[2] += 1;
            coordsPrimerAciertoRachaPtr[2] += 1;
        }
    }
}
