#include <stdio.h>
#include <time.h>

#include "../../header.h"

int*** crearMat(int filas, int cols) {
    // Reservar memoria para la matriz 3D
    int ***matriz = (int ***)malloc(filas * sizeof(int **));

    for (int i = 0; i < filas; i++) {
        matriz[i] = (int **)malloc(cols * sizeof(int *));
        for (int j = 0; j < cols; j++) {
            matriz[i][j] = (int *)malloc(2 * sizeof(int));
        }
    }
    
    // Inicializar la matriz con ceros
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < 2; k++) {
                matriz[i][j][k] = 0;
            }
        }
    }

    return matriz;
}

