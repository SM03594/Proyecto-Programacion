#include <stdio.h>
#include "../pedirCoords.c"

int main(void)
{
    int coordsVec[3], longitud, reps;

    longitud = 10;
    reps = 5;

    for(int i=0; i<reps; i++)
    {
        pedirCoords(coordsVec, longitud);
        printf("\nTest %d eje:%d fila:%d col:%d\n\n", i+1, coordsVec[0], coordsVec[1], coordsVec[2]);   
    }
    
    return 0;
}