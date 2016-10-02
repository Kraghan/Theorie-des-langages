#define true 0x1
#define false !true
#define bool char

// Etat d'un automate
struct state
{
    bool is_final;
    bool is_initial;
    size_t id;
};

void state_create_state(struct state* state,size_t index);
