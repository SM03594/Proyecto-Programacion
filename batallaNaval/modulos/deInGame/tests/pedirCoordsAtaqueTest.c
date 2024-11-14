#include <stdio.h>
#include "../../../header.h"

#include "../pedirCoordsAtaque.c"

int main(void)
{
    int filas=10, cols=12, coordsAtaque[2];

    pedirCoordsAtaque(coordsAtaque, filas, cols);

    printf("CoordsAtaque = (%d, %d)", coordsAtaque[0], coordsAtaque[1]);

    return 0;
}