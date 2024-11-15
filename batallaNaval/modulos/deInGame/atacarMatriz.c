#include <stdio.h>
#include "../../header.h"
#include "pedirCoordsAtaque.c"


//#include "../compartido/numAleatorio.c"

// Funcion atacarMatriz ( matriz Por Referencia, longMatriz, puntaje Por Referencia, turno ) 
// 	Definir fila, col, coordsAtaque, posPrevAtacada, celdaAtaqueStatus, hayBarco Como Entero;
// 	Dimensionar coordsAtaque[2];
	
// 	posPrevAtacada = 1;
	
// 	Mientras (posPrevAtacada==1) Hacer
		
// 		Si(turno == 0) Entonces //turno == 0 es turno de jugador
// 			Escribir "";
// 			Escribir "Ingrese las coordenadas de ataque: ";
// 			Escribir "";
// 			pedirCoordsAtaque(coordsAtaque, longMatriz);
// 			fila = coordsAtaque[0];
// 			col = coordsAtaque[1];
// 		SiNo
// 			fila = Aleatorio(0, longMatriz-1);
// 			col = Aleatorio(0, longMatriz-1);
// 		FinSi
		
// 		celdaAtaqueStatus = matriz[fila, col, 1]; // sera 1 si la celda ya fue atacada y 0 si no lo fue
		
// 		Si (celdaAtaqueStatus == 1) Entonces
// 			Escribir "ERROR: la celda ubicada en ( ", fila, ", ", col  " ), ya fue atacada";
// 		SiNo
// 			posPrevAtacada = 0;
			
// 			matriz[fila, col, 1] = 1; //marcar el ataque en la celda
			
// 			hayBarco = matriz[fila, col, 0]; // sera 1 si hay barco y 0 si no lo hay
			
// 			Si(hayBarco == 1) Entonces
// 				puntaje = puntaje + 1;
// 			FinSi
			
// 			Escribir "";
			
// 		FinSi
// 	Fin Mientras
// Fin Funcion


void atacarMatriz(int ***matiz, int filas, int cols, int *puntaje, int turno)
{
    int fila, col, coordsAtaque[2], posPrevAtacada, celdaAtaqueStatus, hayBarco;

    posPrevAtacada = 1;

    while (posPrevAtacada==1)
    {
        if(turno==0) //turno == 0 es turno del jugador
        {
            printf("\nIngrese las coordenadas de ataque \n");

            pedirCoordsAtaque(coordsAtaque, filas, cols);

            fila = coordsAtaque[0];
 			col = coordsAtaque[1];
        }
        else //turno de computadora
        {
            fila = numAleatorio(0, filas-1);
            col = numAleatorio(0, cols-1);
        }

        celdaAtaqueStatus = matiz[fila][col][1];

        if(celdaAtaqueStatus==0)
        {
            posPrevAtacada = 0;

            matiz[fila][col][1] = 1; //marcar atque en matriz

            hayBarco = matiz[fila][col][0]; // sera 1 si hay barco y 0 si no lo hay

            if(hayBarco==1)
            {
                (*puntaje)+=1;
            }

            printf("\n");
        }
        else
        {
            printf("\nERROR: la celda ubicada en ( %d, %d ) ya fue atacada \n", fila, col);
        }
    }
}

