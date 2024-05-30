#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

typedef struct s_list *list;
typedef int list_elem;

/* Constructors */
list empty_list(void);
/* Crea una lista vacia */

list addl(list_elem e, list l);
/* Agrega el elemento e al principio de la lista l */

/* Destroy */
list destroy(list l);
/* Libera memoria en caso de que sea necesario */

/* Operations */
bool is_empty(list l);
/* Devuelve True si l es vacia */

list_elem head(list l);
/* Devuelve el primer elemento de la lista l */
/* PRE: !is_empty(l) */

list tail(list l);
/* Elimina el primer elemento de la lista l */
/* PRE: !is_empty(l) */

list addr(list l, list_elem e);
/* Agrega el elemento e al final de la lista l */

unsigned int length(list l);
/* Devuelve la cantidad de elementos de la lista l */

list concat(list l, list lO);
/* Agrega el final de la lista l todos los elementos de la lista lO en el mismo orden */

list_elem index(list l, unsigned int n);
/* Devuelve el n-esimo elemento de la lista l */
/* PRE: length(l) > n */

list take(list l, unsigned int n);
/* Deja en la lista l solo los primeros n elementos eliminando el resto */

list drop(list l, unsigned int n);
/* Elimina los primeros n elementos de la lista l */

list copy_list(list l);
/* Copia todos los elementos de la lista l en una nueva lista */

#endif