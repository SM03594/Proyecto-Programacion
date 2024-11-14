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
    printf("    1  2  3  4  5  6  7  8\n");
    printf("    -  -  -  -  -  -  -  -\n");
    for (int i = 0; i < LONG; i++) {
        printf("%d |", i + 1);
        for (int j = 0; j < LONG; j++) {
            printf(" %c ", mat[i][j]);
        }
        printf("| %d\n", i + 1);
    }
    printf("    -  -  -  -  -  -  -  -\n");
    printf("    1  2  3  4  5  6  7  8\n");
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
        // Repetir el ciclo hasta que haya un ganador
        finJuego = VerificarFinJuego(mat, finJuego, turnoColor);
        if (finJuego == 0) {
            MovimientoR(mat);  // Mueve las piezas rojas
            MostrarMatriz(mat); // Muestra el tablero después del movimiento
        }

        finJuego = VerificarFinJuego(mat, finJuego, turnoColor);
        turnoColor = 2;  // Cambiar turno a negras
        finJuego = VerificarFinJuego(mat, finJuego, turnoColor);

        if (finJuego == 0) {
            MovimientoN(mat);  // Mueve las piezas negras
            MostrarMatriz(mat); // Muestra el tablero después del movimiento
            finJuego = VerificarFinJuego(mat, finJuego, turnoColor);
            turnoColor = 1;  // Cambiar turno a rojas
        }
    } while (finJuego != 1);  // Mientras no haya fin de juego
}

//-------------------------------------------------------------------------------------------------------------------
int VerificarFinJuego(char mat[LONG][LONG], int finJuego, int turnoColor) {
    int i, j;
    int contarRojas, contarNegras;
    int tieneMovimientos = 0;
    contarRojas=0;
    contarNegras=0;

for (i=0;i<= 7;i++){
    for (j=0; j<=7; j++){
        if (mat[i][j]=='R' || mat[i][j]=='r'){
            contarRojas++;
        }

		if (mat[i][j]=='N' || mat[i][j]=='n'){
            contarNegras++;
        }
    }
}

if(contarRojas == 0)
	{finJuego = 2;}
else if (contarNegras == 0)
	{finJuego = 1;}


    // Comprobar si el jugador tiene movimientos disponibles
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

    // Si no tiene movimientos, el oponente gana
    if (!tieneMovimientos) {
        finJuego = 1;
        printf("Jugador %d ha ganado, no tiene movimientos disponibles.\n", (turnoColor == 1) ? 2 : 1);
    }

    return finJuego;
}

// Función para verificar si una pieza puede moverse
int PuedeMover(char mat[LONG][LONG], int fila, int columna, int turnoColor) {
    int i, j;
    int direcciones[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}}; // Direcciones diagonales
    char pieza = mat[fila][columna];

    for (i = 0; i < 4; i++) {
        int nuevaFila = fila + direcciones[i][0];
        int nuevaColumna = columna + direcciones[i][1];

        if (nuevaFila >= 0 && nuevaFila < LONG && nuevaColumna >= 0 && nuevaColumna < LONG) {
            if (mat[nuevaFila][nuevaColumna] == ' ') {
                return 1;  // Movimiento válido
            }
        }
    }

    return 0;  // No hay movimiento válido
}
//-------------------------------------------------------------------------------------------------------------------
void MovimientoR(char mat[LONG][LONG]) {
    printf("Turno de Rojas\n");

    int fila, columna, filaN, columnaN, deltaX, deltaY, capturarXP, capturarY, movimientoValido;
    int vectorCaptura[3] = {0, 0, 0}; // [0] indica si hay pieza que capturar, [1] fila, [2] columna
    movimientoValido = 0;

    VerificarCapturaRojas(mat, vectorCaptura);

    if (vectorCaptura[0] == 1) {
        // Si hay una pieza a capturar, forzar a capturarla
        fila = vectorCaptura[1] - 1;  // Ajustamos a índices de 0
        columna = vectorCaptura[2] - 1;
        printf("Pieza Roja (%d, %d) esta obligada a comer\n", fila + 1, columna + 1);  // Se imprime en formato 1-based

        do {
            printf("Donde desea mover la pieza? (primero fila, luego columna):\n");
            scanf("%d %d", &filaN, &columnaN);
            filaN--; columnaN--;  // Ajustamos a índices de 0
            deltaX = columnaN - columna;
            deltaY = filaN - fila;

        } while (filaN < 0 || filaN >= LONG || columnaN < 0 || columnaN >= LONG ||
                 abs(deltaX) != 2 || abs(deltaY) != 2 || mat[filaN][columnaN] != ' ' ||
                 (mat[fila + deltaY / 2][columna + deltaX / 2] != 'n' && mat[fila + deltaY / 2][columna + deltaX / 2] != 'N')); // Captura: la pieza enemiga debe estar en el medio

        // Realizar la captura
        capturarXP = columna + deltaX / 2;
        capturarY = fila + deltaY / 2;
        if (mat[capturarY][capturarXP] == 'n' || mat[capturarY][capturarXP] == 'N') { // Captura de piezas negras o reinas negras
            mat[capturarY][capturarXP] = ' ';  // Eliminar la pieza capturada
            if (mat[fila][columna] == 'R'){
            mat[fila][columna] = ' ';
            mat[filaN][columnaN] = 'R';
            }
            else if (mat[fila][columna] == 'r'){
            mat[fila][columna] = ' ';
            mat[filaN][columnaN] = 'r';
            }

        }
    } else {
        do {
            printf("Ingrese las coordenadas de la pieza que desea mover (primero fila, luego columna):\n");
            scanf("%d%d", &fila, &columna);
            fila--; columna--;  // Ajuste a índices de 0

            if (mat[fila][columna] != 'R' && mat[fila][columna] != 'r') {
                printf("La casilla seleccionada no contiene una pieza Roja valida.\n");
            } else {
                // Si la pieza llega a la última fila, se convierte en reina
                if (fila == LONG - 1 && mat[fila][columna] == 'R') {
                    mat[fila][columna] = 'r';  // Convertimos a reina
                    printf("La pieza Roja se ha convertido en Reina!\n");
                }

                // Verificar si la pieza puede moverse
                if (PuedeMover(mat, fila, columna, 2)) {
                    printf("Donde desea mover la pieza? (primero fila, luego columna):\n");
                    scanf("%d %d", &filaN, &columnaN);
                    filaN--; columnaN--;  // Ajuste a índices de 0
                    deltaX = columnaN - columna;
                    deltaY = filaN - fila;

                    // Lógica de movimiento para pieza normal
                    if (mat[fila][columna] == 'R' && abs(deltaX) == 1 && abs(deltaY) == 1 && mat[filaN][columnaN] == ' ') {
                        mat[fila][columna] = ' ';
                        mat[filaN][columnaN] = 'R';
                        movimientoValido = 1;
                    }
                    // Lógica de movimiento para pieza normal que realiza una captura
                    else if (mat[fila][columna] == 'R' && abs(deltaX) == 2 && abs(deltaY) == 2 &&
                             (mat[fila + deltaY / 2][columna + deltaX / 2] == 'n' || mat[fila + deltaY / 2][columna + deltaX / 2] == 'N') && mat[filaN][columnaN] == ' ') {
                        // Realizar la captura
                        mat[fila][columna] = ' ';
                        mat[filaN][columnaN] = 'R';
                        mat[fila + deltaY / 2][columna + deltaX / 2] = ' ';  // Eliminar la pieza capturada
                        movimientoValido = 1;
                    }
                    // Lógica de movimiento para reina (no debe retroceder)
                    else if (mat[fila][columna] == 'r' && abs(deltaX) == 1 && abs(deltaY) == 1 && mat[filaN][columnaN] == ' ') {
                        mat[fila][columna] = ' ';
                        mat[filaN][columnaN] = 'r';
                        movimientoValido = 1;
                    }
                    // Lógica de captura para reina (también puede capturar a reinas negras)
                    else if (mat[fila][columna] == 'r' && abs(deltaX) == 2 && abs(deltaY) == 2 &&
                             (mat[fila + deltaY / 2][columna + deltaX / 2] == 'n' || mat[fila + deltaY / 2][columna + deltaX / 2] == 'N') && mat[filaN][columnaN] == ' ') {
                        // Realizar la captura
                        mat[fila][columna] = ' ';
                        mat[filaN][columnaN] = 'r';
                        mat[fila + deltaY / 2][columna + deltaX / 2] = ' ';  // Eliminar la pieza capturada
                        movimientoValido = 1;
                    }
                    // Lógica de movimiento hacia atrás para la reina (NO se permite)
                    else if (mat[fila][columna] == 'r' && abs(deltaX) == 1 && abs(deltaY) == -1 && mat[filaN][columnaN] == ' ') {
                        // No permitir movimiento hacia atrás para reinas
                        printf("Las reinas no pueden moverse hacia atras\n");
                    }
                }
            }
        } while (!movimientoValido);  // Repetir hasta que el movimiento sea válido
    }
}
//-------------------------------------------------------------------------------------------------------------------
void MovimientoN(char mat[LONG][LONG]) {
    printf("Turno de Negras\n");

    int fila, columna, filaN, columnaN, deltaX, deltaY, capturarXP, capturarY, movimientoValido;
    int vectorCaptura[3] = {0, 0, 0}; // [0] indica si hay pieza que capturar, [1] fila, [2] columna
    movimientoValido = 0;

    VerificarCapturaNegras(mat, vectorCaptura);

    if (vectorCaptura[0] == 1) {
        // Si hay una pieza a capturar, forzar a capturarla
        fila = vectorCaptura[1] - 1;  // Ajustamos a índices de 0
        columna = vectorCaptura[2] - 1;
        printf("Pieza Negra (%d, %d) esta obligada a comer\n", fila + 1, columna + 1);  // Se imprime en formato 1-based

        do {
            printf("Donde desea mover la pieza? (primero fila, luego columna):\n");
            scanf("%d %d", &filaN, &columnaN);
            filaN--; columnaN--;  // Ajustamos a índices de 0
            deltaX = columnaN - columna;
            deltaY = filaN - fila;

        } while (filaN < 0 || filaN >= LONG || columnaN < 0 || columnaN >= LONG ||
                 abs(deltaX) != 2 || abs(deltaY) != 2 || mat[filaN][columnaN] != ' ' ||
                 (mat[fila + deltaY / 2][columna + deltaX / 2] != 'R' && mat[fila + deltaY / 2][columna + deltaX / 2] != 'r')); // Permitir capturar a piezas rojas o reinas rojas

        // Realizar la captura
        capturarXP = columna + deltaX / 2;
        capturarY = fila + deltaY / 2;
if (mat[capturarY][capturarXP] == 'r' || mat[capturarY][capturarXP] == 'R') {
            mat[capturarY][capturarXP] = ' ';  // Eliminar la pieza capturada
            if (mat[fila][columna] == 'N')
            {
                mat[fila][columna] = ' ';
                mat[filaN][columnaN] = 'N';
            }
            else if (mat[fila][columna] == 'n')
            {
                mat[fila][columna] = ' ';
                mat[filaN][columnaN] = 'n';
            }    // Colocar la pieza negra en la nueva posición
        }
    } else {
        do {
            printf("Ingrese las coordenadas de la pieza que desea mover (primero fila, luego columna):\n");
            scanf("%d%d", &fila, &columna);
            fila--; columna--;  // Ajuste a índices de 0

            if (mat[fila][columna] != 'N' && mat[fila][columna] != 'n') {
                printf("La casilla seleccionada no contiene una pieza Negra válida.\n");
            } else {
                // Si la pieza llega a la primera fila (la del lado opuesto), se convierte en reina
                if (fila == 0 && mat[fila][columna] == 'N') {
                    mat[fila][columna] = 'n';  // Convertimos a reina
                    printf("La pieza Negra se ha convertido en Reina!\n");
                }

                // Verificar si la pieza puede moverse
                if (PuedeMover(mat, fila, columna, 1)) {
                    printf("Donde desea mover la pieza? (primero fila, luego columna):\n");
                    scanf("%d %d", &filaN, &columnaN);
                    filaN--; columnaN--;  // Ajuste a índices de 0
                    deltaX = columnaN - columna;
                    deltaY = filaN - fila;

                    // Lógica de movimiento para pieza normal
                    if (mat[fila][columna] == 'N' && abs(deltaX) == 1 && abs(deltaY) == 1 && mat[filaN][columnaN] == ' ') {
                        mat[fila][columna] = ' ';
                        mat[filaN][columnaN] = 'N';
                        movimientoValido = 1;
                    }
                    // Lógica de movimiento para pieza normal que realiza una captura
                    else if (mat[fila][columna] == 'N' && abs(deltaX) == 2 && abs(deltaY) == 2 &&
                             (mat[fila + deltaY / 2][columna + deltaX / 2] == 'R' || mat[fila + deltaY / 2][columna + deltaX / 2] == 'r') && mat[filaN][columnaN] == ' ') {
                        // Realizar la captura
                        mat[fila][columna] = ' ';
                        mat[filaN][columnaN] = 'N';
                        mat[fila + deltaY / 2][columna + deltaX / 2] = ' ';  // Eliminar la pieza capturada
                        movimientoValido = 1;
                    }
                    // Lógica de movimiento para reina
                    else if (mat[fila][columna] == 'n' && abs(deltaX) == 1 && abs(deltaY) == 1 && mat[filaN][columnaN] == ' ') {
                        mat[fila][columna] = ' ';
                        mat[filaN][columnaN] = 'n';
                        movimientoValido = 1;
                    }
                    // Lógica de captura para reina (también puede capturar a reinas rojas)
                    else if (mat[fila][columna] == 'n' && abs(deltaX) == 2 && abs(deltaY) == 2 &&
                             (mat[fila + deltaY / 2][columna + deltaX / 2] == 'R' || mat[fila + deltaY / 2][columna + deltaX / 2] == 'r') && mat[filaN][columnaN] == ' ') {
                        // Realizar la captura
                        mat[fila][columna] = ' ';
                        mat[filaN][columnaN] = 'n';
                        mat[fila + deltaY / 2][columna + deltaX / 2] = ' ';  // Eliminar la pieza capturada
                        movimientoValido = 1;
                    }
                    // Lógica de movimiento hacia atrás para la reina
                    else if (mat[fila][columna] == 'n' && abs(deltaX) == 1 && abs(deltaY) == -1 && mat[filaN][columnaN] == ' ') {
                        mat[fila][columna] = ' ';
                        mat[filaN][columnaN] = 'n';
                        movimientoValido = 1;
                    }
                }
            }
        } while (!movimientoValido);  // Repetir hasta que el movimiento sea válido
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
