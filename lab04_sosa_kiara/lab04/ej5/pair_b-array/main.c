#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */

static
void show_pair(pair_t p) {
    printf("(%d, %d)\n", p.values[0], p.values[1]);
}


int main(void) {
    pair_t p, q;
    // Nuevo par p
    p = pair_new(3, 4);
    // Se muestra el par por pantalla
    printf("p = ");
    show_pair(p);
    // Nuevo para q con elementos de p intercambiados
    q = pair_swapped(p);
    // Se muestra q
    printf("q = ");
    show_pair(q);
    // Se destruyen p y q
    p = pair_destroy(p);
    q = pair_destroy(q);
    return EXIT_SUCCESS;
}

/*
 * I. La funcion show_pair intentaba mostrar el p.fst y p.snd, pero en la estructura no estaban definidos dichos valores.
 * III. Este diseño de TAD no logra el encapsulamiento porque se debe utilizar los indices del arreglo para acceder a ellos, 
 * ademas esto queda claro al tener que haber cambiado las funciones para que funcione correctamente. 
 * De haber logrado el encampsulamiento este deberia haber funcionado con las funciones sin modificarlas.
 */