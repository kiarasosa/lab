#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    struct s_node **array;
    unsigned int min_priority;
    unsigned int size;
};

struct s_node {
    unsigned int value;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    
    new_node->value = e;
    new_node->next = NULL;

    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    node->next = NULL;
    free(node);
    node = NULL;

    return node;
}


static bool invrep(pqueue q) {
    if(q->array == NULL && q->size != 0) return false;
    else if(q->array != NULL && q->size == 0) return false;
    else return true;
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue q = NULL;
    
    q = malloc(sizeof(struct s_pqueue));
    q->array = NULL;
    q->min_priority = min_priority;
    q->size = 0;

    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e);

    assert(priority <= q->min_priority);

    if(q->array == NULL) {
        q->array = calloc(q->min_priority, sizeof(struct s_node));
        q->array[priority] = new_node;
    }
    else {
        if(q->array[priority] == NULL) {
            q->array[priority] = new_node;
        }
        else {
            struct s_node *p = q->array[priority];
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = new_node;
        }
    }
    q->size++;

    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    return (q->size == 0);
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));

    unsigned int i = 0;
    struct s_node *p = q->array[i];
    while(p == NULL) {
        i++;
        p = q->array[i];
    }

    return q->array[i]->value;
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    
    unsigned int i = 0;
    struct s_node *p = q->array[i];
    while(p == NULL) {
        i++;
        p = q->array[i];
    }

    return i;
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    
    unsigned int i = 0;
    struct s_node *p = q->array[i];
    while(p == NULL) {
        i++;
        p = q->array[i];
    }

    if(q->array[i]->next == NULL) {
        free(q->array[i]);
        q->array[i] = NULL;
    }
    else {
        q->array[i] = q->array[i]->next;
        p->next = NULL;
        free(p);
    }
    q->size--;

    if(q->size == 0) q->array = NULL;

    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *p = NULL;

    if(q->array == NULL) {
        free(q);
        q = NULL;
    }
    else {
        for(unsigned int i = 0; i < q->min_priority; i++) {
            if(q->array[i] != NULL) {
                while(q->array[i] != NULL) {
                    p = q->array[i];
                    q->array[i] = q->array[i]->next;
                    destroy_node(p);
                }
            }
        }
    }
    

    return q;
}