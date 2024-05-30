
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_node {
    pstack_elem elem;
    priority_t priority;
    struct s_node *next;
};

struct s_pstack {
    struct s_node *top;
    size_t size;
    priority_t max_priority;
};

static struct s_node * create_node(pstack_elem e,priority_t priority) {
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    return NULL;
}


static bool invrep(pstack s) {
    return s != NULL;
}

pstack pstack_empty(priority_t max_priority) {
    pstack s=NULL;
    s = malloc(sizeof(struct s_pstack));
    assert(s != NULL);
    s->top = NULL;
    s->size = 0;
    s->max_priority = max_priority;
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    assert(priority <= s->max_priority);

    struct s_node *new_node = create_node(e, priority);
    if (s->top == NULL || s->top->priority < priority) {
        new_node->next = s->top;
        s->top = new_node;
    } else {
        struct s_node *current = s->top;
        while (current->next != NULL && current->next->priority >= priority) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    s->size++;    
    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    assert(invrep(s));
    return s->size == 0;
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    return s->top->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    return s->top->priority;
}

size_t pstack_size(pstack s) {
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    struct s_node *node_to_remove = s->top;
    s->top = s->top->next;
    node_to_remove = destroy_node(node_to_remove);
    s->size--;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
 while (!pstack_is_empty(s)) {
        s = pstack_pop(s);
    }
    free(s);
    s = NULL;
    return s;
}
