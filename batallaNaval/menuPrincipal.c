#include <stdio.h>

#include "header.h"


int main(void) {
    int opcion;
    do {
            printf("\n------ Menu Principal ------\n");
            printf("| 1-Iniciar Juego           |\n");
            printf("| 2-Ver el Ranking          |\n");
            printf("| 3-Salir                   |\n");
            printf("-----------------------------\n");
            printf("Seleccione una opcion:");
            scanf("%d",&opcion);

        switch (opcion){
        case 1:
            system("cls"); ///////////////
            batallaNavalFunc();
            break;
        case 2:
            system("cls"); ///////////////
            mostrarPuntuaciones();
            break;
        case 3:
            printf("Salir del juego...\n");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
            break;
        }
    } while(opcion != 3);

    return 0;
}
