#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "tape.h"

struct _s_node {
    tape_elem elem;
    struct _s_node *next;
};

typedef struct _s_node * node_t;

struct _s_tape {
    unsigned int size;
    node_t cursor;  // Puntero al elemento actual
    node_t start;   // Puntero al primer nodo de la cinta
};

static bool invrep(tape_t tape) {
    return (tape != NULL);
}

static node_t create_node(tape_elem e) {
    node_t new_node = malloc(sizeof(struct _s_node));
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static node_t destroy_node(node_t node) {
    free(node);
    return NULL;
}

tape_t tape_create(void) {
    tape_t tape = malloc(sizeof(struct _s_tape));
    tape->cursor = NULL;
    tape->start = NULL; 
    tape->size = 0;
    assert(invrep(tape) && tape_is_empty(tape) && tape_at_start(tape));
    return tape;
}

tape_t tape_rewind(tape_t tape) {
    assert(invrep(tape));
    tape->cursor = tape->start;
    assert(invrep(tape) && tape_at_start(tape));
    return tape;
}


bool tape_at_start(tape_t tape) {
    assert(invrep(tape));
    return tape->cursor == tape->start;
}

bool tape_at_stop(tape_t tape) {
    assert(invrep(tape));
    return tape->cursor == NULL;
}

bool tape_is_empty(tape_t tape) {
    assert(invrep(tape));
    return tape->size == 0u;
}

unsigned int tape_length(tape_t tape) {
    assert(invrep(tape));
    return tape->size;
}

tape_t tape_step(tape_t tape) {
    assert(invrep(tape));
    if (tape->cursor != NULL) {
        tape->cursor = tape->cursor->next;
    }
    assert(invrep(tape));
    return tape;
}


tape_t tape_insertl(tape_t tape, tape_elem e) {
    assert(invrep(tape));
    node_t new_node = create_node(e);
    if (tape->cursor == tape->start){
        new_node->next = tape->start;
        tape->start = new_node;
    } else {
        node_t t_ant = tape->start;
        while(t_ant->next != tape->cursor){
            t_ant = t_ant->next; // avanza mientras se cumplan las cond hasta ubicarse en el nodo anterior al que está apuntando el cursor
        }
        new_node->next = tape->cursor;  // el next del nuevo nodo apuntará al elemento apuntado por el cursor 
        t_ant->next = new_node;         // next apunta al siguiente nodo de t_ant (ubicado en el nodo anterior a tape->cursor) y apunta ahora al nuevo nodo
    }                                   // agregándolo a la izquierda de tape->cursor
    tape->cursor = new_node;
    tape->size++;
    assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape) && e == tape_read(tape));
    return tape;
}

tape_t tape_insertr(tape_t tape, tape_elem e) {
    assert(invrep(tape) && (!tape_at_stop(tape) || tape_is_empty(tape)));
    node_t new_node=create_node(e);
    if (tape->start!= NULL) {
        new_node->next = tape->cursor->next;
        tape->cursor->next = new_node;
        tape->cursor = new_node;
    } else {
        tape->start = new_node;
        tape->cursor = new_node;
    }
    tape->size++;
    assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape) && e == tape_read(tape));
    return tape;
}

tape_t tape_erase(tape_t tape) {
    assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape));
    node_t to_remove = tape->cursor;
    if (tape->cursor == tape->start) {
        tape->start = tape->cursor->next;
        tape->cursor = tape->start;
    } else {
        node_t prev = tape->start;
        while (prev->next != tape->cursor) {
            prev = prev->next;
        }
        prev->next = tape->cursor->next;
        tape->cursor = prev->next;
    }
    to_remove = destroy_node(to_remove);
    tape->size--;
    assert(invrep(tape));
    return tape;
}


/*
la funcion tape_erase no andaria en el caso que el tape tenga un solo elemento
pero en los ejemplos del parcial anda, alta paja cambiarla.
*/

tape_elem tape_read(tape_t tape) {
    assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape));
    return tape->cursor->elem;
}

void tape_dump(tape_t tape) {
    assert(invrep(tape));
    node_t node=tape->start;
    printf("#");
    while (node != NULL) {
        if (node != tape->cursor) {
            printf("-%c-", node->elem);
        } else {
            printf("-[%c]-", node->elem);
        }
        node = node->next;
    }
    if (tape->cursor==NULL) {
        printf("-[]-");
    }
    printf("#\n");
}

tape_t tape_copy(tape_t tape) {
    assert(invrep(tape));
    tape_t copy = tape_create();
    copy->size = 0u;
    tape_t t_aux = tape;
    t_aux = tape_rewind(t_aux);
    node_t copy_node = malloc(sizeof(struct _s_node));
    while(!tape_at_stop(t_aux)){
        if(tape_length(copy) == 0u){
            copy_node = create_node(t_aux->cursor->elem);
            tape_insertl(copy, copy_node->elem);
            t_aux = tape_step(t_aux);
        }else{
            copy_node = create_node(t_aux->cursor->elem);
            tape_insertr(copy, copy_node->elem);
            t_aux = tape_step(t_aux);
        }
    }
    copy = tape_rewind(copy);
    assert(invrep(copy) && copy != tape && !tape_is_empty(copy) && tape_at_start(copy) && tape_length(copy) == tape_length(tape));
    return copy;
}

tape_t tape_destroy(tape_t tape) {
    assert(invrep(tape));
    node_t node=tape->start;
    while (node != NULL) {
        node_t killme=node;
        node = node->next;
        destroy_node(killme);
    }
    free(tape);
    tape = NULL;
    return tape;
}


/* tape_erase: Primero guarda el nodo a eliminar en una variable temporal (erase), 
luego actualiza el puntero de inicio (tape->start) para que apunte al siguiente nodo, y finalmente mueve el cursor al nuevo primer nodo. 
Este proceso asegura que el primer nodo se elimina correctamente de la cinta y que los punteros de la estructura se mantienen coherentes. 
tape_t tape_erase(tape_t tape) {
    assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape));
    node_t erase = tape->cursor;
    if (tape->cursor == tape->start){
        tape->start = tape->cursor->next;
        tape->cursor = tape->start;
    } else {
        node_t n_ant = tape->start;
        while(n_ant->next != tape->cursor){
            n_ant = n_ant->next;
        }
        n_ant->next = tape->cursor->next;  // actualiza el puntero next del nodo anterior (n_ant) para saltar el nodo apuntado por el cursor.
        tape->cursor = n_ant->next;  // mueve el cursor al siguiente nodo después del nodo eliminado.
    }
    destroy_node(erase);
    tape->size--;
    assert(invrep(tape));
    return tape;

*/