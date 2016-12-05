//
// Created by Kraghan on 05/10/2016.
//

#ifndef THEORIE_LANGAGE_FA_H
#define THEORIE_LANGAGE_FA_H

#include "state.h"
#include "state_set.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Alpha_size : Number of kind of transition in the FA
 * State_size : Number of states in the FA. Choose wisely this number because
 * you will need a completly new FA if you want to add a state (to complete
 * the FA for example)
 * States : List of states
 * Transitions : List of state_set. To access to the transition of the state
 * s for the letter b, use the transitions[n*alpha_size+'a'-b].
 */
struct fa{
    unsigned int alpha_size;
    unsigned int state_size;
    state* states;
    state_set* transitions;
};

typedef struct fa fa;

/**
 * Return the number of state in the FA
 * @param self FA pointer
 */
unsigned int fa_count_state(fa* self);

/**
 * Add state to the FA, return false if can't add the state.
 * @param self FA pointer
 * @param state Id of the state to add
 */
bool fa_add_state(fa *self, unsigned int state);

/**
 * Return the index of the state of id state
 * @param self FA pointer
 * @param state Id of the state to search
 */
int fa_get_state_index(const fa *self, unsigned int state);

/**
 * Initialize a new FA
 * @param self FA pointer
 * @param alpha_count Number of kind of transition in the FA
 * @param state_count Number of state in the FA. Choose wisely this number
 * because you will need a completly new FA if you want to add a state (to
 * complete the FA for example)
 */
void fa_create(fa *self, unsigned int alpha_count, unsigned int state_count);

/**
 * Free the memory of the FA
 * @param self FA pointer
 */
void fa_destroy(fa *self);

/**
 * Set the state state initial
 * @param self FA pointer
 * @param state Id of the state
 */
void fa_set_state_initial(fa *self, unsigned int state);

/**
 * Set the state state final
 * @param self FA pointer
 * @param state Id of the state
 */
void fa_set_state_final(fa *self, unsigned int state);

/**
 * Add a transition to the FA
 * @param self FA pointer
 * @param from Start of the transition (id of the state)
 * @param alpha Letter of the transition
 * @param to End of the transition (id of the state)
 */
void fa_add_transition(fa *self, unsigned int from, char alpha, unsigned int to);

/**
 * Print the data of the FA
 * @param self FA pointer
 * @param out File descriptor
 */
void fa_print(const fa *self, FILE *out);

/**
 * Remove transition from the FA
 * @param self FA pointer
 * @param from Id of state of the source of the transition
 * @param alpha Letter of the transition
 * @param to Id of state of the destination of the transition
 */
void fa_remove_transition(fa *self, unsigned int from, char alpha,
                          unsigned int to);

/**
 * Remove state form the FA
 * @param self FA pointer
 * @param state Id of the state to remove
 */
void fa_remove_state(fa *self, unsigned int state);

/**
 * Return the number of transitions
 * @param self FA pointer
 */
unsigned int fa_count_transitions(const fa *self);

/**
 * Return true if the FA is deterministic
 * @param self FA pointer
 */
bool fa_is_deterministic(const fa *self);

/**
 * Return true if the FA is complete
 * @param self FA pointer
 */
bool fa_is_complete(const fa *self);

/**
 * Make the FA complete
 * @param self FA pointer
 */
void fa_make_complete(fa *self);

/**
 * Merge two states
 * @param self FA pointer
 * @param state1 State id
 * @param state2 State id
 */
void fa_merge_states(fa *self, unsigned int state1, unsigned int state2);

/**
 * Return true if the FA is empty language
 * @param self FA pointer
 */
bool fa_is_language_empty(const fa *self);

/**
 * Remove all non accessible states
 * @param self FA pointer
 */
void fa_remove_non_accessible_state(fa *self);

/**
 * Remove all non co accessible states
 * @param self FA pointer
 */
void fa_remove_non_co_accessible_state(fa *self);

/**
 * Create the product of lhs and rhs
 * @param self FA pointer
 * @param lhs FA pointer
 * @param rhs FA pointer
 */
void fa_create_product(fa* self, const struct fa* lhs, const struct fa* rhs);

/**
 * Return true if the intersection of lhs and rhs is empty
 * @param lhs FA pointer
 * @param rhs FA pointer
 */
bool fa_has_empty_intersection(const struct fa* lhs, const struct fa* rhs);

/**
 * Return true if self has a transition from - (alphaIndex) > to
 * @param self FA pointer
 * @param alphaIndex Kind of transition
 * @param from Id of the state
 * @param to Id of the state
 */
bool fa_has_transition(const fa* self,unsigned int alphaIndex, unsigned int
from, unsigned int to);

/**
 * Transform the FA self to a deterministic version of nfa
 * @param self FA pointer
 * @param nfa FA pointer
 */
void fa_create_deterministic(fa * self, const fa *nfa);

/**
 * Return true if the FA lhs is included in the FA rhs
 * @param lhs FA pointer
 * @param rhs FA pointer
 */
bool fa_is_included(const fa * lhs, const fa * rhs);

/**
 * Quick exponanciation
 */
unsigned int pow(unsigned int integer, unsigned int exposant);

#endif //THEORIE_LANGAGE_FA_H