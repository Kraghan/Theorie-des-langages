//
// Created by Kraghan on 05/10/2016.
//

#include "fa.h"

unsigned int faCountState(fa* self)
{
    unsigned int i;
    for(i = 0; i < self->state_size; ++i)
    {
        if(self->states[i].id == 99999)
        {
            return i;
        }
    }
    return i;
}

// Return -1 if not found
int faGetStateIndex(fa* self, unsigned int state)
{
    int i;
    for(i = 0; i < self->state_size; ++i)
    {
        if(self->states[i].id == state)
        {
            return i;
        }
    }
    return -1;
}

bool faAddState(fa* self, unsigned int state)
{
    if(faGetStateIndex(self,state) != -1)
    {
        fprintf(stderr,"\nWarning : Can't add state %u. Cause : Already in.\n",state);
        return false;
    }

    unsigned int i;
    for(i = 0; i < self->state_size; ++i)
    {
        if(self->states[i].id == 99999)
        {
            self->states[i].id = state;
            return true;
        }
    }
    fprintf(stderr,"\nError : Can't add state. Cause : State limit reach.\n");
    return false;
}

void faCreate(fa* self, unsigned int alpha_count, unsigned int state_count)
{
    unsigned int i;
    self->alpha_size = alpha_count;
    self->state_size = state_count;
    self->states = (state*)malloc(sizeof(state)*state_count);
    for(i = 0; i < state_count; ++i)
    {
        stateCreate(&self->states[i],99999);
    }

    self->transitions = (state_set*)malloc(sizeof(state_set)*state_count*alpha_count);
    for(i = 0; i < state_count*alpha_count;++i)
    {
        stateSetCreate(&self->transitions[i],state_count,'a'+(i%alpha_count),i/state_count);
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
        fprintf(stderr,"\nError : Can't add transition. Cause : Alpha isn't in possible transitions.\n");
        return;
    }

    int indexFrom = faGetStateIndex(self,from);
    if(indexFrom == -1)
    {
        fprintf(stderr,"\nError : Can't add transition. Cause : From isn't in possible states.\n");
        return;
    }

    unsigned int index = self->alpha_size*indexFrom+(alpha-'a');
    if(stateSetContains(&self->transitions[index],to))
    {
        fprintf(stderr,"\nError : Can't add transition %u to %u by %c. Cause : Already in.\n",from,to,alpha);
        return;
    }
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
        fprintf(out,"\n\t For state : %u",self->states[i].id);
        for(j = 0; j < self->alpha_size; ++j)
        {
            fprintf(out,"\n\t\t For letter %c : ",'a'+j);
            index = self->alpha_size*i+j;
            stateSetPrint(&self->transitions[index],out);
        }

    }

    if(faIsDeterministic(self))
    {
        fprintf(out,"\nIs deterministic");
    }
    else
    {
        fprintf(out,"\nIs not deterministic");
    }

    if(faIsComplete(self))
    {
        fprintf(out,"\nIs complete");
    }
    else
    {
        fprintf(out, "\nIs not complete\n");
    }

}

void faRemoveTransition(fa* self, unsigned int from, char alpha, unsigned int to)
{
    if(alpha-'a' >= self->alpha_size)
    {
        fprintf(stderr,"\nError : Can't remove transition. Cause : alpha isn't in possible transitions.\n");
        return;
    }

    int indexFrom = faGetStateIndex(self,from);
    if(indexFrom == -1)
    {
        fprintf(stderr,"\nError : Can't remove transition. Cause : From isn't in possible states.\n");
        return;
    }

    unsigned int index = self->alpha_size*indexFrom+(alpha-'a');

    stateSetRemove(&self->transitions[index],to);
}

void faRemoveState(fa* self, unsigned int state)
{
    int stateIndex = faGetStateIndex(self,state);

    if(stateIndex == -1)
    {

        fprintf(stderr,"\nWarning : Can't remove state %u. Cause : Isn't in states list.\n",state);
        return;
    }

    unsigned int i,j;
    // Je supprime toutes les transitions qui vont vers l'état
    for(i = 0; i < self->state_size; ++i)
    {
        int indexFrom = faGetStateIndex(self,self->states[i].id);
        if(indexFrom == -1)
        {
            continue;
        }
        for(j = 0; j < self->alpha_size; ++j)
        {
            unsigned int index = self->alpha_size*indexFrom+j;
            stateSetRemove(&self->transitions[index],state);
        }
    }

    // Je supprime toutes les transitions qui sortent de l'état
    for(i = 0; i < self->alpha_size; ++i)
    {
        unsigned int index = self->alpha_size*stateIndex+i;
        free(self->transitions[index].states);
    }
    for(i = (unsigned int)stateIndex; i < self->state_size-1; ++i)
    {
        for(j = 0; j < self->alpha_size; ++j)
        {
            self->transitions[i*self->alpha_size+j] = self->transitions[i*self->alpha_size+j+self->alpha_size];
        }
    }

    // Je supprime l'état de la liste
    for(i = (unsigned int)stateIndex; i < self->state_size-1;++i)
    {
        self->states[i] = self->states[i+1];
    }
    self->state_size--;
}

unsigned int faCountTransitions(const fa* self)
{
    unsigned int i,sum = 0;
    for(i = 0; i < self->state_size*self->alpha_size; ++i)
    {
        sum += stateSetCount(&self->transitions[i]);
    }
    return sum;
}

bool faIsDeterministic(const fa* self)
{
    unsigned int i,j;
    for(i = 0; i < self->state_size; ++i)
    {
        for(j = 0; j < self->alpha_size; ++j)
        {
            if(stateSetCount(&self->transitions[i*self->alpha_size + j]) > 1)
                return false;
        }
    }
    return true;
}

bool faIsComplete(const fa* self)
{
    unsigned int i,j,nombreDeTransition;
    for(i = 0; i < self->state_size; ++i)
    {
        for(j = 0; j < self->alpha_size; ++j)
        {
            nombreDeTransition = stateSetCount(&self->transitions[i*self->alpha_size + j]);
            if(nombreDeTransition > 1 || nombreDeTransition == 0)
                return false;
        }
    }
    return true;
}

void faMakeComplete(fa* self)
{
    if(!faIsDeterministic(self))
    {
        fprintf(stderr,"\nError : Can't make complete. Cause : non deterministic.\n");
        return;
    }
    if(faIsComplete(self))
    {
        fprintf(stderr,"\nWarning : Can't make complete. Cause : Already complete.\n");
        return;
    }
    if(!faAddState(self,99998))
    {
        if(faGetStateIndex(self,99998) == -1)
        {
            fprintf(stderr,"\nError : Can't make complete. Cause : States limit reach.\n");
            return;
        }
        else
        {
            fprintf(stderr,"\nError : Can't make complete. Cause : state 99998 already in.\n");
            return;
        }
    }
    unsigned int i,j,nombreDeTransition;
    for(i = 0; i < self->state_size; ++i)
    {
        for(j = 0; j < self->alpha_size; ++j)
        {
            nombreDeTransition = stateSetCount(&self->transitions[i*self->alpha_size + j]);
            if(nombreDeTransition == 0)
                stateSetAdd(&self->transitions[i*self->alpha_size + j],99998);
        }
    }
}

void faMergeStates(fa* self, unsigned int state1, unsigned int state2)
{
    int indexState1 = faGetStateIndex(self,state1);
    if(indexState1 == -1)
    {
        fprintf(stderr,"\nError : Can't merge states %u and %u. Cause : state %u doesn't exist.\n",state1,state2,state1);
        return;
    }
    int indexState2 = faGetStateIndex(self,state2);
    if(indexState2 == -1)
    {
        fprintf(stderr,"\nError : Can't merge states %u and %u. Cause : state %u doesn't exist.\n",state1,state2,state2);
        return;
    }

    if(state1 == state2)
    {
        fprintf(stderr,"\nWarning : Can't merge states %u and %u. Cause : Same state.\n",state1,state2,state2);
        return;
    }

    unsigned int i,j,k;

    // J'ajoute toutes les transitions partant de state2 à state1
    for(i = 0; i < self->alpha_size;++i)
    {
        for(j = 0; j < self->transitions[indexState2*self->alpha_size+i].size;++j)
        {
            faAddTransition(self, state1, 'a' + i,self->transitions[indexState2*self->alpha_size+i].states[j].id);
        }
    }

    // J'ajoute toutes les transitions arrivant à state2 à state1
    for(i = 0; i < self->alpha_size;++i)
    {
        for(j = 0; j < self->alpha_size;++j)
        {
            for(k = 0; k < self->transitions[i*self->alpha_size+j].size;++k)
            {
                if(self->transitions[i*self->alpha_size+j].states[k].id == state2)
                    faAddTransition(self, self->states[i].id, 'a' + j,state1);
            }
        }
    }

    // J'affecte les propriétés final et initial de state2 à state1
    if(self->states[indexState2].is_final)
        self->states[indexState1].is_final = true;
    if(self->states[indexState2].is_initial)
        self->states[indexState1].is_initial = true;

    // Je supprime state2
    faRemoveState(self,state2);
}