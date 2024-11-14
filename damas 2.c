#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LONG 8
#define TAMANO_TABLERO 8

void CrearMatriz();
void MostrarMatriz(char mat[LONG][LONG]);
void rellenarMatriz(char mat[LONG][LONG]);
int VerificarFinJuego(char mat[LONG][LONG], int finJuego, int turnoColor);
void MovimientoR(char mat[LONG][LONG]);
void MovimientoN(char mat[LONG][LONG]);
void VerificarCapturaRojas(char mat[LONG][LONG], int vectorCaptura[3]);
void VerificarCapturaNegras(char mat[LONG][LONG], int vectorCaptura[3]);

int main() {
    CrearMatriz();
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
void CrearMatriz() {
    char mat[LONG][LONG];
    for (int i = 0; i < LONG; i++) {
        for (int j = 0; j < LONG; j++) {
            mat[i][j] = ' ';
        }
    }
    rellenarMatriz(mat);
}

//-------------------------------------------------------------------------------------------------------------------
void MostrarMatriz(char mat[LONG][LONG]) {
    printf("   1  2  3  4  5  6  7  8\n");
    printf("   -  -  -  -  -  -  -  -\n");
    for (int i = 0; i < LONG; i++) {
        printf("%d |", i + 1);
        for (int j = 0; j < LONG; j++) {
            printf(" %c ", mat[i][j]);
        }
        printf("| %d\n", i + 1);
    }
    printf("   -  -  -  -  -  -  -  -\n");
    printf("   1  2  3  4  5  6  7  8\n");
}

//-------------------------------------------------------------------------------------------------------------------
void rellenarMatriz(char mat[LONG][LONG]) {
    int cont = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = (1 - cont); j < LONG; j += 2) {
            mat[i][j] = 'N';
        }
        cont = 1 - cont;
    }

    cont = 1;
    for (int i = 5; i < 8; i++) {
        for (int j = (1 - cont); j < LONG; j += 2) {
            mat[i][j] = 'R';
        }
        cont = 1 - cont;
    }
    MostrarMatriz(mat);
    int finJuego = 0;
    int turnoColor = 1;
    do {
        finJuego = VerificarFinJuego(mat, finJuego, turnoColor);
        if (finJuego == 0) {
            MovimientoR(mat);
            MostrarMatriz(mat);
        }
        finJuego = VerificarFinJuego(mat, finJuego, turnoColor);
        turnoColor = 2;
        finJuego = VerificarFinJuego(mat, finJuego, turnoColor);
        if (finJuego == 0) {
            MovimientoN(mat);
            MostrarMatriz(mat);
            finJuego = VerificarFinJuego(mat, finJuego, turnoColor);
            turnoColor = 1;
        }
    } while (finJuego != 0);
}

//-------------------------------------------------------------------------------------------------------------------
int VerificarFinJuego(char mat[LONG][LONG], int finJuego, int turnoColor) {
    int i, j;
    int tienePiezas = 0;
    int tieneMovimientos = 0;

    for (i = 0; i < LONG; i++) {
        for (j = 0; j < LONG; j++) {
            if (turnoColor == 1 && (mat[i][j] == 'N' || mat[i][j] == 'n')) { // Piezas negras
                tienePiezas = 1;
            } else if (turnoColor == 2 && (mat[i][j] == 'R' || mat[i][j] == 'r')) { // Piezas rojas
                tienePiezas = 1;
            }
        }
    }


    if (!tienePiezas) {
        finJuego = 1;
        printf("Jugador %d ha ganado, no tiene más piezas.\n", (turnoColor == 1) ? 2 : 1);
        return finJuego;
    }


    for (i = 0; i < LONG; i++) {
        for (j = 0; j < LONG; j++) {
            if (turnoColor == 1 && (mat[i][j] == 'N' || mat[i][j] == 'n')) { // Piezas negras
                if (PuedeMover(mat, i, j, turnoColor)) {
                    tieneMovimientos = 1;
                    break;
                }
            } else if (turnoColor == 2 && (mat[i][j] == 'R' || mat[i][j] == 'r')) { // Piezas rojas
                if (PuedeMover(mat, i, j, turnoColor)) {
                    tieneMovimientos = 1;
                    break;
                }
            }
        }
        if (tieneMovimientos) break;
    }


    if (!tieneMovimientos) {
        finJuego = 1;
        printf("Jugador %d ha ganado, no tiene movimientos disponibles.\n", (turnoColor == 1) ? 2 : 1);
    }

    return finJuego;
}


int PuedeMover(char mat[LONG][LONG], int fila, int columna, int turnoColor) {
    int i, j;
    int direcciones[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    char pieza = mat[fila][columna];


    for (i = 0; i < 4; i++) {
        int nuevaFila = fila + direcciones[i][0];
        int nuevaColumna = columna + direcciones[i][1];


        if (nuevaFila >= 0 && nuevaFila < LONG && nuevaColumna >= 0 && nuevaColumna < LONG) {
            if (mat[nuevaFila][nuevaColumna] == ' ') {
                return 1;
            }
        }
    }


    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
void MovimientoR(char mat[LONG][LONG]) {
    printf("Turno de Rojas\n");

    int fila, columna, filaN, columnaN, deltaX, deltaY, capturarXP, capturarXN, capturarY, movimientoValido;
    int vectorCaptura[3] = {0, 0, 0};
    movimientoValido = 0;


    VerificarCapturaRojas(mat, vectorCaptura);

    if (vectorCaptura[0] == 1) {

        fila = vectorCaptura[1];
        columna = vectorCaptura[2];
        printf("Pieza Roja (%d, %d) está obligada a comer\n", fila, columna);

        if (mat[fila - 1][columna - 1] == 'R') {
            do {
                printf("¿Dónde desea mover la pieza? (primero fila, luego columna): ");
                scanf("%d %d", &filaN, &columnaN);
                deltaX = columnaN - columna;
                deltaY = filaN - fila;
            } while (filaN > 0 && filaN <= LONG && columnaN > 0 && columnaN <= LONG && deltaY < 0 && abs(deltaX) == 2 && abs(deltaY) == 2 && mat[filaN - 1][columnaN - 1] == ' ' &&
                     filaN <= 7 && (columnaN - 2 >= 0 && (mat[filaN - 1][columnaN - 2] == 'N' || mat[filaN - 1][columnaN - 2] == 'n')) ||
                     (columnaN <= 7 && (mat[filaN - 1][columnaN - 1] == 'N' || mat[filaN - 1][columnaN - 1] == 'n')));

            if (abs(deltaX) == 2 && abs(deltaY) == 2) {
                capturarXP = columna + (deltaX / 2);
                capturarY = fila + (deltaY / 2);
                if (mat[capturarY - 1][capturarXP - 1] == 'N' || mat[capturarY - 1][capturarXP - 1] == 'n') {
                    mat[capturarY - 1][capturarXP - 1] = ' ';
                    printf("Pieza capturada\n");
                }
            }
        }
    } else {
        do {
            do {
                printf("Seleccione la posición de la pieza que desea mover (primero fila, luego columna): ");
                scanf("%d %d", &fila, &columna);
            } while (columna <= 0 || columna > LONG || fila <= 0 || fila > LONG || (mat[fila - 1][columna - 1] != 'R' && mat[fila - 1][columna - 1] != 'r'));

            if (mat[fila - 1][columna - 1] == 'R') {
                if ((fila - 2 >= 0) && (columna - 2 >= 0 || columna <= 7) && ((columna - 2 >= 0 && mat[fila - 2][columna - 2] == ' ') || (columna <= 7 && mat[fila - 2][columna] == ' '))) {
                    movimientoValido = 1;
                }
            } else if (mat[fila - 1][columna - 1] == 'r') {
                if (((fila - 2 >= 0) && ((columna - 2 >= 0 && mat[fila - 2][columna - 2] == ' ') || (columna <= 7 && mat[fila - 2][columna] == ' '))) ||
                    ((fila <= 7) && ((columna - 2 >= 0 && mat[fila][columna - 2] == ' ') || (columna <= 7 && mat[fila][columna] == ' ')))) {
                    movimientoValido = 1;
                }
            }
        } while (movimientoValido != 1);

        // Realizar el movimiento
        if (mat[fila - 1][columna - 1] == 'R') {
            do {
                printf("¿Dónde desea mover la pieza? (primero fila, luego columna): ");
                scanf("%d %d", &filaN, &columnaN);
                deltaX = columnaN - columna;
                deltaY = filaN - fila;
            } while (filaN > 0 && filaN <= LONG && columnaN > 0 && columnaN <= LONG && deltaY < 0 && abs(deltaX) == 1 && abs(deltaY) == 1 && mat[filaN - 1][columnaN - 1] == ' ' && deltaY < 0);
        } else if (mat[fila - 1][columna - 1] == 'r') {
            do {
                printf("¿Dónde desea mover la pieza? (primero fila, luego columna): ");
                scanf("%d %d", &filaN, &columnaN);
                deltaX = columnaN - columna;
                deltaY = filaN - fila;
            } while (filaN > 0 && filaN <= LONG && columnaN > 0 && columnaN <= LONG && abs(deltaX) == 1 && abs(deltaY) == 1 && mat[filaN - 1][columnaN - 1] == ' ');
        }
    }


    if (mat[fila - 1][columna - 1] == 'R') {
        mat[filaN - 1][columnaN - 1] = 'R';
        mat[fila - 1][columna - 1] = ' ';
    } else {
        mat[filaN - 1][columnaN - 1] = 'r';
        mat[fila - 1][columna - 1] = ' ';
    }


    if (filaN == 1) {
        mat[filaN - 1][columnaN - 1] = 'r'; // Dama roja
    }
}
//-------------------------------------------------------------------------------------------------------------------


void MovimientoN(char mat[LONG][LONG]) {
    printf("Turno de Negras\n");

    int fila, columna, filaN, columnaN, deltaX, deltaY, capturarX, capturarY;
    int vectorCaptura[3] = {0, 0, 0};
    int movimientoValido = 0;


    VerificarCapturaNegras(mat, vectorCaptura);

    if (vectorCaptura[0] == 1) {
        fila = vectorCaptura[1];
        columna = vectorCaptura[2];
        printf("Pieza Negra (%d, %d) está obligada a comer\n", fila, columna);

        if (mat[fila - 1][columna - 1] == 'N') {
            do {
                printf("¿Dónde desea mover la pieza? (primero fila, luego columna): ");
                scanf("%d %d", &filaN, &columnaN);
                deltaX = columnaN - columna;
                deltaY = filaN - fila;
            } while (!((filaN > 0 && filaN <= 8 && columnaN > 0 && columnaN <= 8) &&
                      (abs(deltaX) == 2 && abs(deltaY) == 2) &&
                      mat[filaN - 1][columnaN - 1] == ' ' &&
                      (filaN - 2 >= 0) &&
                      ((columnaN - 2 >= 0 && (mat[filaN - 2][columnaN - 2] == 'R' || mat[filaN - 2][columnaN - 2] == 'r')) ||
                       (columnaN <= 7 && (mat[filaN - 2][columnaN] == 'R' || mat[filaN - 2][columnaN] == 'r')))));

            if (abs(deltaX) == 2 && abs(deltaY) == 2) {
                capturarX = columna + (deltaX / 2);
                capturarY = fila + (deltaY / 2);
                if (mat[capturarY - 1][capturarX - 1] == 'R') {
                    mat[capturarY - 1][capturarX - 1] = ' ';
                    printf("Pieza capturada\n");
                } else if (mat[capturarY - 1][capturarX - 1] == 'r') {
                    mat[capturarY - 1][capturarX - 1] = ' ';
                    printf("Pieza capturada\n");
                }
            }
        }
        else if (mat[fila - 1][columna - 1] == 'n') {
            do {
                printf("¿Dónde desea mover la pieza? (primero fila, luego columna): ");
                scanf("%d %d", &filaN, &columnaN);
                deltaX = columnaN - columna;
                deltaY = filaN - fila;
            } while (!((filaN > 0 && filaN <= 8 && columnaN > 0 && columnaN <= 8) &&
                      (abs(deltaX) == 2 && abs(deltaY) == 2) &&
                      mat[filaN - 1][columnaN - 1] == ' ' &&
                      ((filaN <= 7 && (columnaN - 2 >= 0 && (mat[filaN][columnaN - 2] == 'R' || mat[filaN][columnaN - 2] == 'r'))) ||
                       (columnaN <= 7 && (mat[filaN][columnaN] == 'R' || mat[filaN][columnaN] == 'r'))) ||
                       (filaN - 2 >= 0 && (columnaN - 2 >= 0 && (mat[filaN - 2][columnaN - 2] == 'R' || mat[filaN - 2][columnaN - 2] == 'r'))) ||
                       (columnaN <= 7 && (mat[filaN - 2][columnaN] == 'R' || mat[filaN - 2][columnaN] == 'r'))));

            if (abs(deltaX) == 2 && abs(deltaY) == 2) {
                capturarX = columna + (deltaX / 2);
                capturarY = fila + (deltaY / 2);
                if (mat[capturarY - 1][capturarX - 1] == 'R') {
                    mat[capturarY - 1][capturarX - 1] = ' ';
                    printf("Pieza capturada\n");
                } else if (mat[capturarY - 1][capturarX - 1] == 'r') {
                    mat[capturarY - 1][capturarX - 1] = ' ';
                    printf("Pieza capturada\n");
                }
            }
        }
    } else {
        do {
            do {
                printf("Seleccione la posición de la pieza que desea mover (primero fila, luego columna): ");
                scanf("%d %d", &fila, &columna);
            } while (!(fila > 0 && fila <= 8 && columna > 0 && columna <= 8 &&
                      (mat[fila - 1][columna - 1] == 'N' || mat[fila - 1][columna - 1] == 'n')));

            if (mat[fila - 1][columna - 1] == 'N') {
                if ((fila <= 7) && ((columna - 2 >= 0 && mat[fila][columna - 2] == ' ') ||
                                    (columna <= 7 && mat[fila][columna] == ' '))) {
                    movimientoValido = 1;
                }
            } else if (mat[fila - 1][columna - 1] == 'n') {
                if (((fila - 2 >= 0) && ((columna - 2 >= 0 && mat[fila - 2][columna - 2] == ' ') ||
                                         (columna <= 7 && mat[fila - 2][columna] == ' '))) ||
                    ((fila <= 7) && ((columna - 2 >= 0 && mat[fila][columna - 2] == ' ') ||
                                     (columna <= 7 && mat[fila][columna] == ' ')))) {
                    movimientoValido = 1;
                }
            }
        } while (movimientoValido == 0);

        do {
            printf("¿Dónde desea mover la pieza? (primero fila, luego columna): ");
            scanf("%d %d", &filaN, &columnaN);
            deltaX = columnaN - columna;
            deltaY = filaN - fila;
        } while (!((filaN > 0 && filaN <= 8 && columnaN > 0 && columnaN <= 8) &&
                  (abs(deltaX) == 1 && abs(deltaY) == 1) && mat[filaN - 1][columnaN - 1] == ' ' && deltaY > 0));

        if (mat[fila - 1][columna - 1] == 'N') {
            mat[filaN - 1][columnaN - 1] = 'N';
            mat[fila - 1][columna - 1] = ' ';
        } else if (mat[fila - 1][columna - 1] == 'n') {
            mat[filaN - 1][columnaN - 1] = 'n';
            mat[fila - 1][columna - 1] = ' ';
        }
    }

    if (filaN == 8) {
        mat[filaN - 1][columnaN - 1] = 'n'; // Dama negra
    }
}


//-------------------------------------------------------------------------------------------------------------------
void VerificarCapturaRojas(char mat[LONG][LONG], int vectorCaptura[3]) {
    int vectorAux[3] = {0, 0, 0};
    int fila, columna;
    int capturaPosible = 0;

    for (fila = 0; fila < LONG && !capturaPosible; fila++) {
        for (columna = 0; columna < LONG && !capturaPosible; columna++) {

            if (mat[fila][columna] == 'R') {

                if (fila - 2 >= 0 && columna - 2 >= 0 &&
                    (mat[fila - 1][columna - 1] == 'N' || mat[fila - 1][columna - 1] == 'n') &&
                    mat[fila - 2][columna - 2] == ' ') {
                    printf("La pieza Roja puede capturar a la Negra\n");
                    vectorAux[0] = 1;
                    vectorAux[1] = fila + 1;
                    vectorAux[2] = columna + 1;
                    capturaPosible = 1;
                    break;
                }

                else if (fila - 2 >= 0 && columna + 2 < LONG &&
                    (mat[fila - 1][columna + 1] == 'N' || mat[fila - 1][columna + 1] == 'n') &&
                    mat[fila - 2][columna + 2] == ' ') {
                    printf("La pieza Roja puede capturar a la Negra\n");
                    vectorAux[0] = 1;
                    vectorAux[1] = fila + 1;
                    vectorAux[2] = columna + 1;
                    capturaPosible = 1;
                    break;
                }
            }

            else if (mat[fila][columna] == 'r') {
                if (fila - 2 >= 0 && columna - 2 >= 0 &&
                    (mat[fila - 1][columna - 1] == 'N' || mat[fila - 1][columna - 1] == 'n') &&
                    mat[fila - 2][columna - 2] == ' ') {
                    printf("La Reina Roja puede capturar a la Negra\n");
                    vectorAux[0] = 1;
                    vectorAux[1] = fila + 1;
                    vectorAux[2] = columna + 1;
                    capturaPosible = 1;
                    break;
                }
                else if (fila - 2 >= 0 && columna + 2 < LONG &&
                    (mat[fila - 1][columna + 1] == 'N' || mat[fila - 1][columna + 1] == 'n') &&
                    mat[fila - 2][columna + 2] == ' ') {
                    printf("La Reina Roja puede capturar a la Negra\n");
                    vectorAux[0] = 1;
                    vectorAux[1] = fila + 1;
                    vectorAux[2] = columna + 1;
                    capturaPosible = 1;
                    break;
                }
                else if (fila + 2 < LONG && columna - 2 >= 0 &&
                    (mat[fila + 1][columna - 1] == 'N' || mat[fila + 1][columna - 1] == 'n') &&
                    mat[fila + 2][columna - 2] == ' ') {
                    printf("La Reina Roja puede capturar a la Negra\n");
                    vectorAux[0] = 1;
                    vectorAux[1] = fila + 1;
                    vectorAux[2] = columna + 1;
                    capturaPosible = 1;
                    break;
                }
                else if (fila + 2 < LONG && columna + 2 < LONG &&
                    (mat[fila + 1][columna + 1] == 'N' || mat[fila + 1][columna + 1] == 'n') &&
                    mat[fila + 2][columna + 2] == ' ') {
                    printf("La Reina Roja puede capturar a la Negra\n");
                    vectorAux[0] = 1;
                    vectorAux[1] = fila + 1;
                    vectorAux[2] = columna + 1;
                    capturaPosible = 1;
                    break;
                }
            }
        }
    }

    vectorCaptura[0] = vectorAux[0];
    vectorCaptura[1] = vectorAux[1];
    vectorCaptura[2] = vectorAux[2];
}

//-------------------------------------------------------------------------------------------------------------------
void VerificarCapturaNegras(char mat[LONG][LONG], int vectorCaptura[3]) {
    int vectorAux[3] = {0, 0, 0};  // Inicializamos el vector auxiliar para la captura
    int fila, columna;
    int capturaPosible = 0;  // Usamos un entero para representar falso (0) o verdadero (1)

    // Recorremos todo el tablero buscando piezas negras
    for (fila = 0; fila < LONG && !capturaPosible; fila++) {
        for (columna = 0; columna < LONG; columna++) {
            if (mat[fila][columna] == 'N') {  // Si encontramos una pieza negra normal
                // Comprobar si puede capturar hacia la izquierda y abajo
                if (fila + 2 < LONG && columna - 2 >= 0 &&
                    (mat[fila + 1][columna - 1] == 'R' || mat[fila + 1][columna - 1] == 'r') &&
                    mat[fila + 2][columna - 2] == ' ') {
                    printf("La pieza Negra puede capturar a la Roja\n");
                    vectorAux[0] = 1;
                    vectorAux[1] = fila + 1;  // Guardamos la posición de la pieza que captura (en formato 1-indexed)
                    vectorAux[2] = columna + 1;
                    capturaPosible = 1;
                    break;
                }
                // Comprobar si puede capturar hacia la derecha y abajo
                else if (fila + 2 < LONG && columna + 2 < LONG &&
                         (mat[fila + 1][columna + 1] == 'R' || mat[fila + 1][columna + 1] == 'r') &&
                         mat[fila + 2][columna + 2] == ' ') {
                    printf("La pieza Negra puede capturar a la Roja\n");
                    vectorAux[0] = 1;
                    vectorAux[1] = fila + 1;
                    vectorAux[2] = columna + 1;
                    capturaPosible = 1;
                    break;
                }
            }
            else if (mat[fila][columna] == 'n') {  // Si encontramos una Reina Negra
                // Comprobar si puede capturar hacia la izquierda y abajo
                if ((fila - 2 >= 0 && columna - 2 >= 0 &&
                     (mat[fila - 1][columna - 1] == 'R' || mat[fila - 1][columna - 1] == 'r') &&
                     mat[fila - 2][columna - 2] == ' ') ||
                    (fila + 2 < LONG && columna - 2 >= 0 &&
                     (mat[fila + 1][columna - 1] == 'R' || mat[fila + 1][columna - 1] == 'r') &&
                     mat[fila + 2][columna - 2] == ' ')) {
                    printf("La Reina Negra puede capturar a la Roja\n");
                    vectorAux[0] = 1;
                    vectorAux[1] = fila + 1;
                    vectorAux[2] = columna + 1;
                    capturaPosible = 1;
                    break;
                }
                // Comprobar si puede capturar hacia la derecha y abajo
                else if ((fila - 2 >= 0 && columna + 2 < LONG &&
                          (mat[fila - 1][columna + 1] == 'R' || mat[fila - 1][columna + 1] == 'r') &&
                          mat[fila - 2][columna + 2] == ' ') ||
                         (fila + 2 < LONG && columna + 2 < LONG &&
                          (mat[fila + 1][columna + 1] == 'R' || mat[fila + 1][columna + 1] == 'r') &&
                          mat[fila + 2][columna + 2] == ' ')) {
                    printf("La Reina Negra puede capturar a la Roja\n");
                    vectorAux[0] = 1;
                    vectorAux[1] = fila + 1;
                    vectorAux[2] = columna + 1;
                    capturaPosible = 1;
                    break;
                }
            }
        }
    }

    // Asignamos los valores de captura al vector de captura
    vectorCaptura[0] = vectorAux[0];
    vectorCaptura[1] = vectorAux[1];
    vectorCaptura[2] = vectorAux[2];
}
