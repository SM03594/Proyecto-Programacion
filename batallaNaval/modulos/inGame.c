#include <stdio.h>
#include <string.h>

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
    
    system("cls"); ///////////////

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

        if(turno == 0)
            rondasCont+=1
        ;
    
        system("cls"); //////////
        printMesa(matrizJug, matrizComp, filas, cols);
    }
    
    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("Ronda: %d \n", rondasCont+1);
    printf("Puntaje Jugador: %d/%d \n", puntosJug, puntosVic);
    printf("Puntaje Computadora: %d/%d \n", puntosComp, puntosVic);
    printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");

    if(puntosJug == puntosVic)
    {
        printf("\nEl jugador ha gandado!!!!\n\n");

        int inputValido, longitud;
        char nombre[100];

        inputValido = 0;
        
        while (inputValido != 1) {
            printf("Ingrese su nombre para el ranking (7 caracteres max): ");

            if (fgets(nombre, sizeof(nombre), stdin)) {
                // Eliminar el salto de línea (\n) al final de la entrada
                nombre[strcspn(nombre, "\n")] = '\0';

                longitud = strlen(nombre);

                if (longitud >= 1 && longitud <= 7) {
                    inputValido = 1;  
                    printf("Nombre ingresado: %s\n", nombre);
                } else {
                    printf("\nERROR: El nombre debe tener entre 1 y 7 caracteres.\n");
                }
            } else {
                printf("ERROR: Entrada no válida. Intente de nuevo.\n");
                while (getchar() != '\n');  // Esto consume los caracteres restantes en el buffer
            }
        }

        guardarPuntuacion(nombre, (rondasCont+1)); ////////////////
    }
    else
    {
        printf("\nLa computadora ha ganado!!!!\n");
    }

}
