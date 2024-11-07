#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../header.h"

int numAleatorio(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

