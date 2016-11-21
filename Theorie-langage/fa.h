//
// Created by Kraghan on 05/10/2016.
//

#ifndef THEORIE_LANGAGE_FA_H
#define THEORIE_LANGAGE_FA_H

#include "state.h"
#include "state_set.h"
#include <stdio.h>
#include <stdlib.h>

struct fa{
    unsigned int alpha_size;
    unsigned int state_size;
    state* states;
    state_set* transitions;
};

typedef struct fa fa;

unsigned int fa_count_state(fa* self);

bool fa_add_state(fa *self, unsigned int state);

int fa_get_state_index(const fa *self, unsigned int state);

void fa_create(fa *self, unsigned int alpha_count, unsigned int state_count);

void fa_destroy(fa *self);

void fa_set_state_initial(fa *self, unsigned int state);

void fa_set_state_final(fa *self, unsigned int state);

void fa_add_transition(fa *self, unsigned int from, char alpha, unsigned int to);

void fa_print(fa *self, FILE *out);

void fa_remove_transition(fa *self, unsigned int from, char alpha,
                          unsigned int to);

void fa_remove_state(fa *self, unsigned int state);

unsigned int fa_count_transitions(const fa *self);

bool fa_is_deterministic(const fa *self);

bool fa_is_complete(const fa *self);

void fa_make_complete(fa *self);

void fa_merge_states(fa *self, unsigned int state1, unsigned int state2);

bool fa_is_language_empty(const fa *self);

void fa_remove_non_accessible_state(fa *self);

void fa_remove_non_co_accessible_state(fa *self);

void fa_create_product(fa* self, const struct fa* lhs, const struct fa* rhs);

bool fa_has_empty_intersection(const struct fa* lhs, const struct fa* rhs);

bool fa_has_transition(const fa* self,unsigned int alphaIndex, unsigned int
from, unsigned int to);

#endif //THEORIE_LANGAGE_FA_H
