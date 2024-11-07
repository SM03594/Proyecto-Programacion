#include <stdio.h>
#include "../header.h"

char* darNombreBarco(int longBarco)
{
    char* nombreBarco;

    switch (longBarco)
    {
    case 5:
        nombreBarco = "Portaviones";
        break;

    case 4:
        nombreBarco = "Crucero";
        break;
    
    case 3:
        nombreBarco = "Destructor";
        break;
    
    case 2:
        nombreBarco = "Submarino";
        break;
    
    case 1:
        nombreBarco = "Lancha";
        break;
    }

    return nombreBarco;
}

