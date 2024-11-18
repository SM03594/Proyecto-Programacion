#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONG 8
#define TAMANO_TABLERO 8
#define ARCHIVO_PARTIDA "partida_guardada.txt"
#define ARCHIVO_PUNTAJES "puntajes.txt"

void CrearMatriz(char mat[LONG][LONG]);
void MostrarMatriz(char mat[LONG][LONG]);
int CargarPartida(char mat[LONG][LONG], int *turnoColor);
void GuardarPartida(char mat[LONG][LONG], int turnoColor);
void Jugar(char mat[LONG][LONG], int *turnoColor);
void MostrarMenu();
void MostrarClasificacion();
void CargarPuntajes();
void GuardarPuntajes();
int VerificarNombre(char *nombre);
void IngresarNombres();
void ActualizarPuntajes(int turnoColor, int puntaje);
int VerificarFinJuego(char mat[LONG][LONG], int finJuego, int turnoColor);

// Funciones de movimiento
void MovimientoR(char mat[LONG][LONG], int *turnoColor);
void MovimientoN(char mat[LONG][LONG], int *turnoColor);

//-------------------------------------------------------------------------------------------------------------------

// Variables globales para manejar los puntajes
typedef struct {
    char nombre[50];
    int puntaje;
} Jugador;

Jugador jugadores[100];
int cantidadJugadores = 0;
//-------------------------------------------------------------------------------------------------------------------

int main() {
    char tablero[LONG][LONG];
    int turnoColor = 0;  // 0 para rojas, 1 para negras
    int opcion;

    // Cargar los puntajes desde el archivo
    CargarPuntajes();

    // Mostrar el menú principal
    while (1) {
        MostrarMenu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                // Iniciar una nueva partida
                IngresarNombres();
                CrearMatriz(tablero);  // Inicializar el tablero
                printf("Iniciando una nueva partida...\n");
                MostrarMatriz(tablero);  // Mostrar el tablero inicial
                Jugar(tablero, &turnoColor);  // Comenzar el juego
                break;

            case 2:
                // Cargar una partida guardada
                if (CargarPartida(tablero, &turnoColor)) {
                    printf("Partida cargada correctamente. Continuando...\n");
                    MostrarMatriz(tablero);  // Mostrar el tablero cargado
                    Jugar(tablero, &turnoColor);  // Continuar el juego cargado
                } else {
                    printf("No hay partidas guardadas. Se iniciara una nueva partida.\n");
                    CrearMatriz(tablero);  // Si no hay partida guardada, crear una nueva
                    MostrarMatriz(tablero);  // Mostrar el tablero inicial
                    Jugar(tablero, &turnoColor);  // Comenzar el juego
                }
                break;

            case 3:
                // Mostrar la tabla de clasificación
                MostrarClasificacion();
                break;

            case 4:
                printf("Saliendo del juego...\n");
                return 0;  // Terminar el programa

            default:
                printf("Opción no valida. Intente de nuevo.\n");
                break;
        }
    }

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------

// Función para mostrar el menú principal
void MostrarMenu() {
    printf("\n------ Menu Principal ------\n");
    printf("1. Iniciar nueva partida\n");
    printf("2. Cargar partida guardada\n");
    printf("3. Tabla de clasificación\n");
    printf("4. Salir\n");
    printf("---------------------------\n");
    printf("Selecciona una opcion: ");
}

//-------------------------------------------------------------------------------------------------------------------

// Función para cargar los puntajes desde el archivo
void CargarPuntajes() {
    FILE *archivo = fopen(ARCHIVO_PUNTAJES, "r");
    if (archivo == NULL) {
        printf("No se pudo cargar la tabla de puntajes.\n");
        return;
    }

    while (fscanf(archivo, "%49[^,], %d\n", jugadores[cantidadJugadores].nombre, &jugadores[cantidadJugadores].puntaje) == 2) {
        cantidadJugadores++;
    }

    fclose(archivo);
}

//-------------------------------------------------------------------------------------------------------------------

// Función para guardar los puntajes en el archivo
void GuardarPuntajes() {
    FILE *archivo = fopen(ARCHIVO_PUNTAJES, "w");
    if (archivo == NULL) {
        printf("No se pudo guardar la tabla de puntajes.\n");
        return;
    }

    for (int i = 0; i < cantidadJugadores; i++) {
        fprintf(archivo, "%s, %d\n", jugadores[i].nombre, jugadores[i].puntaje);
    }

    fclose(archivo);
}
//-------------------------------------------------------------------------------------------------------------------

void MostrarClasificacion() {
    int opcion;

    printf("\n------ Tabla de Clasificacion ------\n");

    // Ordenar los jugadores por puntaje de mayor a menor
    for (int i = 0; i < cantidadJugadores - 1; i++) {
        for (int j = i + 1; j < cantidadJugadores; j++) {
            if (jugadores[i].puntaje < jugadores[j].puntaje) {
                Jugador temp = jugadores[i];
                jugadores[i] = jugadores[j];
                jugadores[j] = temp;
            }
        }
    }

    for (int i = 0; i < cantidadJugadores; i++) {
        printf("%d. %s: %d puntos\n", i + 1, jugadores[i].nombre, jugadores[i].puntaje);
    }

    printf("\nQuieres volver al menu principal? (1 = sí, 0 = no): ");
    scanf("%d", &opcion);
    if (opcion == 0) {
        printf("Saliendo de la tabla de clasificacion.\n");
    }
}
//-------------------------------------------------------------------------------------------------------------------

// Función para ingresar los nombres de los jugadores
void IngresarNombres() {
    char nombreRojo[50], nombreNegro[50];

    // Pedir el nombre del jugador rojo
    printf("Ingrese el nombre del jugador Rojo: ");
    scanf("%s", nombreRojo);

    // Verificar si el nombre está disponible o si ya existe
    if (VerificarNombre(nombreRojo)) {
        strcpy(jugadores[cantidadJugadores].nombre, nombreRojo);
        jugadores[cantidadJugadores].puntaje = 0;  // Iniciar con 0 puntos
        cantidadJugadores++;
    } else {
        char confirmacion;
        printf("El nombre %s ya esta en uso. Es este tu nombre de usuario? (s/n): ", nombreRojo);
        scanf(" %c", &confirmacion);  // El espacio antes de %c es importante para leer correctamente el salto de línea anterior
        if (confirmacion == 'n' || confirmacion == 'N') {
            printf("Elige otro nombre para el jugador Rojo: ");
            scanf("%s", nombreRojo);
            strcpy(jugadores[cantidadJugadores].nombre, nombreRojo);
            jugadores[cantidadJugadores].puntaje = 0;  // Iniciar con 0 puntos
            cantidadJugadores++;
        } else {
            // Si el nombre ya existe, actualizamos el puntaje
            ActualizarPuntajes(nombreRojo, 0);  // No modificamos el puntaje ya que es el inicio del juego
        }
    }

    // Pedir el nombre del jugador negro
    printf("Ingrese el nombre del jugador Negro: ");
    scanf("%s", nombreNegro);

    // Verificar si el nombre está disponible o si ya existe
    if (VerificarNombre(nombreNegro)) {
        strcpy(jugadores[cantidadJugadores].nombre, nombreNegro);
        jugadores[cantidadJugadores].puntaje = 0;  // Iniciar con 0 puntos
        cantidadJugadores++;
    } else {
        char confirmacion;
        printf("El nombre %s ya está en uso. ¿Es este tu nombre de usuario? (s/n): ", nombreNegro);
        scanf(" %c", &confirmacion);
        if (confirmacion == 'n' || confirmacion == 'N') {
            printf("Elige otro nombre para el jugador Negro: ");
            scanf("%s", nombreNegro);
            strcpy(jugadores[cantidadJugadores].nombre, nombreNegro);
            jugadores[cantidadJugadores].puntaje = 0;  // Iniciar con 0 puntos
            cantidadJugadores++;
        } else {
            // Si el nombre ya existe, actualizamos el puntaje
            ActualizarPuntajes(nombreNegro, 0);  // No modificamos el puntaje ya que es el inicio del juego
        }
    }

    GuardarPuntajes();  // Guardar los puntajes después de agregar los jugadores
}

//-------------------------------------------------------------------------------------------------------------------

// Función para verificar si un nombre ya está en uso
int VerificarNombre(char *nombre) {
    for (int i = 0; i < cantidadJugadores; i++) {
        if (strcmp(jugadores[i].nombre, nombre) == 0) {
            return 0;  // Nombre ya en uso
        }
    }
    return 1;  // Nombre disponible
}
//-------------------------------------------------------------------------------------------------------------------

// Función para actualizar los puntajes de los jugadores
void ActualizarPuntajes(int turnoColor, int puntaje) {
    char *nombre;  // Nombre del jugador actual

    // Determinar el nombre del jugador activo según el turno
    if (turnoColor == 0) {  // Jugador Rojo
        nombre = jugadores[0].nombre;  // Suponemos que el jugador rojo es el primero en la lista
    } else {  // Jugador Negro
        nombre = jugadores[1].nombre;  // Suponemos que el jugador negro es el segundo
    }

    // Buscar al jugador en la lista de jugadores
    int encontrado = 0;
    for (int i = 0; i < cantidadJugadores; i++) {
        if (strcmp(jugadores[i].nombre, nombre) == 0) {
            jugadores[i].puntaje += puntaje;  // Sumar los puntos al jugador correspondiente
            encontrado = 1;
            break;
        }
    }

    // Si el jugador no estaba en la lista, lo agregamos con el puntaje inicial
    if (!encontrado) {
        strcpy(jugadores[cantidadJugadores].nombre, nombre);
        jugadores[cantidadJugadores].puntaje = puntaje;
        cantidadJugadores++;
    }

    // Guardar los puntajes en el archivo
    GuardarPuntajes();
}
//-------------------------------------------------------------------------------------------------------------------

// Función para crear y mostrar el tablero inicial
void CrearMatriz(char mat[LONG][LONG]) {
    for (int i = 0; i < LONG; i++) {
        for (int j = 0; j < LONG; j++) {
            if ((i + j) % 2 == 0) {
                mat[i][j] = ' ';  // Casillas vacías
            } else if (i < 3) {
                mat[i][j] = ' ';  // Piezas negras
            } else if (i > 4) {
                mat[i][j] = 'R';  // Piezas rojas
            } else {
                mat[i][j] = ' ';  // Casillas vacías en el medio
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------

// Función para mostrar el tablero de juego
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

// Función para guardar el estado de la partida en un archivo único
void GuardarPartida(char mat[LONG][LONG], int turnoColor) {
    FILE *archivo;

    // Abrir el archivo para escribir los datos de la partida (sobrescribirá cualquier archivo existente)
    archivo = fopen(ARCHIVO_PARTIDA, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar la partida.\n");
        return;
    }

    // Guardar la matriz (tablero de juego)
    for (int i = 0; i < LONG; i++) {
        for (int j = 0; j < LONG; j++) {
            fprintf(archivo, "%c", mat[i][j]);  // Guardar cada pieza del tablero
        }
        fprintf(archivo, "\n");
    }

    // Guardar el turno (quién le toca mover)
    fprintf(archivo, "%d\n", turnoColor);

    fclose(archivo);  // Cerrar el archivo
    printf("Partida guardada en %s.\n", ARCHIVO_PARTIDA);

    // Preguntar si desea continuar o salir
    int opcion;
    printf("\nQuieres continuar jugando o salir?\n");
    printf("1. Continuar jugando\n");
    printf("2. Salir del juego\n");
    printf("Selecciona una opcion: ");
    scanf("%d", &opcion);

    // Opciones: continuar o salir
    if (opcion == 2) {
        printf("Saliendo del juego...\n");
        exit(0);  // Salir del programa
    } else if (opcion == 1) {
        printf("Continuando con el juego...\n");
        return;  // Regresar al juego
    } else {
        printf("Opcion no valida. Continuando con el juego...\n");
    }
}
//-------------------------------------------------------------------------------------------------------------------

// Función que carga el estado de la partida desde un archivo único
int CargarPartida(char mat[LONG][LONG], int *turnoColor) {
    FILE *archivo = fopen(ARCHIVO_PARTIDA, "r");
    if (archivo == NULL) {
        printf("No hay partida guardada. Iniciando una nueva partida...\n");
        return 0;  // Si no se encuentra el archivo, se inicia una nueva partida
    }

    // Cargar la matriz (tablero)
    for (int i = 0; i < LONG; i++) {
        for (int j = 0; j < LONG; j++) {
            // Leer cada carácter y manejar los espacios correctamente
            fscanf(archivo, "%c", &mat[i][j]);  // Sin espacio extra, leer exactamente el carácter
        }
        fscanf(archivo, "%*c");  // Leer el salto de línea después de cada fila
    }

    // Cargar el turno
    fscanf(archivo, "%d", turnoColor);  // Leer el turno desde el archivo

    fclose(archivo);  // Cerrar el archivo
    printf("Partida cargada correctamente.\n");
    return 1;
}
//-------------------------------------------------------------------------------------------------------------------

void Jugar(char mat[LONG][LONG], int *turnoColor) {
    int finJuego = 0;  // Variable que determina si el juego ha terminado

    while (!finJuego) {
        // Alternar los turnos
        if (*turnoColor == 0) {
            MovimientoR(mat, turnoColor);  // Turno de las piezas rojas
        } else {
            MovimientoN(mat, turnoColor);  // Turno de las piezas negras
        }

        // Alternar entre los jugadores (rojo o negro)
        *turnoColor = (*turnoColor == 0) ? 1 : 0;

        // Mostrar el tablero después de cada movimiento
        MostrarMatriz(mat);

        // Preguntar si quiere guardar la partida después de cada turno
        char respuesta;
        printf("Desea guardar la partida? (s/n): ");
        scanf(" %c", &respuesta);
        if (respuesta == 's' || respuesta == 'S') {
            GuardarPartida(mat, *turnoColor);
        }

        // Verificar si el juego ha terminado
        finJuego = VerificarFinJuego(mat, finJuego, *turnoColor);
    }
}
//-------------------------------------------------------------------------------------------------------------------

// Lógica para verificar el fin del juego y asignar el puntaje al jugador contrario
int VerificarFinJuego(char mat[LONG][LONG], int finJuego, int turnoColor) {
    int i, j;
    int contarRojas = 0, contarNegras = 0;

    // Contamos las piezas restantes de cada jugador
    for (i = 0; i < LONG; i++) {
        for (j = 0; j < LONG; j++) {
            if (mat[i][j] == 'R' || mat[i][j] == 'r') {
                contarRojas++;
            }
            if (mat[i][j] == 'N' || mat[i][j] == 'n') {
                contarNegras++;
            }
        }
    }

    // Si un jugador no tiene piezas, ha perdido
    if (contarRojas == 0) {
        printf("Las piezas rojas han sido eliminadas!\n");
        // El jugador negro gana 1 punto
        ActualizarPuntajes(0, 1);  // El jugador rojo (turnoColor 0) ha perdido, el punto va al negro
        return 2;  // Las piezas rojas han perdido
    }
    if (contarNegras == 0) {
        printf("¡Las piezas negras han sido eliminadas!\n");
        // El jugador rojo gana 1 punto
        ActualizarPuntajes(1, 1);  // El jugador negro (turnoColor 1) ha perdido, el punto va al rojo
        return 1;  // Las piezas negras han perdido
    }

    // Verificar si el jugador actual tiene movimientos válidos
    int tieneMovimientos = 0;
    for (i = 0; i < LONG; i++) {
        for (j = 0; j < LONG; j++) {
            if ((turnoColor == 0 && (mat[i][j] == 'R' || mat[i][j] == 'r')) ||  // Piezas rojas
                (turnoColor == 1 && (mat[i][j] == 'N' || mat[i][j] == 'n'))) { // Piezas negras
                if (PuedeMover(mat, i, j, turnoColor)) {
                    tieneMovimientos = 1;
                    break;  // Si al menos una pieza puede moverse, no se declara fin de juego
                }
            }
        }
        if (tieneMovimientos) break;
    }

    // Si el jugador no tiene movimientos, el oponente gana
    if (!tieneMovimientos) {
        printf("El jugador %d no tiene movimientos disponibles!\n", turnoColor == 0 ? 2 : 1);
        // El oponente gana 1 punto
        if (turnoColor == 0) {
            ActualizarPuntajes(1, 1);  // El jugador negro gana
        } else {
            ActualizarPuntajes(0, 1);  // El jugador rojo gana
        }
        return (turnoColor == 0) ? 2 : 1;  // El oponente gana si no tiene movimientos
    }

    return finJuego;  // Si no hay ganador aún, seguimos el juego
}


// Función que verifica si una pieza puede moverse
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
void MovimientoR(char mat[LONG][LONG], int *turnoColor) {
    printf("Turno de Rojas\n");

    int fila, columna, filaN, columnaN, deltaX, deltaY, capturarXP, capturarY, movimientoValido;
    int vectorCaptura[3] = {0, 0, 0}; // [0] indica si hay pieza que capturar, [1] fila, [2] columna
    movimientoValido = 0;

    VerificarCapturaRojas(mat, vectorCaptura);

    if (vectorCaptura[0] == 1) {
        // Si hay una pieza a capturar, forzar a capturarla
        fila = vectorCaptura[1] - 1;  // Ajustamos a índices de 0
        columna = vectorCaptura[2] - 1;
        printf("Pieza Roja (%d, %d) está obligada a comer\n", fila + 1, columna + 1);  // Se imprime en formato 1-based

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
            if (mat[fila][columna] == 'R') {
                mat[fila][columna] = ' ';
                mat[filaN][columnaN] = 'R';
            }
            else if (mat[fila][columna] == 'r') {
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
                // Si la pieza roja llega a la última fila, se convierte en reina
                if (fila == 0 && mat[fila][columna] == 'R') {  // Cambio aquí
                    mat[fila][columna] = 'r';  // Convertimos a reina
                    printf("La pieza Roja se ha convertido en Reina!\n");
                }

                // Verificar si la pieza puede moverse
                if (PuedeMover(mat, fila, columna, 2)) {
                    printf("¿Dónde desea mover la pieza? (primero fila, luego columna):\n");
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
                    // Lógica de movimiento para reina
                    else if (mat[fila][columna] == 'r' && abs(deltaX) == 1 && abs(deltaY) == 1 && mat[filaN][columnaN] == ' ') {
                        mat[fila][columna] = ' ';
                        mat[filaN][columnaN] = 'r';
                        movimientoValido = 1;
                    }
                    // Lógica de captura para reina
                    else if (mat[fila][columna] == 'r' && abs(deltaX) == 2 && abs(deltaY) == 2 &&
                             (mat[fila + deltaY / 2][columna + deltaX / 2] == 'n' || mat[fila + deltaY / 2][columna + deltaX / 2] == 'N') && mat[filaN][columnaN] == ' ') {
                        // Realizar la captura
                        mat[fila][columna] = ' ';
                        mat[filaN][columnaN] = 'r';
                        mat[fila + deltaY / 2][columna + deltaX / 2] = ' ';  // Eliminar la pieza capturada
                        movimientoValido = 1;
                    }
                }
            }
        } while (!movimientoValido);  // Repetir hasta que el movimiento sea válido
    }
}

//----------------------------------------------------------------------------------------------------------------------------
void MovimientoN(char mat[LONG][LONG], int *turnoColor) {
    printf("Turno de Negras\n");

    int fila, columna, filaN, columnaN, deltaX, deltaY, capturarXP, capturarY, movimientoValido;
    int vectorCaptura[3] = {0, 0, 0}; // [0] indica si hay pieza que capturar, [1] fila, [2] columna
    movimientoValido = 0;

    VerificarCapturaNegras(mat, vectorCaptura);

    if (vectorCaptura[0] == 1) {
        // Si hay una pieza a capturar, forzar a capturarla
        fila = vectorCaptura[1] - 1;  // Ajustamos a índices de 0
        columna = vectorCaptura[2] - 1;
        printf("Pieza Negra (%d, %d) está obligada a comer\n", fila + 1, columna + 1);  // Se imprime en formato 1-based

        do {
            printf("Donde desea mover la pieza? (primero fila, luego columna):\n");
            scanf("%d %d", &filaN, &columnaN);
            filaN--; columnaN--;  // Ajustamos a índices de 0
            deltaX = columnaN - columna;
            deltaY = filaN - fila;

        } while (filaN < 0 || filaN >= LONG || columnaN < 0 || columnaN >= LONG ||
                 abs(deltaX) != 2 || abs(deltaY) != 2 || mat[filaN][columnaN] != ' ' ||
                 (mat[fila + deltaY / 2][columna + deltaX / 2] != 'r' && mat[fila + deltaY / 2][columna + deltaX / 2] != 'R')); // Captura: la pieza enemiga debe estar en el medio

        // Realizar la captura
        capturarXP = columna + deltaX / 2;
        capturarY = fila + deltaY / 2;
        if (mat[capturarY][capturarXP] == 'r' || mat[capturarY][capturarXP] == 'R') { // Captura de piezas negras o reinas negras
            mat[capturarY][capturarXP] = ' ';  // Eliminar la pieza capturada
            if (mat[fila][columna] == 'N') {
                mat[fila][columna] = ' ';
                mat[filaN][columnaN] = 'N';
            }
            else if (mat[fila][columna] == 'n') {
                mat[fila][columna] = ' ';
                mat[filaN][columnaN] = 'n';
            }
        }
    } else {
        do {
            printf("Ingrese las coordenadas de la pieza que desea mover (primero fila, luego columna):\n");
            scanf("%d%d", &fila, &columna);
            fila--; columna--;  // Ajuste a índices de 0

            if (mat[fila][columna] != 'N' && mat[fila][columna] != 'n') {
                printf("La casilla seleccionada no contiene una pieza Negra valida.\n");
            } else {
                // Si la pieza roja llega a la última fila, se convierte en reina
                if (fila == 8 && mat[fila][columna] == 'N') {  // Cambio aquí
                    mat[fila][columna] = 'n';  // Convertimos a reina
                    printf("La pieza Negra se ha convertido en Reina!\n");
                }

                // Verificar si la pieza puede moverse
                if (PuedeMover(mat, fila, columna, 2)) {
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
                             (mat[fila + deltaY / 2][columna + deltaX / 2] == 'r' || mat[fila + deltaY / 2][columna + deltaX / 2] == 'R') && mat[filaN][columnaN] == ' ') {
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
                    // Lógica de captura para reina
                    else if (mat[fila][columna] == 'n' && abs(deltaX) == 2 && abs(deltaY) == 2 &&
                             (mat[fila + deltaY / 2][columna + deltaX / 2] == 'r' || mat[fila + deltaY / 2][columna + deltaX / 2] == 'R') && mat[filaN][columnaN] == ' ') {
                        // Realizar la captura
                        mat[fila][columna] = ' ';
                        mat[filaN][columnaN] = 'n';
                        mat[fila + deltaY / 2][columna + deltaX / 2] = ' ';  // Eliminar la pieza capturada
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
                    vectorAux[1] = fila + 1;  // Guardamos la posici�n de la pieza que captura (en formato 1-indexed)
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
