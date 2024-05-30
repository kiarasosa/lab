#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    if (x >= 0) {
    y = x;
    } else {
    y = -x;
    }
}

int main(void) {
    int a=0, res=0;
    a = -10;
    absolute(a, res);
    printf("%d\n", res);
    
    return EXIT_SUCCESS;
}

/*
El valor que se imprime por pantalla en la definición del teórico es 10.
En C, el valor que se muestra por pantalla es 0 (valor original de res).
*/
