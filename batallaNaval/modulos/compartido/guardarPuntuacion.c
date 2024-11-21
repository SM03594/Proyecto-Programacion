#include <stdio.h>
#include <string.h>

#include "../../header.h"


void guardarPuntuacion(char nombre[10], int movimientos) {

    FILE *archivo = fopen("puntuaciones.txt", "a+");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo de puntuaciones.\n");
        return;
    }

    // Escribimos el nuevo registro
    fprintf(archivo, "%s %d\n", nombre, movimientos);
    fclose(archivo);


    // Reabrimos el archivo para leer y ordenar las puntuaciones
    archivo = fopen("puntuaciones.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo de puntuaciones.\n");
        return;
    }

    // Leemos las puntuaciones en un array
    char nombres[100][50];
    int puntajes[100];
    int count = 0;
    while (fscanf(archivo, "%s %d", nombres[count], &puntajes[count]) != EOF) {
        count++;
    }
    fclose(archivo);

    // Ordenamos las puntuaciones usando Bubble Sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (puntajes[j] > puntajes[j + 1]) {
                int tempPuntaje = puntajes[j];
                char tempNombre[50];
                strcpy(tempNombre, nombres[j]);

                puntajes[j] = puntajes[j + 1];
                strcpy(nombres[j], nombres[j + 1]);

                puntajes[j + 1] = tempPuntaje;
                strcpy(nombres[j + 1], tempNombre);
            }
        }
    }

    // Escribimos las puntuaciones ordenadas en el archivo
    archivo = fopen("puntuaciones.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo de puntuaciones.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(archivo, "%s %d\n", nombres[i], puntajes[i]);
    }
    fclose(archivo);
}
