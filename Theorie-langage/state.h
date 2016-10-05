//
// Created by Kraghan on 05/10/2016.
//

#ifndef THEORIE_LANGAGE_STATE_H
#define THEORIE_LANGAGE_STATE_H


#include <stdbool.h>

struct state{
    bool is_initial;
    bool is_final;
    unsigned int id;
};

typedef struct state state;

void stateCreate(state* self,unsigned int id);

void stateSetInitial(state* self);

void stateSetFinal(state* self);

#endif //THEORIE_LANGAGE_STATE_H
