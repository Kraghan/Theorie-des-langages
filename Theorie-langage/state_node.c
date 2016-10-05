//
// Created by kraghan on 03/10/16.
//

#include "state_node.h"

void state_node_create(struct state_node* self, struct state* state)
{
    self->next = NULL;
    self->state = state;
}