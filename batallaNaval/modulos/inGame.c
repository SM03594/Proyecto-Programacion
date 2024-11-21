#include <stdio.h>

#include "../header.h"

// Funcion inGame ( matrizComp Por Referencia, matrizJug Por Referencia, long, puntosVic )
	
// 	Definir puntosJug, puntosComp, rondasCont, turno, victoria Como Entero;
	
// 	puntosJug = 0;
// 	puntosComp = 0;
// 	rondasCont = 0;
	
// 	turno = 0; //turno == 0 es turno de jugador, turno == 1 es turno computadora
	
// 	Definir compRacha, cantPosBlancos, vecPosBlancos, vecDirDisp, ultDirTomada, coordsUltAcierto, coordsPrimerAciretoRacha Como Entero; //para la func ataqueComp
	
// 	Dimensionar vecPosBlancos[puntosVic, 4, 3];
// 	Dimensionar vecDirDisp[4, 2]; //vector para guardar las direcciones disponibles en las que atacar 
// 	Dimensionar coordsUltAcierto[3], coordsPrimerAciretoRacha[3]; //en 0 fila, en 1 col, en 2 numero de rondas desde el acierto
// 	Dimensionar ultDirTomada[2]; // en 0 direccion 0=nulo, 1=der, 2=izq, 3=arriba, 4=abajo   en 1 puntaje inmediatamente despues de cuando se tomo la direccion
	
// 	compRacha = 0;
	
// 	Mientras (victoria == 0) Hacer //ciclo in game
		
// 		Si(rondasCont == 0) Entonces
// 			printMesa(matrizJug, matrizComp, long); //printear ambas matrices
// 		FinSi
		
// 		Si (turno == 0) Entonces //turno del jugador
// 			Escribir "";
// 			Escribir "Ronda:", rondasCont+1;
// 			Escribir "Puntaje Jugador: ", puntosJug, "/", puntosVic;
// 			Escribir "Puntaje computadora: ", puntosComp, "/", puntosVic;
			
// 			atacarMatriz(matrizComp, long, puntosJug, turno);
// 			turno = 1;
// 			Si (puntosJug == puntosVic) Entonces
// 				victoria = 1;
// 			FinSi
// 		SiNo // tunro computadora
			
// 			ataqueComp(matrizJug, long, puntosComp, compRacha, cantPosBlancos, vecPosBlancos, vecDirDisp, ultDirTomada, coordsUltAcierto, coordsPrimerAciretoRacha);
			
// 			turno = 0; //cambiar de turno
// 			Si (puntosComp == puntosVic) Entonces
// 				victoria = 1;
// 			FinSi
// 		FinSi
		
// 		printMesa(matrizJug, matrizComp, long); //printear ambas matrices
		
// 		rondasCont = rondasCont + 1;
// 	Fin Mientras
	
// 	Escribir "";
// 	Escribir "Ronda:", rondasCont+1;
// 	Escribir "Puntaje Jugador: ", puntosJug, "/", puntosVic;
// 	Escribir "Puntaje computadora: ", puntosComp, "/", puntosVic;
// 	Escribir "";
	
// 	Si(puntosJug==puntosVic) Entonces
// 		escribir " ****************************** "
// 		escribir "* \    ^    /    ||     |\\  | *"
// 		escribir "*  \  / \  /     ||     | \\ | *"
// 		escribir "*   \/   \/      ||     |  \\| *"
// 		escribir " ****************************** "
// 		//Escribir "";
// 		//Escribir "El jugador ha gandado!!!!";
// 		//Escribir "";
// 	SiNo
// 		escribir " ************************** "
// 		escribir "* |     ----    ---   |--  *"
// 		escribir "* |     |  |     \    |--  *"
// 		escribir "* |__   ----    ---   |__  *"
// 		escribir " ************************** "
// 		//Escribir "";
// 		//Escribir "La computadora ha ganado!!!!";
// 		//Escribir "";
// 	FinSi
	
// FinFuncion


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
        rondasCont+=1;
    }
    
    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("Ronda: %d \n", rondasCont+1);
    printf("Puntaje Jugador: %d/%d \n", puntosJug, puntosVic);
    printf("Puntaje Computadora: %d/%d \n", puntosComp, puntosVic);
    printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");

    if(puntosJug == puntosVic)
    {
        printf("\nEl jugador ha gandado!!!!\n");
    }
    else
    {
        printf("\nLa computadora ha ganado!!!!\n");
    }

}

