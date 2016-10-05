#include "State.h"
#include "State_list.h"
// Automate fini
struct fa
{
    // Taille de l'alphabet
    size_t alpha_size;
    // Nombre d'etat
    size_t state_size;
    // Tableau d'etat
    struct state* states;
    // Tableau de transitions
   	struct state_list* transitions;
};

void fa_create(struct fa *self, size_t alpha_count, size_t state_count);

void fa_destroy(struct fa *self);

void fa_set_state_initial(struct fa *self, size_t state_id);

void fa_set_state_final(struct fa *self, size_t state_id);

void fa_add_transition(struct fa *self, size_t state_id_from, char alpha, size_t state_id_to);
