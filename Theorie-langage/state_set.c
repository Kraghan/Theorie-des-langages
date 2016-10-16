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

void stateSetRemove(state_set* self, unsigned int state)
{
    if(self->size == 0)
        return;

    unsigned int i,j;
    for(i = 0; i < self->size ; ++i)
    {
        if(state == self->states[i].id)
        {
            // On descend tous les états suivants
            for(j = i; j < self->size ; ++j)
            {
                self->states[j] = self->states[j+1];
            }
            self->size--;
            stateCreate(&self->states[self->capacity-1],99999);
            return;
        }
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

unsigned int stateSetCount(state_set* self)
{
    return self->size;
}