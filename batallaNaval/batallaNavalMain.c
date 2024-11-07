
#include <stdio.h>
#include "modulos/printMatriz.c"
#include "modulos/ponerBarco.c"
#include "modulos/checkDispon.c"
#include "modulos/posEnRango.c"
#include "modulos/pedirCoords.c"

#define LONGITUD 10
#define LONGCELDA 2


int main(void)
{
    int numBarcos, puntosVic;

    numBarcos = 5;
    puntosVic = 0;

    int matrizJug[LONGITUD][LONGITUD][LONGCELDA] = {0}, 
        matrizComp[LONGITUD][LONGITUD][LONGCELDA] = {0},
        vecBarcos[numBarcos]
    ;

    printf("\n");

    for(int i=0; i<numBarcos; i++)
    {
        vecBarcos[i] = i+1;
        puntosVic += (i+1);
        //printf(" %d ", i);
    }

    //printf("\n\n");
    //printMatriz(matrizJug);
    //printf("\n\n");

    int coords1[3] = {0,0,0},
        coords2[3] = {0,1,2},
        coords3[3] = {0,5,3}, 
        coords4[3] = {1,8,2}, 
        coords5[3] = {1,9,9},
        //para checkDisp:
        coords6[3] = {0,0,2}, //m
        coords7[3] = {1,0,9}, //b
        coords8[3] = {1,3,3}, //m
        coords9[3] = {0,8,2}, //m
        coords10[3] = {1,2,0} //b        
    ;

    ponerBarco(matrizJug, coords1, 5);
    ponerBarco(matrizJug, coords2, 4);
    ponerBarco(matrizJug, coords3, 3);
    ponerBarco(matrizJug, coords4, 2);
    ponerBarco(matrizJug, coords5, 1);


    printf("\n\n");
    printMatriz(matrizJug);
    printf("\n\n");

    int a, b, c, d, e;

    a = checkDisp(matrizJug, coords6, 5, 1);
    printf("\n");
    b = checkDisp(matrizJug, coords7, 4, 1); 
    printf("\n"); 
    c = checkDisp(matrizJug, coords8, 3, 1);
    printf("\n");
    d = checkDisp(matrizJug, coords9, 2, 1);
    printf("\n");
    e = checkDisp(matrizJug, coords10, 5, 1);

    printf("\n\n");

    printf("Pos1: %d \n", a);
    printf("Pos2: %d \n", b);
    printf("Pos3: %d \n", c);
    printf("Pos4: %d \n", d);
    printf("Pos5: %d \n", e);

    printf("\n\n");

//---------------------------------------------------------------

    int coords11[3] = {0,0,5}, //b
        coords12[3] = {1,0,9}, //b
        coords13[3] = {1,8,3}, //m
        coords14[3] = {0,8,9}, //m
        coords15[3] = {1,2,0} //b
    ;

    int alfa, beta, gamma, delta, epsilon;

    printf("1: ");
    alfa = posEnRango(coords11, 5, LONGITUD, 1);
    printf("\n");
    printf("2: ");
    beta = posEnRango(coords12, 4, LONGITUD, 1);
    printf("\n");
    printf("3: ");
    gamma = posEnRango(coords13, 3, LONGITUD, 1);
    printf("\n");
    printf("4: ");
    delta = posEnRango(coords14, 2, LONGITUD, 1);
    printf("\n");
    printf("5: ");
    epsilon = posEnRango(coords15, 1, LONGITUD, 1);
    printf("\n");

}


