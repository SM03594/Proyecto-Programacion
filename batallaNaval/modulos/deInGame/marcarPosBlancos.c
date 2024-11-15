#include <stdio.h>
#include "../../header.h"

void marcarPosBlancos(int ***matriz ,int ***vecPosBlancos, int fila, int col, int *cantPosBlancos, int puntaje, int filas, int cols)
{
    int celdaAtaqueStatus, coordsMatriz[4][3], filaAux, colAux, cont, indicePuntaje;

    indicePuntaje = puntaje - 1;

    coordsMatriz[0][0] = fila;
    coordsMatriz[0][1] = col+1;

    coordsMatriz[1][0] = fila;             //1=der, 2=izq, 3=arriba, 4=abajo
    coordsMatriz[1][1] = col-1;

    coordsMatriz[2][0] = fila-1;
    coordsMatriz[2][1] = col;

    coordsMatriz[3][0] = fila+1;
    coordsMatriz[3][1] = col;

    cont = 0;

    for(int i=0; i<4; i++)
    {
        filaAux = coordsMatriz[i][0];
        colAux = coordsMatriz[i][1];

        if((filaAux >= 0) && (filaAux <= filas-1))
        {
            if((colAux >= 0) && (colAux <= cols-1))
            {
                celdaAtaqueStatus = matriz[filaAux][colAux][1];

                if(celdaAtaqueStatus == 0)
                {
                    vecPosBlancos[indicePuntaje][cont][0] = filaAux;
                    vecPosBlancos[indicePuntaje][cont][1] = colAux;
                    vecPosBlancos[indicePuntaje][cont][2] = i+1;   //direccion con respeto al acierto 1-der 2-izq 3-arriba 4-abajo

                    cont+=1;
                }
            }
        }
    }

    *cantPosBlancos = cont;
}

