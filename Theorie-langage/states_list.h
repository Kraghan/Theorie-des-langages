//
// Created by kraghan on 03/10/16.
//

#ifndef THEORIE_LANGAGE_STATES_LIST_H_H
#define THEORIE_LANGAGE_STATES_LIST_H_H

#include <stdio.h>
#include <stdlib.h>
#include "state_node.h"

struct states_list
{
    unsigned int size;
    struct state_node* head;
};

void states_list_create(struct states_list* self);

void states_list_destroy(struct states_list* self);

void states_list_add(struct states_list* self, struct state* state);

void states_list_remove(struct states_list* self, struct state* state);

#endif //THEORIE_LANGAGE_STATES_LIST_H_H
