//
// Created by Kraghan on 05/10/2016.
//
#include "state.h"

void state_create(state *self, unsigned int id)
{
    self->is_final = false;
    self->id = id;
    self->is_initial = false;
}

void state_set_initial(state *self)
{
    self->is_initial = true;
}

void state_set_final(state *self)
{
    self->is_final = true;
}