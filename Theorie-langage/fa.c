//
// Created by Kraghan on 05/10/2016.
//

#include "fa.h"
#include "graph.h"

unsigned int fa_count_state(fa* self)
{
    unsigned int i;
    for(i = 0; i < self->state_size; ++i)
    {
        if(self->states[i].id == 99999)
        {
            return i;
        }
    }
    return i;
}

// Return -1 if not found
int fa_get_state_index(const fa *self, unsigned int state)
{
    int i;
    for(i = 0; i < self->state_size; ++i)
    {
        if(self->states[i].id == state)
        {
            return i;
        }
    }
    return -1;
}

bool fa_add_state(fa *self, unsigned int state)
{
    if(fa_get_state_index(self, state) != -1)
    {
        fprintf(stderr,"\nWarning : Can't add state %u. Cause : Already in.\n",state);
        return false;
    }

    unsigned int i;
    for(i = 0; i < self->state_size; ++i)
    {
        if(self->states[i].id == 99999)
        {
            self->states[i].id = state;
            return true;
        }
    }
    fprintf(stderr,"\nError : Can't add state. Cause : State limit reach.\n");
    return false;
}

void fa_create(fa *self, unsigned int alpha_count, unsigned int state_count)
{
    unsigned int i;
    self->alpha_size = alpha_count;
    self->state_size = state_count;
    self->states = (state*)malloc(sizeof(state)*state_count);
    for(i = 0; i < state_count; ++i)
    {
        state_create(&self->states[i], 99999);
    }

    self->transitions = (state_set*)malloc(sizeof(state_set)*state_count*alpha_count);
    for(i = 0; i < state_count*alpha_count;++i)
    {
        state_set_create(&self->transitions[i], state_count,
                         'a' + (i % alpha_count), i / state_count);
    }
}

void fa_destroy(fa *self)
{
    free(self->states);

    unsigned int i;
    for(i = 0; i < self->state_size*self->alpha_size;++i)
    {
        free(self->transitions[i].states);
    }
    free(self->transitions);

    self->alpha_size = 0;
    self->state_size = 0;
}

void fa_set_state_initial(fa *self, unsigned int state)
{
    unsigned int i;
    for(i = 0; i < self->state_size;++i)
    {
        if(self->states[i].id == state)
        {
            state_set_initial(&(self->states[i]));
        }
    }
}

void fa_set_state_final(fa *self, unsigned int state)
{
    unsigned int i;
    for(i = 0; i < self->state_size;++i)
    {
        if(self->states[i].id == state)
        {
            state_set_final(&(self->states[i]));
        }
    }
}

void fa_add_transition(fa *self, unsigned int from, char alpha, unsigned int to)
{
    if(alpha-'a' >= self->alpha_size)
    {
        fprintf(stderr,"\nError : Can't add transition. Cause : Alpha isn't in possible transitions.\n");
        return;
    }

    int indexFrom = fa_get_state_index(self, from);
    if(indexFrom == -1)
    {
        fprintf(stderr,"\nError : Can't add transition. Cause : From isn't in possible states.\n");
        return;
    }

    unsigned int index = self->alpha_size*indexFrom+(alpha-'a');
    if(state_set_contains(&self->transitions[index], to))
    {
        fprintf(stderr,"\nError : Can't add transition %u to %u by %c. Cause : Already in.\n",from,to,alpha);
        return;
    }
    state_set_add(&self->transitions[index], to);
}

void fa_print(fa *self, FILE *out)
{
    unsigned int i,j,index;

    fprintf(out,"States : \n\t");
    for(i = 0; i < self->state_size;++i)
    {
        if(self->states[i].id == 99999)
            continue;
        fprintf(out,"%u ",self->states[i].id);
    }

    fprintf(out,"\nInitial states : \n\t");
    for(i = 0; i < self->state_size;++i)
    {
        if(self->states[i].id == 99999)
            continue;
        if(self->states[i].is_initial == true)
        {
            fprintf(out,"%u ",self->states[i].id);
        }
    }

    fprintf(out,"\nFinal states : \n\t");
    for(i = 0; i < self->state_size;++i)
    {
        if(self->states[i].id == 99999)
            continue;
        if(self->states[i].is_final == true)
        {
            fprintf(out,"%u ",self->states[i].id);
        }
    }

    fprintf(out,"\nTransitions :");
    for(i = 0; i < self->state_size;++i)
    {
        if(self->states[i].id == 99999)
            continue;
        fprintf(out,"\n\t For state : %u",self->states[i].id);
        for(j = 0; j < self->alpha_size; ++j)
        {
            fprintf(out,"\n\t\t For letter %c : ",'a'+j);
            index = self->alpha_size*i+j;
            state_set_print(&self->transitions[index], out);
        }

    }

    if(fa_is_deterministic(self))
    {
        fprintf(out,"\nIs deterministic");
    }
    else
    {
        fprintf(out,"\nIs not deterministic");
    }

    if(fa_is_complete(self))
    {
        fprintf(out,"\nIs complete");
    }
    else
    {
        fprintf(out, "\nIs not complete");
    }

    if(fa_is_language_empty(self))
    {
        fprintf(out,"\nIs empty language\n");
    }
    else
    {
        fprintf(out,"\nIs not empty language\n");
    }
}

void fa_remove_transition(fa *self, unsigned int from, char alpha,
                          unsigned int to)
{
    if(alpha-'a' >= self->alpha_size)
    {
        fprintf(stderr,"\nError : Can't remove transition. Cause : alpha isn't in possible transitions.\n");
        return;
    }

    int indexFrom = fa_get_state_index(self, from);
    if(indexFrom == -1)
    {
        fprintf(stderr,"\nError : Can't remove transition. Cause : From isn't in possible states.\n");
        return;
    }

    unsigned int index = self->alpha_size*indexFrom+(alpha-'a');

    state_set_remove(&self->transitions[index], to);
}

void fa_remove_state(fa *self, unsigned int state)
{
    int stateIndex = fa_get_state_index(self, state);

    if(stateIndex == -1)
    {

        fprintf(stderr,"\nWarning : Can't remove state %u. Cause : Isn't in states list.\n",state);
        return;
    }

    unsigned int i,j;
    // Je supprime toutes les transitions qui vont vers l'état
    for(i = 0; i < self->state_size; ++i)
    {
        int indexFrom = fa_get_state_index(self, self->states[i].id);
        if(indexFrom == -1)
        {
            continue;
        }
        for(j = 0; j < self->alpha_size; ++j)
        {
            unsigned int index = self->alpha_size*indexFrom+j;
            state_set_remove(&self->transitions[index], state);
        }
    }

    // Je supprime toutes les transitions qui sortent de l'état
    for(i = 0; i < self->alpha_size; ++i)
    {
        unsigned int index = self->alpha_size*stateIndex+i;
        free(self->transitions[index].states);
    }
    for(i = (unsigned int)stateIndex; i < self->state_size-1; ++i)
    {
        for(j = 0; j < self->alpha_size; ++j)
        {
            self->transitions[i*self->alpha_size+j] = self->transitions[i*self->alpha_size+j+self->alpha_size];
        }
    }

    // Je supprime l'état de la liste
    for(i = (unsigned int)stateIndex; i < self->state_size-1;++i)
    {
        self->states[i] = self->states[i+1];
    }
    self->state_size--;
}

unsigned int fa_count_transitions(const fa *self)
{
    unsigned int i,sum = 0;
    for(i = 0; i < self->state_size*self->alpha_size; ++i)
    {
        sum += state_set_count(&self->transitions[i]);
    }
    return sum;
}

bool fa_is_deterministic(const fa *self)
{
    unsigned int i,j;
    for(i = 0; i < self->state_size; ++i)
    {
        for(j = 0; j < self->alpha_size; ++j)
        {
            if(state_set_count(&self->transitions[i * self->alpha_size + j]) > 1)
                return false;
        }
    }
    return true;
}

bool fa_is_complete(const fa *self)
{
    unsigned int i,j,nombreDeTransition;
    for(i = 0; i < self->state_size; ++i)
    {
        for(j = 0; j < self->alpha_size; ++j)
        {
            nombreDeTransition = state_set_count(
                    &self->transitions[i * self->alpha_size + j]);
            if(nombreDeTransition > 1 || nombreDeTransition == 0)
                return false;
        }
    }
    return true;
}

void fa_make_complete(fa *self)
{
    if(!fa_is_deterministic(self))
    {
        fprintf(stderr,"\nError : Can't make complete. Cause : non deterministic.\n");
        return;
    }
    if(fa_is_complete(self))
    {
        fprintf(stderr,"\nWarning : Can't make complete. Cause : Already complete.\n");
        return;
    }
    if(!fa_add_state(self, 99998))
    {
        if(fa_get_state_index(self, 99998) == -1)
        {
            fprintf(stderr,"\nError : Can't make complete. Cause : States limit reach.\n");
            return;
        }
        else
        {
            fprintf(stderr,"\nError : Can't make complete. Cause : state 99998 already in.\n");
            return;
        }
    }
    unsigned int i,j,nombreDeTransition;
    for(i = 0; i < self->state_size; ++i)
    {
        for(j = 0; j < self->alpha_size; ++j)
        {
            nombreDeTransition = state_set_count(
                    &self->transitions[i * self->alpha_size + j]);
            if(nombreDeTransition == 0)
                state_set_add(&self->transitions[i * self->alpha_size + j],
                              99998);
        }
    }
}

void fa_merge_states(fa *self, unsigned int state1, unsigned int state2)
{
    int indexState1 = fa_get_state_index(self, state1);
    if(indexState1 == -1)
    {
        fprintf(stderr,"\nError : Can't merge states %u and %u. Cause : state %u doesn't exist.\n",state1,state2,state1);
        return;
    }
    int indexState2 = fa_get_state_index(self, state2);
    if(indexState2 == -1)
    {
        fprintf(stderr,"\nError : Can't merge states %u and %u. Cause : state %u doesn't exist.\n",state1,state2,state2);
        return;
    }

    if(state1 == state2)
    {
        fprintf(stderr,"\nWarning : Can't merge states %u and %u. Cause : Same state.\n",state1,state2);
        return;
    }

    unsigned int i,j,k;

    // J'ajoute toutes les transitions partant de state2 à state1
    for(i = 0; i < self->alpha_size;++i)
    {
        for(j = 0; j < self->transitions[indexState2*self->alpha_size+i].size;++j)
        {
            fa_add_transition(self, state1, (char)('a'+i),
                              self->transitions[indexState2 * self->alpha_size +
                                                i].states[j].id);
        }
    }

    // J'ajoute toutes les transitions arrivant à state2 à state1
    for(i = 0; i < self->alpha_size;++i)
    {
        for(j = 0; j < self->alpha_size;++j)
        {
            for(k = 0; k < self->transitions[i*self->alpha_size+j].size;++k)
            {
                if(self->transitions[i*self->alpha_size+j].states[k].id == state2)
                    fa_add_transition(self, self->states[i].id, (char)('a'+j), state1);
            }
        }
    }

    // J'affecte les propriétés final et initial de state2 à state1
    if(self->states[indexState2].is_final)
        self->states[indexState1].is_final = true;
    if(self->states[indexState2].is_initial)
        self->states[indexState1].is_initial = true;

    // Je supprime state2
    fa_remove_state(self, state2);
}

bool fa_is_language_empty(const fa *self)
{
    unsigned int i,j;
    // Creation du graphe
    graph graph;
    graph_create_from_fa(&graph, self, false);

    // On cherche si pour un etat initial, il existe un chemin vers un etat
    // final
    for(i = 0; i < self->state_size; ++i)
    {
        if(self->states[i].is_initial)
        {
            for(j = 0; j < self->state_size; ++j)
            {
                if(self->states[j].is_final)
                {
                    if(graph_has_path(&graph, i, j))
                    {
                        graph_destroy(&graph);
                        return false;
                    }
                }
            }
        }
    }
    graph_destroy(&graph);
    return true;
}

void fa_remove_non_accessible_state(fa *self)
{
    if(fa_is_language_empty(self))
    {
        fprintf(stderr,"\nError : Can't remove non accessible states. Cause :"
                " Empty language");
        return;
    }

    graph graph;
    graph_create_from_fa(&graph, self, false);
    graph_print(&graph, stdout);

    unsigned int i,j;
    for(i = 0; i < graph.states; ++i)
    {
        bool hasPathToInitialState = false;
        for(j = 0; j < graph.states; ++j)
        {
            if(self->states[j].is_initial)
            {
                if(graph_has_path(&graph, j, i))
                {
                    hasPathToInitialState = true;
                    break;
                }
            }

        }
        if(!hasPathToInitialState)
            fa_remove_state(self, self->states[i].id);
    }
    graph_destroy(&graph);
}

void fa_remove_non_co_accessible_state(fa *self)
{
    if(fa_is_language_empty(self))
    {
        fprintf(stderr,"\nError : Can't remove non co-accessible states. "
                "Cause : Empty language");
        return;
    }

    graph graph;
    graph_create_from_fa(&graph, self, false);
    graph_print(&graph, stdout);

    unsigned int i,j;
    for(i = 0; i < graph.states; ++i)
    {
        bool hasPathToFinalState = false;
        for(j = 0; j < graph.states; ++j)
        {
            if(self->states[j].is_final)
            {
                if(graph_has_path(&graph, i, j))
                {
                    hasPathToFinalState = true;
                    break;
                }
            }

        }
        if(!hasPathToFinalState)
            fa_remove_state(self, self->states[i].id);
    }
    graph_destroy(&graph);
}

void fa_create_product(fa* self, const fa* lhs, const fa* rhs)
{
    unsigned int alphaSize = lhs->alpha_size < rhs->alpha_size ? lhs->alpha_size
                                                               : rhs->alpha_size;
    fa_create(self,alphaSize, lhs->state_size * rhs->state_size);
    unsigned int i, j, k,lhsCursor, rhsCursor;

    // Pour chaque lettre
    for (k = 0; k < alphaSize; ++k)
    {
        for(i = 0; i < lhs->state_size; ++i)
        {
            for(lhsCursor = 0; lhsCursor < lhs->state_size; ++lhsCursor)
            {
                // On regarde si il existe une transition entre i et
                // lhsCursor dans lhs pour la lettre k
                if(fa_has_transition(lhs,k,i,lhsCursor))
                {
                    for (j = 0; j < rhs->state_size; ++j)
                    {
                        for(rhsCursor = 0; rhsCursor < rhs->state_size;++rhsCursor)
                        {
                            // On regarde si il existe une transition entre j et
                            // rhsCursor dans rhs pour la lettre k
                            if(fa_has_transition(rhs,k,j,rhsCursor))
                            {
                                fa_add_transition(self, i*rhs->state_size+j,
                                                  (char)('a'+k),
                                                  lhsCursor*rhs->state_size+rhsCursor);
                            }
                        }
                    }
                }
            }
        }
    }
}

bool fa_has_empty_intersection(const struct fa* lhs, const struct fa* rhs)
{

}


bool fa_has_transition(const fa* self, unsigned int alphaIndex, unsigned int
from, unsigned int to)
{
    int fromIndex = fa_get_state_index(self, from);
    return state_set_contains(&self->transitions[fromIndex+alphaIndex],to);
}