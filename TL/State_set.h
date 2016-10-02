#include "State_node.h"
// Ensemble des etats
struct state_set
{
    struct state_node* first;
};

void set_add(struct state_set* state_set, size_t state_id);

void set_new(struct state_set* set);
