//
// Created by kraghan on 03/10/16.
//

#ifndef THEORIE_LANGAGE_STATE_H
#define THEORIE_LANGAGE_STATE_H
#define true 0x1
#define false !true
#define bool char

struct state
{
    bool is_initial;
    bool is_final;
    unsigned int id;
};

#endif //THEORIE_LANGAGE_STATE_H
