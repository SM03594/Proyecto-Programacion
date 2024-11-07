#include <stdio.h>
#include <time.h>

#include "../../header.h"
#include "../fasePosBarcos.c"

#define LONGITUD 10
#define LONGCELDA 2

int main(void)
{   
    srand(time(NULL));

    int numBarcos = 5;

    int vecBarcos[numBarcos], 
        matrizJug[LONGITUD][LONGITUD][LONGCELDA] = {0},
        matrizComp[LONGITUD][LONGITUD][LONGCELDA] = {0}
    ;

    for(int i=0; i<numBarcos; i++)
    {
        vecBarcos[i] = numBarcos - i;
    }

    fasePosBarcos(LONGITUD, numBarcos, vecBarcos, matrizJug, matrizComp);

    return 0;
}


