//
// Created by Kraghan on 06/10/2016.
//

#include "state_set.h"

void stateSetCreate(state_set* self, unsigned int capacity, char alpha, unsigned int s)
{
    self->alphaId = alpha;
    self->capacity = capacity;
    self->size = 0;
    self->stateId = s;

    self->states = (state*)malloc(sizeof(state)*capacity);
    unsigned int i;
    for(i = 0; i < capacity; ++i)
    {
        stateCreate(&self->states[i],99999);
    }
}

void stateSetAdd(state_set* self, unsigned int state)
{
    if(self->size == self->capacity)
        return;
    stateCreate(&self->states[self->size],state);
    ++self->size;
}

void stateSetPrint(state_set* self, FILE* out)
{
    unsigned int i;
    for(i = 0; i < self->size; ++i)
    {
        fprintf(out,"%u ",self->states[i].id);
    }
}