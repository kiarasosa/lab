#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "counter.h"

struct _counter {
    unsigned int count;
};

/* Constructors */
counter counter_init(void) {
    counter c = malloc(sizeof(struct _counter));
    c->count = 0u;
    return c;
}

void counter_inc(counter c) {
    c->count++;
}

/* Operations */
bool counter_is_init(counter c) {
    return c->count == 0u;
}

void counter_dec(counter c) {
    assert(!counter_is_init(c));
    c->count--;
}

counter counter_copy(counter c) {
    counter copy = malloc(sizeof(struct _counter));
    copy->count = c->count;
    return copy;
}

void counter_destroy(counter c) {
    free(c);
    c = NULL;
}