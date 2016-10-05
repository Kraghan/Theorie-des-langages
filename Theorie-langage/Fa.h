//
// Created by kraghan on 03/10/16.
//

#ifndef THEORIE_LANGAGE_FA_H
#define THEORIE_LANGAGE_FA_H

#include <stdio.h>
#include "states_list.h"
#include "transitions_list.h"

struct fa{
    unsigned int alpha_size;
    unsigned int state_size;
    struct states_list* states;
    struct transitions_list* transitions;
};

void fa_create(struct fa* self, unsigned int alpha_count, unsigned int state_count);

void fa_set_state_initial(struct fa* self, unsigned int state);

void fa_set_state_final(struct fa* self, unsigned int state);

void fa_add_transition(struct fa* self, unsigned int from, char alpha, unsigned int to);

void fa_print(const struct fa* self, FILE* out);

#endif //THEORIE_LANGAGE_FA_H
