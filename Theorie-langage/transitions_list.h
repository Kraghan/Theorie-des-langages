//
// Created by kraghan on 03/10/16.
//

#ifndef THEORIE_LANGAGE_TRANSITIONS_LIST_H
#define THEORIE_LANGAGE_TRANSITIONS_LIST_H
#include "list_node.h"

struct transitions_list
{
    unsigned int size;
    struct list_node* head;
};

void transitions_list_create(struct transitions_list* self);

void transitions_list_destroy(struct transitions_list* self);

void transitions_list_add(struct transitions_list* self, struct state* from, char alpha, struct state* to);

void transitions_list_remove(struct transitions_list* self, struct state* state);

#endif //THEORIE_LANGAGE_TRANSITIONS_LIST_H
