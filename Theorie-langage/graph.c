//
// Created by kraghan on 17/10/16.
//

#include "graph.h"

void graphDepthFirstSearch(const graph* self, unsigned int state, bool* visited)
{

}

bool graphHasPath(const graph* self, unsigned int from, unsigned int to)
{
    // Djikstra
    return false;
}

void graphCreateFromFa(graph* self, const struct fa* fa, bool inverted)
{
    self->adjacentList = (bool*)malloc(fa->state_size*fa->state_size*sizeof(bool));
    self->states = fa->state_size;
    unsigned int i,j,k;
    for(i = 0; i < self->states; ++i)
    {
        for(j = 0; j < fa->state_size; ++j)
        {
            if(inverted)
                self->adjacentList[j*self->states+i] = false;
            else
                self->adjacentList[i*self->states+j] = false;
            for (k = 0; k < fa->alpha_size; ++k)
            {
                if (stateSetContains(&fa->transitions[j*fa->alpha_size+k],i))
                {
                    if(inverted)
                        self->adjacentList[j*self->states+i] = true;
                    else
                        self->adjacentList[i*self->states+j] = true;
                }

            }
        }

    }
}