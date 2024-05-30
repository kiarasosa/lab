#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "data.h"

void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

int main(void) {

    data_t messi = {"Leo Messi", 36, 169};
    print_data(messi);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n\n", sizeof(messi.name),
                                         sizeof(messi.age),
                                         sizeof(messi.height),
                                         sizeof(messi.name) + sizeof(messi.age) + sizeof(messi.height));

    unsigned int *p = NULL;
    data_t *q = NULL;
    
    printf("La direccion de memoria del nombre es: %p\n", (void *)messi.name);
    printf("El indice de memoria del nombre es: %lu\n\n", (uintptr_t)messi.name);

    p = &messi.age;
    printf("La direccion de memoria de la edad es: %p\n", (void *) p);
    printf("El indice de memoria de la edad es: %lu\n\n", (uintptr_t) p);

    p = &messi.height;
    printf("La direccion de memoria del peso es: %p\n", (void *) p);
    printf("El indice de memoria del peso es: %lu\n\n", (uintptr_t) p);

    q = &messi;
    printf("La direccion de memoria de la data es: %p\n", (void *) p);
    printf("El indice de memoria de la data es: %lu\n\n", (uintptr_t) q);


    
        return EXIT_SUCCESS;
}

