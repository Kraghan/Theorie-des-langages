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

void faCreate(fa* self, unsigned int alpha_count, unsigned int state_count);

void faDestroy(fa* self);

void faSetStateInitial(fa* self, unsigned int state);

void faSetStateFinal(fa* self, unsigned int state);

void faAddTransition(fa* self, unsigned int from, char alpha, unsigned int to);

void faPrint(fa* self, FILE* out);

#endif //THEORIE_LANGAGE_FA_H
