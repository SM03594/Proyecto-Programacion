#include <stdio.h>
#include <math.h>
#include "../../header.h"


void printMesa(int ***matrizJug, int ***matrizComp, int filas, int cols)
{
    int i, x, j;
    int longMesa, espIntermedio, espTituloJuego, espCartelJugadores, espParaNumeracion, espEntreCartelesJugs, espEntreFilasDeNums, ejeMayor;

    // if(filas >= cols)
    //     ejeMayor = filas;
    // else
    //     ejeMayor = cols
    // ;

    if(filas > 10)
    {
        espIntermedio = 10;
        espParaNumeracion = 5;
        espTituloJuego = trunc(filas*3 + espIntermedio/2);
        espCartelJugadores = trunc(espParaNumeracion + ((filas*3)/2) - 8);
        espEntreFilasDeNums = espIntermedio + espParaNumeracion*2 - 2;
    }
    else
    {
        espIntermedio = 6;
        espParaNumeracion = 5; ///

        if(filas < 8)
            espCartelJugadores = trunc( filas/2);
        else
            espCartelJugadores = trunc( (filas+2)/2)
        ;
        espTituloJuego = trunc(filas*2 + espIntermedio/2);
        espEntreFilasDeNums = espIntermedio + espParaNumeracion*2 - 3;

    }

    espEntreCartelesJugs = espCartelJugadores*2 + espIntermedio;
    

    //Limpiar Pantalla

    printf("\n");

    //---------titulo juego-------------------------------

    
    for(i=0; i<espTituloJuego; i++)
        printf(" ")
    ;

    printf("  _______________   \n");

    for(i=0; i<espTituloJuego; i++)
        printf(" ")
    ;

    printf(" | BATALLA NAVAL |  \n");

    for(i=0; i<espTituloJuego; i++)
        printf(" ")
    ;

    printf("  ---------------   \n");

    //----------------------------------------------------

    printf("\n");

    //------------Espacio para carteles de pertenecia de tableros--------------------------------

    for(i=0; i<espCartelJugadores; i++)
        printf(" ")
    ;

    printf("TABLERO JUGADOR");

    for(i=0; i<espEntreCartelesJugs; i++)
        printf(" ")
    ;

    printf("TABLERO OPONENTE\n");

    //----------------------------------------------------

    printf("\n");

    //------------Matrices--------------------------------

    for(i=-1; i<filas; i++)
    {   
        if(i==-1)
        {

            for(x=0; x<espParaNumeracion; x++)
                printf(" ");
            ;  

            for(x=0; x<cols; x++)
            {
                if((filas > 10) && (x<10)) //Enumerar las cols de la primera matriz
                    printf(" ") //para compensar por el espacio del digito extra
                ;
                
                printf(" %d", x);
            }

            for(x=0; x<espEntreFilasDeNums; x++) ///
                printf(" ")
            ;

            for(x=0; x<cols; x++)
            {
                if((filas > 10) && (x<10)) //Enumerar las cols de la primera matriz
                    printf(" ") //para compensar por el espacio del digito extra
                ;
                
                printf(" %d", x);
            }

            printf("\n");


            for(x=0; x<espParaNumeracion; x++)
                printf(" ");
            ;

            for(x=0; x<cols; x++)
            {
                if(filas > 10)
                    printf(" --");
                else
                    printf(" -")
                ;
            }

            for(x=0; x<espEntreFilasDeNums; x++) ////
                printf(" ")
            ;

            for(x=0; x<cols; x++)
            {
                if(filas > 10)
                    printf(" --");
                else
                    printf(" -")
                ;
            }

            printf("\n");
        }
        else
        {
           
            if((i<10) && (filas > 10))
                printf(" ")
            ;

            printf("   %d|", i);

            for(x=0; x<cols; x++)
            {
                if(matrizJug[i][x][0]==1)
                {
                    if(matrizJug[i][x][1]==1)
                        printf(" X");
                    else
                        printf(" #")
                    ;
                }
                else
                {
                    if(matrizJug[i][x][1]==1)
                        printf("  ");
                    else
                        printf(" 0")
                    ;
                }

                if(filas>10)
                    printf(" ")
                ;
            }

            if(filas<=10)
                printf(" ")
            ;

            printf("|%d", i);

            for(x=0; x<espIntermedio; x++)
                printf(" ")
            ;

            if((i<10) && (filas>10))
                printf("  ")
            ;

            printf("  %d|", i);

            for(x=0; x<filas; x++)
            {
                if(matrizComp[i][x][0]==1)
                {
                    if(matrizComp[i][x][1]==1)
                        printf(" X");
                    else
                        printf(" #")
                    ;
                }
                else
                {
                    if(matrizComp[i][x][1]==1)
                        printf("  ");
                    else
                        printf(" 0")
                    ;
                }

                if(filas>10)
                    printf(" ")
                ;
            }

            if(filas<=10)
                printf(" ") //agregar espacio extra para que el numero no quede pegado al |
            ;

            printf("|%d", i);

            printf("\n");
        }
        
    }

    for(x=0; x<espParaNumeracion; x++)
        printf(" ");
    ;

    for(x=0; x<cols; x++)
    {
        if(filas > 10)
            printf(" --");
        else
            printf(" -")
        ;
    }

    for(x=0; x<espEntreFilasDeNums; x++)
        printf(" ")
    ;

    for(x=0; x<cols; x++)
    {
        if(filas > 10)
            printf(" --");
        else
            printf(" -")
        ;
    }

    printf("\n");

    for(x=0; x<espParaNumeracion; x++)
        printf(" ");
    ;  

    for(x=0; x<cols; x++)
    {
        if((filas > 10) && (x<10)) //Enumerar las cols de la primera matriz
            printf(" ") //para compensar por el espacio del digito extra
        ;
                    
        printf(" %d", x);
    }

    for(x=0; x<espEntreFilasDeNums; x++)
        printf(" ")
    ;

    for(x=0; x<cols; x++)
    {
        if((filas > 10) && (x<10)) //Enumerar las cols de la primera matriz
            printf(" ") //para compensar por el espacio del digito extra
        ;
                    
        printf(" %d", x);
    }

    printf("\n");
    
}

