#include <stdio.h>

#include "../header.h"


void inGame(int ***matrizJug, int ***matrizComp, int puntosVic, int filas, int cols)
{
    int puntosJug, puntosComp, rondasCont, turno, victoria;

    puntosJug = 0;
 	puntosComp = 0;
 	rondasCont = 0;
 	turno = 0; //turno == 0 es turno de jugador, turno == 1 es turno computadora
    victoria = 0;

    struct memoriaComp memoria;
    memoria.compRacha = 0;
    memoria.cantPosBlancos = 0;
    memoria.vecPosBlancos = crearMat3D(100, 4, 3); ////////////
    

    while (victoria==0)
    {
        if(rondasCont == 0)
        {
            printMesa(matrizJug, matrizComp, filas, cols);
        }

        if(turno==0)
        {
            printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            printf("Ronda: %d \n", rondasCont+1);
            printf("Puntaje Jugador: %d/%d \n", puntosJug, puntosVic);
            printf("Puntaje Computadora: %d/%d \n", puntosComp, puntosVic);
            printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");

            atacarMatriz(matrizComp, filas, cols, &puntosJug, turno);
            
            if(puntosJug == puntosVic)
            {
                victoria = 1;
            }
            
            turno = 1;
        }
        else
        {
            ataqueComp(matrizJug, filas, cols, &puntosComp, &memoria, 1);
            
            if(puntosComp == puntosVic)
            {
                victoria = 1;
            }
            
            turno = 0;
        }

        printMesa(matrizJug, matrizComp, filas, cols);
        if(turno == 1)
        {
            rondasCont+=1;
        }
    }
    
    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("Ronda: %d \n", rondasCont+1);
    printf("Puntaje Jugador: %d/%d \n", puntosJug, puntosVic);
    printf("Puntaje Computadora: %d/%d \n", puntosComp, puntosVic);
    printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");

    if(puntosJug == puntosVic)
    {
        printf("\nEl jugador ha gandado!!!!\n\n");

        char *nombre;

        printf("Ingrese su nombre para el ranking: "); ///////////////////
        scanf("%s", nombre);

        guardarPuntuacion(nombre, rondasCont); ////////////////
    }
    else
    {
        printf("\nLa computadora ha ganado!!!!\n");
    }

}

