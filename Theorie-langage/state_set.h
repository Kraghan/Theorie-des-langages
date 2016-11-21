//
// Created by Kraghan on 06/10/2016.
//

#ifndef THEORIE_LANGAGE_STATE_SET_H
#define THEORIE_LANGAGE_STATE_SET_H

#include <stdio.h>
#include "state.h"
#include "stdlib.h"
struct state_set
{
    unsigned int size;
    unsigned int capacity;
    unsigned int stateId;
    char alphaId;
    state* states;
};

typedef struct state_set state_set;

void state_set_create(state_set *self, unsigned int capacity, char alpha,
                      unsigned int state);

void state_set_add(state_set *self, unsigned int state);

void state_set_remove(state_set *self, unsigned int state);

void state_set_print(state_set *self, FILE *out);

bool state_set_contains(state_set *self, unsigned int state);

unsigned int state_set_count(state_set *self);
#endif //THEORIE_LANGAGE_STATE_SET_H
