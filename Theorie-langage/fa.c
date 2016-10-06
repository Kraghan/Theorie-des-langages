//
// Created by Kraghan on 05/10/2016.
//

#include "fa.h"

void faCreate(fa* self, unsigned int alpha_count, unsigned int state_count)
{
    unsigned int i;
    self->alpha_size = alpha_count;
    self->state_size = state_count;
    self->states = (state*)malloc(sizeof(state)*state_count);
    for(i = 0; i < state_count; ++i)
    {
        stateCreate(&self->states[i],i);
    }

    self->transitions = (state_set*)malloc(sizeof(state_set)*state_count*alpha_count);
    for(i = 0; i < state_count*alpha_count;++i)
    {
        stateSetCreate(&self->transitions[i],state_count,'A'+(i%alpha_count),i/state_count);
    }
}

void faDestroy(fa* self)
{
    free(self->states);

    unsigned int i;
    for(i = 0; i < self->state_size*self->alpha_size;++i)
    {
        free(self->transitions[i].states);
    }
    free(self->transitions);

    self->alpha_size = 0;
    self->state_size = 0;
}

void faSetStateInitial(fa* self, unsigned int state)
{
    unsigned int i;
    for(i = 0; i < self->state_size;++i)
    {
        if(self->states[i].id == state)
        {
            stateSetInitial(&(self->states[i]));
        }
    }
}

void faSetStateFinal(fa* self,unsigned int state)
{
    unsigned int i;
    for(i = 0; i < self->state_size;++i)
    {
        if(self->states[i].id == state)
        {
            stateSetFinal(&(self->states[i]));
        }
    }
}

void faAddTransition(fa* self, unsigned int from, char alpha, unsigned int to)
{
    if(alpha-'a' >= self->alpha_size)
    {
        return;
    }

    unsigned int index = self->alpha_size*from+(alpha-'a');

    stateSetAdd(&self->transitions[index],to);
}

void faPrint(fa* self, FILE* out)
{
    unsigned int i,j,index;

    fprintf(out,"States : \n\t");
    for(i = 0; i < self->state_size;++i)
    {
        fprintf(out,"%u ",self->states[i].id);
    }

    fprintf(out,"\nInitial states : \n\t");
    for(i = 0; i < self->state_size;++i)
    {
        if(self->states[i].is_initial == true)
        {
            fprintf(out,"%u ",self->states[i].id);
        }
    }

    fprintf(out,"\nFinal states : \n\t");
    for(i = 0; i < self->state_size;++i)
    {
        if(self->states[i].is_final == true)
        {
            fprintf(out,"%u ",self->states[i].id);
        }
    }

    fprintf(out,"\nTransitions :");
    for(i = 0; i < self->state_size;++i)
    {
        fprintf(out,"\n\t For state : %u",i);
        for(j = 0; j < self->alpha_size; ++j)
        {
            fprintf(out,"\n\t\t For letter %c : ",'a'+j);
            index = self->alpha_size*i+j;
            stateSetPrint(&self->transitions[index],out);
        }

    }
}