//
// Created by Kraghan on 05/10/2016.
//
#include "state.h"

void stateCreate(state* self,unsigned int id)
{
    self->is_final = false;
    self->id = id;
    self->is_initial = false;
}

void stateSetInitial(state* self)
{
    self->is_initial = true;
}

void stateSetFinal(state* self)
{
    self->is_final = true;
}