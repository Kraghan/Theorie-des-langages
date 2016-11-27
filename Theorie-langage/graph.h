//
// Created by kraghan on 17/10/16.
//

#ifndef THEORIE_LANGAGE_GRAPH_H
#define THEORIE_LANGAGE_GRAPH_H

#include "fa.h"

/**
 * AdjacentList : List of bool. State n has a transition to m if
 * adjacentList[n*states+m] is true.
 * States : Number of states in the graph
 */
struct graph
{
    bool* adjacentList;
    unsigned int states;
};

typedef struct graph graph;

/**
 * Find all accessible states from state
 * @param self Graph pointer
 * @param state Id of the state
 * @param visited List of bool of size states
 */
void graph_depth_first_search(const graph *self, unsigned int state,
                              bool *visited);

/**
 * Return true if the state from has a path to the state to
 * @param self Graph pointer
 * @param from Id of the state
 * @param to Id of the state
 */
bool graph_has_path(const graph *self, unsigned int from, unsigned int to);

/**
 * Create a graph from a FA
 * @param self Graph pointer
 * @param fa FA pointer
 * @param inverted If true, the graph will be inverted
 */
void graph_create_from_fa(graph *self, const struct fa *fa, bool inverted);

/**
 * Free the graph
 * @param self Graph pointer
 */
void graph_destroy(graph *self);

/**
 * Print all datas from the graph
 * @param self Graph pointer
 * @param out File descriptor
 */
void graph_print(const graph *self, FILE *out);

#endif //THEORIE_LANGAGE_GRAPH_H
