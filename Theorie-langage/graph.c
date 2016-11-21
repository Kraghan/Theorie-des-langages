//
// Created by kraghan on 17/10/16.
//

#include "graph.h"

void graph_depth_first_search(const graph *self, unsigned int state,
                              bool *visited)
{
    visited[state] = true;
    unsigned int i;
    for(i = 0; i < self->states; ++i)
    {
        if(self->adjacentList[state*self->states+i] && !visited[i])
        {
            graph_depth_first_search(self, i, visited);
        }
    }
}

bool graph_has_path(const graph *self, unsigned int from, unsigned int to)
{
    bool* visited = (bool*) malloc(self->states*sizeof(bool));
    unsigned int i = 0;
    for(i = 0; i < self->states; ++i)
    {
        visited[i] = false;
    }
    graph_depth_first_search(self, from, visited);
    bool result = visited[to];
    free(visited);
    return result;
}

void graph_create_from_fa(graph *self, const struct fa *fa, bool inverted)
{
    self->adjacentList = (bool*)malloc(fa->state_size*fa->state_size*sizeof(bool));
    self->states = fa->state_size;
    unsigned int i,j,k;
    for(i = 0; i < self->states; ++i)
    {
        for(j = 0; j < fa->state_size; ++j)
        {
            if(!inverted)
                self->adjacentList[j*self->states+i] = false;
            else
                self->adjacentList[i*self->states+j] = false;
            for (k = 0; k < fa->alpha_size; ++k)
            {
                if (state_set_contains(&fa->transitions[j * fa->alpha_size + k],
                                       i))
                {
                    if(!inverted)
                        self->adjacentList[j*self->states+i] = true;
                    else
                        self->adjacentList[i*self->states+j] = true;
                }

            }
        }

    }
}

void graph_destroy(graph *self)
{
    free(self->adjacentList);
    self->states = 0;
}

void graph_print(const graph *self, FILE *out)
{
    fprintf(out,"Graph of %u states : \n",self->states);
    unsigned int i,j;
    for(i = 0; i < self->states; ++i)
    {
        for(j = 0; j < self->states; ++j)
        {
            if(self->adjacentList[i*self->states+j])
            {
                fprintf(out,"\t- Transitions from %u to %u \n",i,j);
            }
        }
    }

    bool* visited;
    visited = (bool*) malloc(sizeof(bool)*self->states);
    for(i = 0; i < self->states; ++i)
    {
        visited[i] = false;
    }
    graph_depth_first_search(self, 0, visited);
    for(i = 0; i < self->states; ++i)
    {
        if(visited[i])
        {
            fprintf(stdout,"State %u reachable\n",i);
        }
    }

    free(visited);
}