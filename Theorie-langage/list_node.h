//
// Created by kraghan on 04/10/16.
//

#ifndef THEORIE_LANGAGE_LIST_NODE_H
#define THEORIE_LANGAGE_LIST_NODE_H

#include "states_list.h"

struct list_node
{
    char index_letter;
    unsigned int index_state;
    struct list_node* next;
    struct states_list* list;
};

void list_node_create(struct list_node* self, struct states_list* list);

#endif //THEORIE_LANGAGE_LIST_NODE_H

int a = 3;
int b = 2;

b = a++;

cout<< ++b <<endl

b = ?