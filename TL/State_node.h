// Representation des noeuds d'etat d'un automate
struct state_node
{
    size_t state;
    struct state_node* next;
};

void node_create(struct state_node* node, size_t state_id);
