#include <stdio.h>
#include <stdlib.h>
#include "Fa.h"
#include "State_set.h"

typedef struct state_node state_node;
typedef struct fa fa;
typedef struct state state;
typedef struct state_set state_set;

void node_create(state_node* node, size_t state_id)
{
    node->state = state_id;
    node->next = NULL;
}

void set_add(state_set* state_set, size_t state_id)
{
    if(NULL == state_set->first)
    {
        state_node node;
        node_create(&node,state_id);
        state_set->first = &node;
    }
    else
    {
        state_node newNode;
        node_create(&newNode,state_id);
        state_node* node = state_set->first;
        while(NULL != node->next){
            if(node->state == state_id)
                return;
            node = node->next;
        }
        node->next = &newNode;
    }

}

void set_new(state_set* set)
{
    set->first = NULL;
}

void state_create_state(state* state,size_t index)
{
    state->id = index;
    state->is_initial = false;
    state->is_final = false;
}

void fa_create(struct fa *self, size_t alpha_count, size_t state_count)
{
    self->alpha_size = alpha_count;
    self->state_size = state_count;

    self->states = (state*)malloc(sizeof(struct state)*state_count);

    self->transitions = (state_set**)malloc(sizeof(state_set) * state_count);
    unsigned int i;
    for(i = 0; i < alpha_count; i++)
    {
        state_create_state(&(self->states[i]),(size_t)i);
        self->transitions[i] = (state_set*)malloc(sizeof(state_set)*state_count);
        set_new(self->transitions[i]);
    }
}

void fa_destroy(struct fa *self)
{
    free(self->states);
    int i;
    for(i = 0; i < self->state_size ;i++)
    {
        free(self->transitions[i]);
    }
    free(self->transitions);
    self->transitions = NULL;
    self->state_size = 0;
    self->alpha_size = 0;
}

void fa_set_state_initial(struct fa *self, size_t state_id)
{
    unsigned int i;
    for(i = 0; i < self->state_size; i++)
    {
        if(self->states[i].id == state_id)
        {
            self->states[i].is_initial = true;
        }
    }
}

void fa_set_state_final(struct fa *self, size_t state_id)
{
    unsigned int i;
    for(i = 0; i < self->state_size; i++)
    {
        if(self->states[i].id == state_id)
        {
            self->states[i].is_final = true;
        }
    }
}

void fa_add_transition(struct fa *self, size_t state_id_from, char alpha, size_t state_id_to)
{
    unsigned int index2 = 'a' - alpha;
    set_add(&(self->transitions[state_id_from][index2]),state_id_to);
}

void fa_print(struct fa *self, FILE* out)
{
    int i;
    fprintf(out,"Initial states : ");
    for(i = 0; i < self->state_size; i++)
    {
        if(self->states[i].is_initial == true)
            fprintf(out,"%d ",self->states[i].id);
    }

    fprintf(out,"\nFinal states : ");
    for(i = 0; i < self->state_size; i++)
    {
        if(self->states[i].is_final == true)
            fprintf(out,"%d ",self->states[i].id);
    }

    fprintf(out,"\nTransitions : ");
    for(i = 0; i < self->state_size; i++)
    {
        fprintf(out,"\n\t For state %d ",self->states[i].id);
    }
}

int main()
{
    size_t alpha_size = 2;
    size_t state_size = 5;
    fa automate;
    fa_create(&automate,alpha_size,state_size);
    // Insert code
    fa_set_state_initial(&automate,0);
    fa_set_state_initial(&automate,1);

    fa_set_state_final(&automate,1);
    fa_set_state_final(&automate,4);

    fa_add_transition(&automate,0,'a',1);
    fa_add_transition(&automate,0,'a',2);
    fa_add_transition(&automate,0,'a',3);
    fa_add_transition(&automate,1,'b',3);
    fa_add_transition(&automate,2,'a',3);
    fa_add_transition(&automate,2,'b',4);
    fa_add_transition(&automate,3,'a',3);
    fa_add_transition(&automate,3,'b',4);
    fa_add_transition(&automate,4,'a',4);

    fa_print(&automate,stdout);

    fa_destroy(&automate);
    return 0;
}
