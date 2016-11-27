//
// Created by Kraghan on 05/10/2016.
//

#ifndef THEORIE_LANGAGE_STATE_H
#define THEORIE_LANGAGE_STATE_H


#include <stdbool.h>

/**
 * Is_initial : True if the state is an initial state
 * Id_final : True if the state is an final state
 * Id : Id of the state
 */
struct state{
    bool is_initial;
    bool is_final;
    unsigned int id;
};

typedef struct state state;

/**
 * Create a new state
 * @param self State pointer
 * @param id Id of the state
 */
void state_create(state *self, unsigned int id);

/**
 * Set the state as initial state
 * @param self State pointer
 */
void state_set_initial(state *self);

/**
 * Set the state as final state
 * @param self State pointer
 */
void state_set_final(state *self);

#endif //THEORIE_LANGAGE_STATE_H
