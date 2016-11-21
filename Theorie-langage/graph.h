//
// Created by kraghan on 17/10/16.
//

#ifndef THEORIE_LANGAGE_GRAPH_H
#define THEORIE_LANGAGE_GRAPH_H

#include "fa.h"

struct graph
{
    bool* adjacentList;
    unsigned int states;
};

typedef struct graph graph;

void graph_depth_first_search(const graph *self, unsigned int state,
                              bool *visited);

bool graph_has_path(const graph *self, unsigned int from, unsigned int to);

void graph_create_from_fa(graph *self, const struct fa *fa, bool inverted);

void graph_destroy(graph *self);

void graph_print(const graph *self, FILE *out);

#endif //THEORIE_LANGAGE_GRAPH_H
