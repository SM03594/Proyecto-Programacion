#include <stdio.h>
#include "../../../header.h"

int main(void)
{
    int cantBarcos = 5;
    char* nombreDeBarco;

    for(int i=0; i<cantBarcos; i++)
    {
        nombreDeBarco = darNombreBarco((cantBarcos - i));
        printf("%d Barco: %s \n", i+1, nombreDeBarco);
    }

    return 0;
}
