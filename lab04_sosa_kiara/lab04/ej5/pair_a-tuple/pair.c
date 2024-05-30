#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pair.h"

pair_t pair_new(int x, int y){
    pair_t p;
        p.fst = x;
        p.snd = y;

        assert(p.fst == x && p.snd == y);
        return p;
}

int pair_first(pair_t p){
    assert(sizeof(p) == sizeof(pair_t));
    return p.fst;
}   

int pair_second(pair_t p){
    assert(sizeof(p) == sizeof(pair_t));
    return p.snd;
}

pair_t pair_swapped(pair_t p){
    assert(sizeof(p) == sizeof(pair_t));
    pair_t q = pair_new(p.snd, p.fst);
    assert(pair_first(q) == pair_second(p) && pair_second(q) == pair_first(p));
    return q;
}

pair_t pair_destroy(pair_t p){
    return p;
}