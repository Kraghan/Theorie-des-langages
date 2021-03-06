//
// Created by Kraghan on 06/10/2016.
//

#include "state_set.h"

void state_set_create(state_set *self, unsigned int capacity, char alpha,
                      unsigned int s)
{
    self->alphaId = alpha;
    self->capacity = capacity;
    self->size = 0;
    self->stateId = s;

    self->states = (state*)malloc(sizeof(state)*capacity);
    unsigned int i;
    for(i = 0; i < capacity; ++i)
    {
        state_create(&self->states[i], 99999);
    }
}

void state_set_remove(state_set *self, unsigned int state)
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
            state_create(&self->states[self->capacity - 1], 99999);
            return;
        }
    }
}

void state_set_add(state_set *self, unsigned int state)
{
    if(self->size == self->capacity)
        return;
    state_create(&self->states[self->size], state);
    ++self->size;
}

void state_set_print(state_set *self, FILE *out)
{
    unsigned int i;
    for(i = 0; i < self->size; ++i)
    {
        fprintf(out,"%u ",self->states[i].id);
    }
}

unsigned int state_set_count(state_set *self)
{
    return self->size;
}

bool state_set_contains(state_set *self, unsigned int state)
{
    unsigned int i;
    for(i = 0; i < self->size; ++i)
    {
        if(self->states[i].id == state)
            return true;
    }
    return false;
}

bool state_set_is_empty(state_set *self)
{
    return self->states[0].id == 99999;
}

bool state_set_is_equal(state_set* first, state_set* second)
{
    unsigned int i = 0;
    for(i = 0; i < first->size; ++i)
    {
        if(!state_set_contains(second,first->states[i].id))
            return false;
    }

    for(i = 0; i < second->size; ++i)
    {
        if(!state_set_contains(first,second->states[i].id))
            return false;
    }

    return true;
}

void state_set_add_set(state_set* self, const state_set* to_add)
{
    unsigned int i;
    for(i = 0; i < to_add->size; ++i)
    {
        if(!state_set_contains(self,to_add->states[i].id))
            state_set_add(self,to_add->states[i].id);
    }
}

