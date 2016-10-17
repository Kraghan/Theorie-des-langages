//
// Created by Kraghan on 05/10/2016.
//

#ifndef THEORIE_LANGAGE_FA_H
#define THEORIE_LANGAGE_FA_H

#include "state.h"
#include "state_set.h"
#include <stdio.h>
#include <stdlib.h>

struct fa{
    unsigned int alpha_size;
    unsigned int state_size;
    state* states;
    state_set* transitions;
};

typedef struct fa fa;

bool faAddState(fa* self, unsigned int state);

int faGetStateIndex(fa* self, unsigned int state);

void faCreate(fa* self, unsigned int alpha_count, unsigned int state_count);

void faDestroy(fa* self);

void faSetStateInitial(fa* self, unsigned int state);

void faSetStateFinal(fa* self, unsigned int state);

void faAddTransition(fa* self, unsigned int from, char alpha, unsigned int to);

void faPrint(fa* self, FILE* out);

void faRemoveTransition(fa* self, unsigned int from, char alpha, unsigned int to);

void faRemoveState(fa* self, unsigned int state);

unsigned int faCountTransitions(const fa* self);

bool faIsDeterministic(const fa* self);

bool faIsComplete(const fa* self);

void faMakeComplete(fa* self);

void faMergeStates(fa* self, unsigned int state1, unsigned int state2);

#endif //THEORIE_LANGAGE_FA_H
