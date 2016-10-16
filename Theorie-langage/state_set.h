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

void stateSetCreate(state_set* self, unsigned int capacity, char alpha, unsigned int state);

void stateSetAdd(state_set* self, unsigned int state);

void stateSetRemove(state_set* self, unsigned int state);

void stateSetPrint(state_set* self, FILE* out);

unsigned int stateSetCount(state_set* self);
#endif //THEORIE_LANGAGE_STATE_SET_H
