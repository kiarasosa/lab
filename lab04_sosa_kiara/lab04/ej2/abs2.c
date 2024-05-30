#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void absolute(int x, int *y) {
    if (x >= 0) {
    *y = x;
    } else {
    *y = -x;
    }
}

int main(void) {
    int a=0, res=0; 
    a = -10;
    absolute(a, &res);
    printf("%d\n", res);
    assert(res >= 0 && (res == a || res == -a));
    return EXIT_SUCCESS;
}

/*
El parámetro int *y de absolute es de tipo in, (no se modifica 
dentro de la función) sólo se modifica el valor al que apunta.
C tiene disponibles sólo parametros in para sus funciones.
*/