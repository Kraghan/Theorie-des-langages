//
// Created by kraghan on 03/10/16.
//

#ifndef THEORIE_LANGAGE_STATE_NODE_H
#define THEORIE_LANGAGE_STATE_NODE_H

#include "state.h"
#include <stdio.h>
#include <stdlib.h>

struct state_node
{
    struct state_node* next;
    struct state* state;
};

void state_node_create(struct state_node* self, struct state* state);

#endif //THEORIE_LANGAGE_STATE_NODE_H
