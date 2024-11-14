#include <stdio.h>
#define LONG 8

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
    int i, j;
    char mat[LONG][LONG];

    for (i = 0; i < LONG; i++) {
        for (j = 0; j < LONG; j++) {
            mat[i][j] = ' ';
        }
    }

    rellenarMatriz(mat);
}
//-------------------------------------------------------------------------------------------------------------------
void MostrarMatriz(char mat[LONG][LONG]) {
    int i, j;

    printf("   1  2  3  4  5  6  7  8\n");
    printf("   -  -  -  -  -  -  -  -\n");

    for (i = 0; i < LONG; i++) {
        printf("%d|", i + 1);
        for (j = 0; j < LONG; j++) {
            printf(" %c ", mat[i][j]);
        }
        printf("|%d\n", i + 1);
    }

    printf("   -  -  -  -  -  -  -  -\n");
    printf("   1  2  3  4  5  6  7  8\n");
}
//-------------------------------------------------------------------------------------------------------------------
void rellenarMatriz(char mat[LONG][LONG]) {
    int i, j, cont = 0;
    int finJuego = 0, turnoColor = 1;

    for (i = 0; i <= 2; i++) {
        for (j = (1 - cont); j < LONG; j += 2) {
            mat[i][j] = 'N';
        }
        cont = (cont == 0) ? 1 : 0;
    }

    cont = 1;
    for (i = 5; i <= 7; i++) {
        for (j = (1 - cont); j < LONG; j += 2) {
            mat[i][j] = 'R';
        }
        cont = (cont == 0) ? 1 : 0;
    }

    MostrarMatriz(mat);

    finJuego = 0;
    turnoColor = 1;
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
void VerificarCapturaRojas(char mat[LONG][LONG], int vectorCaptura[3]) {
    int vectorAux[3] = {0, 0, 0};
    int fila, columna;

    do {
        for (fila = 0; fila < 8; fila++) {
            for (columna = 0; columna < 8; columna++) {
                if (mat[fila][columna] == 'R') {
                    if (fila - 2 >= 0 && columna - 2 >= 0 && (mat[fila - 1][columna - 1] == 'N' || mat[fila - 1][columna - 1] == 'n') && mat[fila - 2][columna - 2] == ' ') {
                        printf("La pieza Roja puede capturar a la Negra\n");
                        vectorAux[0] = 1;
                        vectorAux[1] = fila + 1;
                        vectorAux[2] = columna + 1;
                        fila = 7;
                        columna = 7;
                    } else if (fila - 2 >= 0 && columna + 2 <= 7 && (mat[fila - 1][columna + 1] == 'N' || mat[fila - 1][columna + 1] == 'n') && mat[fila - 2][columna + 2] == ' ') {
                        printf("La pieza Roja puede capturar a la Negra\n");
                        vectorAux[0] = 1;
                        vectorAux[1] = fila + 1;
                        vectorAux[2] = columna + 1;
                        fila = 7;
                        columna = 7;
                    } else {
                        vectorAux[0] = 0;
                        vectorAux[1] = fila + 1;
                        vectorAux[2] = columna + 1;
                    }
                } else if (mat[fila][columna] == 'r') {
                    if ((fila - 2 >= 0 && columna - 2 >= 0 && (mat[fila - 1][columna - 1] == 'N' || mat[fila - 1][columna - 1] == 'n') && mat[fila - 2][columna - 2] == ' ') ||
                        (fila + 2 <= 7 && columna - 2 >= 0 && (mat[fila + 1][columna - 1] == 'N' || mat[fila + 1][columna - 1] == 'n') && mat[fila + 2][columna - 2] == ' ')) {
                        printf("La Reina Roja puede capturar a la Negra\n");
                        vectorAux[0] = 1;
                        vectorAux[1] = fila + 1;
                        vectorAux[2] = columna + 1;
                        fila = 7;
                        columna = 7;
                    } else if ((fila - 2 >= 0 && columna + 2 <= 7 && (mat[fila - 1][columna + 1] == 'N' || mat[fila - 1][columna + 1] == 'n') && mat[fila - 2][columna + 2] == ' ') ||
                               (fila + 2 <= 7 && columna + 2 <= 7 && (mat[fila + 1][columna + 1] == 'N' || mat[fila + 1][columna + 1] == 'n') && mat[fila + 2][columna + 2] == ' ')) {
                        printf("La Reina Roja puede capturar a la Negra\n");
                        vectorAux[0] = 1;
                        vectorAux[1] = fila + 1;
                        vectorAux[2] = columna + 1;
                        fila = 7;
                        columna = 7;
                    } else {
                        vectorAux[0] = 0;
                        vectorAux[1] = fila + 1;
                        vectorAux[2] = columna + 1;
                    }
                }
            }
        }
    } while (vectorAux[0] == 1 || (fila < 7 && columna < 7));

    vectorCaptura[0] = vectorAux[0];
    vectorCaptura[1] = vectorAux[1];
    vectorCaptura[2] = vectorAux[2];
}
//-------------------------------------------------------------------------------------------------------------------
void VerificarCapturaNegras(char mat[LONG][LONG], int vectorCaptura[3]) {
    int vectorAux[3] = {0, 0, 0};
    int fila, columna;

    do {
        for (fila = 0; fila < 8; fila++) {
            for (columna = 0; columna < 8; columna++) {
                if (mat[fila][columna] == 'N') {
                    if (fila + 2 <= 7 && columna - 2 >= 0 && (mat[fila + 1][columna - 1] == 'R' || mat[fila + 1][columna - 1] == 'r') && mat[fila + 2][columna - 2] == ' ') {
                        printf("La pieza Negra puede capturar a la Roja\n");
                        vectorAux[0] = 1;
                        vectorAux[1] = fila + 1;
                        vectorAux[2] = columna + 1;
                        fila = 7;
                        columna = 7;
                    } else if (fila + 2 <= 7 && columna + 2 <= 7 && (mat[fila + 1][columna + 1] == 'R' || mat[fila + 1][columna + 1] == 'r') && mat[fila + 2][columna + 2] == ' ') {
                        printf("La pieza Negra puede capturar a la Roja\n");
                        vectorAux[0] = 1;
                        vectorAux[1] = fila + 1;
                        vectorAux[2] = columna + 1;
                        fila = 7;
                        columna = 7;
                    } else {
                        vectorAux[0] = 0;
                        vectorAux[1] = fila;
                        vectorAux[2] = columna;
                    }
                } else if (mat[fila][columna] == 'n') {
                    if ((fila - 2 >= 0 && columna - 2 >= 0 && (mat[fila - 1][columna - 1] == 'R' || mat[fila - 1][columna - 1] == 'r') && mat[fila - 2][columna - 2] == ' ') ||
                        (fila + 2 <= 7 && columna - 2 >= 0 && (mat[fila + 1][columna - 1] == 'R' || mat[fila + 1][columna - 1] == 'r') && mat[fila + 2][columna - 2] == ' ')) {
                        printf("La Reina Negra puede capturar a la Roja\n");
                        vectorAux[0] = 1;
                        vectorAux[1] = fila + 1;
                        vectorAux[2] = columna + 1;
                        fila = 7;
                        columna = 7;
                    } else if ((fila - 2 >= 0 && columna + 2 <= 7 && (mat[fila - 1][columna + 1] == 'R' || mat[fila - 1][columna + 1] == 'r') && mat[fila - 2][columna + 2] == ' ') ||
                               (fila + 2 <= 7 && columna + 2 <= 7 && (mat[fila + 1][columna + 1] == 'R' || mat[fila + 1][columna + 1] == 'r') && mat[fila + 2][columna + 2] == ' ')) {
                        printf("La Reina Negra puede capturar a la Roja\n");
                        vectorAux[0] = 1;
                        vectorAux[1] = fila + 1;
                        vectorAux[2] = columna + 1;
                        fila = 7;
                        columna = 7;
                    } else {
                        vectorAux[0] = 0;
                        vectorAux[1] = fila;
                        vectorAux[2] = columna;
                    }
                }
            }
        }
    } while (vectorAux[0] == 1 || (fila < 7 && columna < 7));

    vectorCaptura[0] = vectorAux[0];
    vectorCaptura[1] = vectorAux[1];
    vectorCaptura[2] = vectorAux[2];
}
//-------------------------------------------------------------------------------------------------------------------

void MovimientoR(char mat[TAM][TAM]) {
    printf("Turno de Rojas\n");
    int fila, columna, filaN, columnaN, deltaX, deltaY, capturarXP, capturarXN, capturarY, movimientoValido;
    int esEntero;
    char auxChar;
    int vectorCaptura[3] = {0, 0, 0};
    movimientoValido = 0;

    verificarCapturaRojas(mat, vectorCaptura);

    if (vectorCaptura[0] == 1) {
        fila = vectorCaptura[1];
        columna = vectorCaptura[2];
        printf("Pieza Roja (%d, %d) está obligada a comer\n", fila, columna);

        if (mat[fila-1][columna-1] == 'R') {
            do {
                printf("¿Dónde desea mover la pieza? (primero fila, luego columna): ");
                esEntero = 0;
                while (esEntero == 0) {
                    scanf(" %c", &auxChar);
                    esEntero = verificarSiEntero(auxChar);
                    if (esEntero == 1) {
                        filaN = convertirANumero(auxChar);
                    } else {
                        printf("ERROR: el valor ingresado para fila no es un numero entero\n");
                    }
                }

                esEntero = 0;
                while (esEntero == 0) {
                    scanf(" %c", &auxChar);
                    esEntero = verificarSiEntero(auxChar);
                    if (esEntero == 1) {
                        columnaN = convertirANumero(auxChar);
                    } else {
                        printf("ERROR: el valor ingresado para columna no es un numero entero\n");
                    }
                }

                deltaX = columnaN - columna;
                deltaY = filaN - fila;
            } while (!(filaN > 0 && filaN <= 8 && columnaN > 0 && columnaN <= 8) && deltaY < 0 && (abs(deltaX) == 2) && (abs(deltaY) == 2) && (mat[filaN-1][columnaN-1] == ' ') && (filaN <= 7) && (columnaN - 2 >= 0 && (mat[filaN][columnaN - 2] == 'N' || mat[filaN][columnaN - 2] == 'n')) || (columnaN <= 7 && (mat[filaN][columnaN] == 'N' || mat[filaN][columnaN] == 'n')));

            if (abs(deltaX) == 2 && abs(deltaY) == 2) {
                capturarXP = columna + (deltaX / 2);
                capturarY = fila + (deltaY / 2);
                if (mat[capturarY-1][capturarXP-1] == 'N') {
                    mat[capturarY-1][capturarXP-1] = ' ';
                    printf("Pieza capturada\n");
                } else if (mat[capturarY-1][capturarXP-1] == 'n') {
                    mat[capturarY-1][capturarXP-1] = ' ';
                    printf("Pieza capturada\n");
                }
            }
        } else if (mat[fila-1][columna-1] == 'r') {
            do {
                printf("¿Dónde desea mover la pieza? (primero fila, luego columna): ");
                esEntero = 0;
                while (esEntero == 0) {
                    scanf(" %c", &auxChar);
                    esEntero = verificarSiEntero(auxChar);
                    if (esEntero == 1) {
                        filaN = convertirANumero(auxChar);
                    } else {
                        printf("ERROR: el valor ingresado para fila no es un numero entero\n");
                    }
                }

                esEntero = 0;
                while (esEntero == 0) {
                    scanf(" %c", &auxChar);
                    esEntero = verificarSiEntero(auxChar);
                    if (esEntero == 1) {
                        columnaN = convertirANumero(auxChar);
                    } else {
                        printf("ERROR: el valor ingresado para columna no es un numero entero\n");
                    }
                }

                deltaX = columnaN - columna;
                deltaY = filaN - fila;
            } while (!(filaN > 0 && filaN <= 8 && columnaN > 0 && columnaN <= 8) && (abs(deltaX) == 2 && abs(deltaY) == 2) && (mat[filaN-1][columnaN-1] == ' ') && ((filaN <= 7) && (columnaN - 2 >= 0 && (mat[filaN][columnaN - 2] == 'N' || mat[filaN][columnaN - 2] == 'n')) || (columnaN <= 7 && (mat[filaN][columnaN] == 'N' || mat[filaN][columnaN] == 'n'))) || (filaN-2 >= 0) && (columnaN - 2 >= 0 && (mat[filaN-2][columnaN - 2] == 'N' || mat[filaN-2][columnaN - 2] == 'n')) || (columnaN <= 7 && (mat[filaN-2][columnaN] == 'N' || mat[filaN-2][columnaN] == 'n'))));

            if (abs(deltaX) == 2 && abs(deltaY) == 2) {
                capturarXP = columna + (deltaX / 2);
                capturarY = fila + (deltaY / 2);
                if (mat[capturarY-1][capturarXP-1] == 'N') {
                    mat[capturarY-1][capturarXP-1] = ' ';
                    printf("Pieza capturada\n");
                } else if (mat[capturarY-1][capturarXP-1] == 'n') {
                    mat[capturarY-1][capturarXP-1] = ' ';
                    printf("Pieza capturada\n");
                }
            }
        }
    } else {
        do {
            printf("Seleccione la posición de la pieza que desea mover (primero fila, luego columna): ");
            esEntero = 0;
            while (esEntero == 0) {
                scanf(" %c", &auxChar);
                esEntero = verificarSiEntero(auxChar);
                if (esEntero == 1) {
                    fila = convertirANumero(auxChar);
                } else {
                    printf("ERROR: el valor ingresado para fila no es un numero entero\n");
                }
            }

            esEntero = 0;
            while (esEntero == 0) {
                scanf(" %c", &auxChar);
                esEntero = verificarSiEntero(auxChar);
                if (esEntero == 1) {
                    columna = convertirANumero(auxChar);
                } else {
                    printf("ERROR: el valor ingresado para columna no es un numero entero\n");
                }
            }

            //leer fila
            //leer columna
        } while (!(columna > 0 && columna <= 8 && fila > 0 && fila <= 8) && (mat[fila-1][columna-1] == 'R' || mat[fila-1][columna-1] == 'r'));
        if (mat[fila-1][columna-1] == 'R') {
            if ((fila-2 >= 0) && (columna-2 >= 0 || columna <= 7) && ((columna-2 >= 0 && mat[fila-2][columna-2] == ' ') || (columna <= 7 && mat[fila-2][columna] == ' '))) {
                movimientoValido = 1;
            }
        } else if (mat[fila-1][columna-1] == 'r') {
            if (((fila-2 >= 0) && ((columna-2 >= 0 && mat[fila-2][columna-2] == ' ') || (columna <= 7 && mat[fila-2][columna] == ' '))) || ((fila <= 7) && ((columna-2 >= 0 && mat[fila][columna-2] == ' ') || (columna <= 7 && mat[fila][columna] == ' ')))) {
                movimientoValido = 1;
            }
        }
    }

    if (mat[fila-1][columna-1] == 'R') {
        mat[filaN-1][columnaN-1] = 'R';
        mat[fila-1][columna-1] = ' ';
    } else {
        mat[filaN-1][columnaN-1] = 'r';
        mat[fila-1][columna-1] = ' ';
    }

    if (filaN == 1) {
        mat[filaN-1][columnaN-1] = 'r'; // Dama roja
    }
}
//-------------------------------------------------------------------------------------------------------------------

void MovimientoN(char mat[8][8]) {
    printf("Turno de Negras\n");

    int fila, columna, filaN, columnaN, deltaX, deltaY, capturarXP, capturarXN, capturarY, movimientoValido;
    int esEntero;
    char auxChar;
    int vectorCaptura[3] = {0, 0, 0};

    movimientoValido = 0;
    VerificarCapturaNegras(mat, vectorCaptura);

    if (vectorCaptura[0] == 1) {
        fila = vectorCaptura[1];
        columna = vectorCaptura[2];
        printf("Pieza Negra (%d, %d) está obligada a comer\n", fila, columna);

        if (mat[fila-1][columna-1] == 'N') {
            do {
                printf("¿Dónde desea mover la pieza? (primero fila, luego columna): ");

                esEntero = 0;
                while (esEntero == 0) {
                    scanf(" %c", &auxChar);
                    esEntero = verificarSiEntero(auxChar);
                    if (esEntero == 1) {
                        filaN = ConvertirANumero(auxChar);
                    } else {
                        printf("ERROR: el valor ingresado para fila no es un numero entero\n");
                    }
                }

                esEntero = 0;
                while (esEntero == 0) {
                    scanf(" %c", &auxChar);
                    esEntero = verificarSiEntero(auxChar);
                    if (esEntero == 1) {
                        columnaN = ConvertirANumero(auxChar);
                    } else {
                        printf("ERROR: el valor ingresado para columna no es un numero entero\n");
                    }
                }

                deltaX = columnaN - columna;
                deltaY = filaN - fila;
            } while (!(filaN > 0 && filaN <= 8 && columnaN > 0 && columnaN <= 8) &&
                     (abs(deltaX) == 2 && abs(deltaY) == 2) &&
                     mat[filaN-1][columnaN-1] == ' ' &&
                     filaN - 2 >= 0 &&
                     ((columnaN - 2 >= 0 && (mat[filaN-2][columnaN-2] == 'R' || mat[filaN-2][columnaN-2] == 'r')) ||
                      (columnaN <= 7 && (mat[filaN-2][columnaN] == 'R' || mat[filaN-2][columnaN] == 'r'))));

            if (abs(deltaX) == 2 && abs(deltaY) == 2) {
                capturarXP = columna + (deltaX / 2);
                capturarY = fila + (deltaY / 2);
                if (mat[capturarY-1][capturarXP-1] == 'R') {
                    mat[capturarY-1][capturarXP-1] = ' ';
                    printf("Pieza capturada\n");
                } else if (mat[capturarY-1][capturarXP-1] == 'r') {
                    mat[capturarY-1][capturarXP-1] = ' ';
                    printf("Pieza capturada\n");
                }
            }
        } else if (mat[fila-1][columna-1] == 'n') {
            do {
                printf("¿Dónde desea mover la pieza? (primero fila, luego columna): ");

                esEntero = 0;
                while (esEntero == 0) {
                    scanf(" %c", &auxChar);
                    esEntero = verificarSiEntero(auxChar);
                    if (esEntero == 1) {
                        filaN = ConvertirANumero(auxChar);
                    } else {
                        printf("ERROR: el valor ingresado para fila no es un numero entero\n");
                    }
                }

                esEntero = 0;
                while (esEntero == 0) {
                    scanf(" %c", &auxChar);
                    esEntero = verificarSiEntero(auxChar);
                    if (esEntero == 1) {
                        columnaN = ConvertirANumero(auxChar);
                    } else {
                        printf("ERROR: el valor ingresado para columna no es un numero entero\n");
                    }
                }

                deltaX = columnaN - columna;
                deltaY = filaN - fila;
            } while (!(filaN > 0 && filaN <= 8 && columnaN > 0 && columnaN <= 8) &&
                     (abs(deltaX) == 2 && abs(deltaY) == 2) &&
                     mat[filaN-1][columnaN-1] == ' ' &&
                     ((filaN <= 7 && (columnaN - 2 >= 0 && (mat[filaN][columnaN-2] == 'R' || mat[filaN][columnaN-2] == 'r'))) ||
                      (columnaN <= 7 && (mat[filaN][columnaN] == 'R' || mat[filaN][columnaN] == 'r'))) ||
                     (filaN - 2 >= 0 &&
                      columnaN - 2 >= 0 &&
                      (mat[filaN-2][columnaN-2] == 'R' || mat[filaN-2][columnaN-2] == 'r')) ||
                      (columnaN <= 7 && (mat[filaN-2][columnaN] == 'R' || mat[filaN-2][columnaN] == 'r'))));

            if (abs(deltaX) == 2 && abs(deltaY) == 2) {
                capturarXP = columna + (deltaX / 2);
                capturarY = fila + (deltaY / 2);
                if (mat[capturarY-1][capturarXP-1] == 'R') {
                    mat[capturarY-1][capturarXP-1] = ' ';
                    printf("Pieza capturada\n");
                } else if (mat[capturarY-1][capturarXP-1] == 'r') {
                    mat[capturarY-1][capturarXP-1] = ' ';
                    printf("Pieza capturada\n");
                }
            }
        }
    } else {
        do {
            printf("Seleccione la posición de la pieza que desea mover (primero fila, luego columna): ");

            esEntero = 0;
            while (esEntero == 0) {
                scanf(" %c", &auxChar);
                esEntero = verificarSiEntero(auxChar);
                if (esEntero == 1) {
                    fila = ConvertirANumero(auxChar);
                } else {
                    printf("ERROR: el valor ingresado para fila no es un numero entero\n");
                }
            }

            esEntero = 0;
            while (esEntero == 0) {
                scanf(" %c", &auxChar);
                esEntero = verificarSiEntero(auxChar);
                if (esEntero == 1) {
                    columna = ConvertirANumero(auxChar);
                } else {
                    printf("ERROR: el valor ingresado para columna no es un numero entero\n");
                }
            }

        } while (!(fila > 0 && fila <= 8 && columna > 0 && columna <= 8) &&
                 (mat[fila - 1][columna - 1] == 'N' || mat[fila - 1][columna - 1] == 'n'));

        if (mat[fila - 1][columna - 1] == 'N') {
            if (fila <= 7 && ((columna - 2 >= 0 && mat[fila][columna - 2] == ' ') ||
                               (columna <= 7 && mat[fila][columna] == ' '))) {
                movimientoValido = 1;
            }
        } else if (mat[fila - 1][columna - 1] == 'n') {
            if (((fila - 2 >= 0 && (columna - 2 >= 0 && mat[fila - 2][columna - 2] == ' ') ||
                  (columna <= 7 && mat[fila - 2][columna] == ' '))) ||
                ((fila <= 7) &&
                 ((columna - 2 >= 0 && mat[fila][columna - 2] == ' ') ||
                  (columna <= 7 && mat[fila][columna] == ' ')))) {
                movimientoValido = 1;
            }
        }

        while (movimientoValido == 0) {
            printf("¿Dónde desea mover la pieza? (primero fila, luego columna): ");

            esEntero = 0;
            while (esEntero == 0) {
                scanf(" %c", &auxChar);
                esEntero = verificarSiEntero(auxChar);
                if (esEntero == 1) {
                    filaN = ConvertirANumero(auxChar);
                } else {
                    printf("ERROR: el valor ingresado para fila no es un numero entero\n");
                }
            }

            esEntero = 0;
            while (esEntero == 0) {
                scanf(" %c", &auxChar);
                esEntero = verificarSiEntero(auxChar);
                if (esEntero == 1) {
                    columnaN = ConvertirANumero(auxChar);
                } else {
                    printf("ERROR: el valor ingresado para columna no es un numero entero\n");
                }
            }

            deltaX = columnaN - columna;
            deltaY = filaN - fila;
        }

        if (mat[fila - 1][columna - 1] == 'N') {
            mat[filaN - 1][columnaN - 1] = 'N';
            mat[fila - 1][columna - 1] = ' ';
        } else {
            mat[filaN - 1][columnaN - 1] = 'n';
            mat[fila - 1][columna - 1] = ' ';
        }

        if (filaN == 8) {
            mat[filaN - 1][columnaN - 1] = 'n'; // Dama negra
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
void Finjuego(char mat[8][8], int *Finjuego, int turnoColor) {
    int contarRojas = 0, contarNegras = 0;
    int puedenMoverRojas = 0, puedenMoverNegras = 0;
    int fila, columna;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (mat[i][j] == 'R' || mat[i][j] == 'r') contarRojas++;
            if (mat[i][j] == 'N' || mat[i][j] == 'n') contarNegras++;
        }
    }

    if (contarRojas == 0) {
        *Finjuego = 2;  // Negras ganan
    } else if (contarNegras == 0) {
        *Finjuego = 1;  // Rojas ganan
    } else {
        if (turnoColor == 1) {
            for (fila = 0; fila < 8; fila++) {
                for (columna = 0; columna < 8; columna++) {
                    if (mat[fila][columna] == 'R') {
                        if ((fila - 2 >= 0 && columna - 2 >= 0 && (mat[fila - 1][columna - 1] == 'N' || mat[fila - 1][columna - 1] == 'n') && mat[fila - 2][columna - 2] == ' ') ||
                            (fila - 2 >= 0 && columna + 2 <= 7 && (mat[fila - 1][columna + 1] == 'N' || mat[fila - 1][columna + 1] == 'n') && mat[fila - 2][columna + 2] == ' ') ||
                            (fila - 1 >= 0 && columna - 1 >= 0 && mat[fila - 1][columna - 1] == ' ') ||
                            (fila - 1 >= 0 && columna + 1 <= 7 && mat[fila - 1][columna + 1] == ' ')) {
                            puedenMoverRojas = 1;
                        }
                    }
                }
            }

            for (fila = 0; fila < 8; fila++) {
                for (columna = 0; columna < 8; columna++) {
                    if (mat[fila][columna] == 'r') {
                        if ((fila - 2 >= 0 && columna - 2 >= 0 && (mat[fila - 1][columna - 1] == 'N' || mat[fila - 1][columna - 1] == 'n') && mat[fila - 2][columna - 2] == ' ') ||
                            (fila - 2 >= 0 && columna + 2 <= 7 && (mat[fila - 1][columna + 1] == 'N' || mat[fila - 1][columna + 1] == 'n') && mat[fila - 2][columna + 2] == ' ') ||
                            (fila - 1 >= 0 && columna - 1 >= 0 && mat[fila - 1][columna - 1] == ' ') ||
                            (fila - 1 >= 0 && columna + 1 <= 7 && mat[fila - 1][columna + 1] == ' ') ||
                            (fila + 2 <= 7 && columna - 2 >= 0 && (mat[fila + 1][columna - 1] == 'N' || mat[fila + 1][columna - 1] == 'n') && mat[fila + 2][columna - 2] == ' ') ||
                            (fila + 2 <= 7 && columna + 2 <= 7 && (mat[fila + 1][columna + 1] == 'N' || mat[fila + 1][columna + 1] == 'n') && mat[fila + 2][columna + 2] == ' ') ||
                            (fila + 1 <= 7 && columna - 1 >= 0 && mat[fila + 1][columna - 1] == ' ') ||
                            (fila + 1 <= 7 && columna + 1 <= 7 && mat[fila + 1][columna + 1] == ' ')) {
                            puedenMoverRojas = 1;
                        }
                    }
                }
            }

            if (puedenMoverRojas == 0) {
                *Finjuego = 3;  // Empate
            }
        }

        if (turnoColor == 2) {
            for (fila = 0; fila < 8; fila++) {
                for (columna = 0; columna < 8; columna++) {
                    if (mat[fila][columna] == 'N') {
                        if ((fila + 2 <= 7 && columna - 2 >= 0 && (mat[fila + 1][columna - 1] == 'R' || mat[fila + 1][columna - 1] == 'r') && mat[fila + 2][columna - 2] == ' ') ||
                            (fila + 2 <= 7 && columna + 2 <= 7 && (mat[fila + 1][columna + 1] == 'R' || mat[fila + 1][columna + 1] == 'r') && mat[fila + 2][columna + 2] == ' ') ||
                            (fila + 1 <= 7 && columna - 1 >= 0 && mat[fila + 1][columna - 1] == ' ') ||
                            (fila + 1 <= 7 && columna + 1 <= 7 && mat[fila + 1][columna + 1] == ' ')) {
                            puedenMoverNegras = 1;
                        }
                    }
                }
            }

            for (fila = 0; fila < 8; fila++) {
                for (columna = 0; columna < 8; columna++) {
                    if (mat[fila][columna] == 'n') {
                        if ((fila - 2 >= 0 && columna - 2 >= 0 && (mat[fila - 1][columna - 1] == 'R' || mat[fila - 1][columna - 1] == 'r') && mat[fila - 2][columna - 2] == ' ') ||
                            (fila - 2 >= 0 && columna + 2 <= 7 && (mat[fila - 1][columna + 1] == 'R' || mat[fila - 1][columna + 1] == 'r') && mat[fila - 2][columna + 2] == ' ') ||
                            (fila - 1 >= 0 && columna - 1 >= 0 && mat[fila - 1][columna - 1] == ' ') ||
                            (fila - 1 >= 0 && columna + 1 <= 7 && mat[fila - 1][columna + 1] == ' ') ||
                            (fila + 2 <= 7 && columna - 2 >= 0 && (mat[fila + 1][columna - 1] == 'R' || mat[fila + 1][columna - 1] == 'r') && mat[fila + 2][columna - 2] == ' ') ||
                            (fila + 2 <= 7 && columna + 2 <= 7 && (mat[fila + 1][columna + 1] == 'R' || mat[fila + 1][columna + 1] == 'r') && mat[fila + 2][columna + 2] == ' ') ||
                            (fila + 1 <= 7 && columna - 1 >= 0 && mat[fila + 1][columna - 1] == ' ') ||
                            (fila + 1 <= 7 && columna + 1 <= 7 && mat[fila + 1][columna + 1] == ' ')) {
                            puedenMoverNegras = 1;
                        }
                    }
                }
            }

            if (puedenMoverNegras == 0) {
                *Finjuego = 3;  // Empate
            }
        }
    }

    if (*Finjuego != 0) {
        if (*Finjuego == 1) {
            printf("¡Felicitaciones! Las Rojas han ganado.\n");
        } else if (*Finjuego == 2) {
            printf("¡Felicitaciones! Las Negras han ganado.\n");
        } else if (*Finjuego == 3) {
            printf("No hay más movimientos posibles para el jugador ¡Empate!\n");
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
int verif(char *charNum) {
    int long_num, i;
    char ch;

    long_num = strlen(charNum);
    int verif = 1;
    i = 0;

    if (long_num != 0) {
        while (i < long_num) {
            ch = charNum[i];
            if (ch >= '0' && ch <= '9') {
                i = i + 1;
            } else {
                verif = 0;
                i = long_num;
            }
        }
    } else {
        verif = 0;
    }

    return verif;
}
