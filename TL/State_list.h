#include "State_node.h"

struct state_list
{
	struct state_node* first;
};

void list_add(struct state_list* self, struct state* element);

void list_remove(struct state_list* self, struct state* element);