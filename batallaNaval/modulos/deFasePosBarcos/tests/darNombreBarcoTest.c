#include <stdio.h>
#include "../darNombreBarco.c"

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
