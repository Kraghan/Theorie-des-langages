//
// Created by kraghan on 03/10/16.
//

#include "states_list.h"

void states_list_create(struct states_list* self)
{
    self->size = 0;
    self->head = NULL;
}

void states_list_destroy(struct states_list* self)
{
    unsigned int i;
    struct state_node* node = self->head;
    struct state_node* nextNode = NULL;
    for(i = 0; i < self->size; ++i)
    {
        nextNode = node->next;
        free(node);
        node = nextNode;
    }
    if(node != NULL)
        free(node);
}

void states_list_add(struct states_list* self, struct state* state)
{
    struct state_node* newNode = NULL;
    state_node_create(newNode,state);

    if(self->head == NULL)
    {
        self->size = 1;
        self->head = newNode;
    }
    else
    {
        unsigned int i;

        struct state_node* node;
        node = self->head;

        for(i = 0; i < self->size; ++i)
        {
            if(node->state->id == state->id)
                return;
            node = node->next;
        }
        if(node->next == NULL)
        {
            node->next = newNode;
            self->size++;
        }
    }
}

void states_list_remove(struct states_list* self, struct state *state)
{

}