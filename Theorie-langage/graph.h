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

void graphDepthFirstSearch(const graph* self, unsigned int state, bool* visited);

bool graphHasPath(const graph* self, unsigned int from, unsigned int to);

void graphCreateFromFa(graph* self, const struct fa* fa, bool inverted);


#endif //THEORIE_LANGAGE_GRAPH_H
