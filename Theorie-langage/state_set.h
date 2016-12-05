//
// Created by Kraghan on 06/10/2016.
//

#ifndef THEORIE_LANGAGE_STATE_SET_H
#define THEORIE_LANGAGE_STATE_SET_H

#include <stdio.h>
#include "state.h"
#include "stdlib.h"

/**
 * Size : Number of states stored in the set
 * Capacity : Maximum number of states can be stored in the set
 * StateId : Used for the determinisation
 * AlphaId : Used for the determinisation
 * States : List of states
 */
struct state_set
{
    unsigned int size;
    unsigned int capacity;
    unsigned int stateId;
    char alphaId;
    state* states;
};

typedef struct state_set state_set;

/**
 * Create a state set
 * @param self StateSet pointer
 * @param capacity Maximum number of states can be stored in the set
 * @param alpha Caracter associated for transition in Fa (unused)
 * @param state State associated for transition in Fa (unused)
 */
void state_set_create(state_set *self, unsigned int capacity, char alpha,
                      unsigned int state);

/**
 * Add a state to the set
 * @param self StateSet pointer
 * @param state State to add to the set
 */
void state_set_add(state_set *self, unsigned int state);

/**
 * Remove state from the set
 * @param self StateSet pointer
 * @param state Id of the state to remove
 */
void state_set_remove(state_set *self, unsigned int state);

/**
 * Print data from the set
 * @param self StateSet pointer
 * @param out File descriptor
 */
void state_set_print(state_set *self, FILE *out);

/**
 * Return true if the set contains a state of id = state
 * @param self StateSet pointer
 * @param state Id of the state to search
 */
bool state_set_contains(state_set *self, unsigned int state);

/**
 * Return the number of state in the set (= size)
 * @param self StateSet pointer
 */
unsigned int state_set_count(state_set *self);

/**
 * Return true if the set is empty
 * @param self StateSet pointer
 */
bool state_set_is_empty(state_set* self);

bool state_set_is_equal(state_set* first, state_set* second);

void state_set_add_set(state_set* self, const state_set* to_add);
#endif //THEORIE_LANGAGE_STATE_SET_H
