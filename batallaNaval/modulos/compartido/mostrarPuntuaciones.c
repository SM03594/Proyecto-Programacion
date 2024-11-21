#include <stdio.h>

#include "../../header.h"

void mostrarPuntuaciones(void) {
    int opcion;

    FILE *archivo = fopen("puntuaciones.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo de puntuaciones.\n");
        return;
    }

    char nombre[50];
    int movimientos;
    printf("\n--- Tabla de Puntuaciones ---\n");
    printf("Nombre\t\tMovimientos\n");
    printf("-----------------------------\n");

    while (fscanf(archivo, "%s %d", nombre, &movimientos) != EOF) {
        printf("%s\t\t%d\n", nombre, movimientos);
    }
    printf("\nPreciona 1 para volver al menu principal: ");
    scanf("%d", &opcion);
    if (opcion == 0) {
        printf("Saliendo de la tabla de clasificacion.\n");
    }

    fclose(archivo);
}