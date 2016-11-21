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

void state_create(state *self, unsigned int id);

void state_set_initial(state *self);

void state_set_final(state *self);

#endif //THEORIE_LANGAGE_STATE_H
