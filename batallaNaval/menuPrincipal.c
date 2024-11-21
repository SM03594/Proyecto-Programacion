#include <stdio.h>

#include "header.h"


void menuPrincipal(void) {
    int opcion;
    do {
            printf("\n--- Menu Principal ---\n");
            printf("Iniciar Juego\n");
            printf("Ver la tabla\n");
            printf("Salir\n");
            printf("Seleccione una opcion:");
            scanf("%d",&opcion);

        switch (opcion){
        case 1:
            batallaNavalFunc();
            break;
        case 2:
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
}