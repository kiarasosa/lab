#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    unsigned int size; 
    struct s_node *top;  // apunta al primer elemento de la pila 
};

struct s_node {
    pstack_elem elem;
    priority_t priority;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    node->next = NULL;
    free(node);
    assert(node == NULL);
    return node;
}


static bool invrep(pstack s) {
    return s != NULL;
}

pstack pstack_empty(void) {
    pstack s=NULL;
    s = malloc(sizeof(struct s_pstack));
    s->top = NULL;
    s->size = 0u;
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);
    if (new_node == NULL){
        return NULL;
    }
         // Inicializar la pila si es NULL
    if (s == NULL) {
        s = (pstack)malloc(sizeof(struct s_pstack));
        if (s == NULL) {
            free(new_node); // Liberar la memoria del nuevo nodo si falla la asignación de la pila
            return NULL;    // Retornar NULL indicando fallo en la asignación de la pila
        }
        s->top = NULL; // Inicializar el campo top de la nueva pila
        s->size = 1;
    } 
    
    if (s->top == NULL || s->top->priority < priority){ // el nuevo nodo se convierte en el primer nodo d la pila :)
        new_node->next = s->top;
        s->top = new_node;
    } else {
        struct s_node *p = s->top;
        while (p->next != NULL && p->next->priority >= priority){
            p = p->next; // avanza el nodo mientras se cumplan las cond
        }
        new_node->next = p->next; // cuando se encuentra la posición correcta, next de new_node apunta al siguiente nodo de p
        p->next = new_node;       // se establece el nuevo nodo según la prioridad 
    }
    s->size++;
    return s;
}


bool pstack_is_empty(pstack s) {
    assert(invrep(s));
    return s->top == NULL;
}

pstack_elem pstack_top(pstack s) {
    assert(s != NULL && s->top != NULL);
    return s->top->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(s != NULL && s->top != NULL);
    return s->top->priority;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(s != NULL && s->top != NULL);
    if (pstack_is_empty(s)){
        return NULL;
    }
    struct s_node *s_aux = s->top;
        s->top = s->top->next;
        free(s_aux);
    return s;
}
pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *node = s->top;
    while (node != NULL) {
        struct s_node *killme = node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(s);
    s = NULL;
    return s;
}
