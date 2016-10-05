//
// Created by kraghan on 03/10/16.
//

#include "Fa.h"

void fa_create(struct fa* self, unsigned int alpha_count, unsigned int state_count)
{
    self->alpha_size = alpha_count;
    self->state_size = state_count;

    self->states = NULL;
    states_list_create(self->states);

    self->transitions = NULL;
    transitions_list_create();

}