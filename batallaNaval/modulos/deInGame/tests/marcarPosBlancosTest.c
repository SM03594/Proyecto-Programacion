#include <stdio.h>
#include "../../../header.h"

int main(void)
{
    int filas, cols, puntosVic;

    filas = 10;
    cols = 10;
    puntosVic = 15;

    int ***matriz = crearMat3D(filas, cols, 2);

    //----------------------------------------------------

    //Poner barcos:
    matriz[0][0][0] = 1;
    matriz[0][1][0] = 1;
    matriz[0][2][0] = 1;
    matriz[0][3][0] = 1;
    matriz[0][4][0] = 1;

    matriz[5][1][0] = 1;
    matriz[6][1][0] = 1;
    matriz[7][1][0] = 1;
    matriz[8][1][0] = 1;

    
    matriz[9][2][0] = 1;
    matriz[9][3][0] = 1;
    matriz[9][4][0] = 1;

    matriz[1][8][0] = 1;
    matriz[1][9][0] = 1;

    matriz[3][7][0] = 1;

    
    //----------------------------------------------------
    //Marcar posiciones como atacadas:

    matriz[9][2][1] = 1;
    matriz[9][3][1] = 1;
    matriz[9][4][1] = 1;

    //al rededor de (5; 5)
    matriz[4][5][1] = 1;
    matriz[5][4][1] = 1;
    matriz[5][6][1] = 1;
    matriz[6][5][1] = 1;

    //al rededor de (0; 9)
    matriz[0][8][1] = 1;
    matriz[1][9][1] = 1;

    //ariva de (9;5)
    matriz[8][5][1] = 1;

    //derecha de (9;0)
    matriz[9][1][1] = 1;

    //----------------------------------------------------

    
    printMatriz(matriz, filas, cols);


    //variables para marcarPosBlancos:

    int ***vecPosBlancos = crearMat3D(puntosVic, 4, 3);

    int fila, col, cantPosBlancos, puntaje, posRelativa, fila2, col2, indxPuntaje;

    puntaje = 1;

    int vecPosicionesAnalizar[][2] = {{5, 5}, {0, 9}, {9, 5}, {9, 0}, {7, 7}};

    int longVecPosicionesAnalizar = sizeof(vecPosicionesAnalizar) / sizeof(*vecPosicionesAnalizar);

    //printf("-------------%d.......", longVecPosicionesAnalizar);

    for(int i=0; i < longVecPosicionesAnalizar; i++)
    {
        fila = vecPosicionesAnalizar[i][0];
        col = vecPosicionesAnalizar[i][1];
        indxPuntaje = puntaje-1;

        marcarPosBlancos(matriz, vecPosBlancos, fila, col, &cantPosBlancos, puntaje, filas, cols);

        printf("**********************************\n\n");

        printf("Por (%d; %d): \n\n", fila, col);
        printf("Cantidad: %d \n", cantPosBlancos);

        for(int x=0; x<cantPosBlancos; x++)
        {
            fila2 = vecPosBlancos[indxPuntaje][x][0];
            col2 = vecPosBlancos[indxPuntaje][x][1];
            posRelativa = vecPosBlancos[indxPuntaje][x][2];

            printf("%d : (%d; %d) \n", posRelativa, fila2, col2);
        }

        printf("**********************************\n\n");

        puntaje+=1;
    }



    return 0;
}
