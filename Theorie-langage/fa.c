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
                         (char)('a' + (i % alpha_count)), i / state_count);
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

void fa_set_state_non_final(fa *self, unsigned int state)
{
    unsigned int i;
    for(i = 0; i < self->state_size;++i)
    {
        if(self->states[i].id == state)
        {
            state_set_non_final(&(self->states[i]));
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

void fa_print(const fa *self, FILE *out)
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
    unsigned int alpha_size = lhs->alpha_size < rhs->alpha_size ?
                              lhs->alpha_size : rhs->alpha_size;

    unsigned int state_size = lhs->state_size * rhs->state_size;

    fa_create(self,alpha_size,state_size);

    unsigned int i,j,k;

    for(i = 0; i < state_size; ++i)
    {
        fa_add_state(self,i);

        if(lhs->states[i/rhs->state_size].is_initial &&
                rhs->states[i%rhs->state_size].is_initial)
        {
            fa_set_state_initial(self,i);
        }

        if(lhs->states[i/rhs->state_size].is_final &&
           rhs->states[i%rhs->state_size].is_final)
        {
            fa_set_state_final(self,i);
        }
    }

    for(i = 0; i < state_size; ++i)
    {
        for(j = 0; j < alpha_size; ++j)
        {
            unsigned int lhsFrom = lhs->states[i/rhs->state_size].id;
            unsigned int rhsFrom = rhs->states[i%rhs->state_size].id;

            for(k = 0; k < state_size; ++k)
            {
                unsigned int lhsTo = lhs->states[k/rhs->state_size].id;
                unsigned int rhsTo = rhs->states[k%rhs->state_size].id;

                if(fa_has_transition(lhs,j,lhsFrom,lhsTo) &&
                        fa_has_transition(rhs,j,rhsFrom,rhsTo))
                {
                    fa_add_transition(self,i,'a'+j,k);
                }
            }
        }
    }
}

bool fa_has_empty_intersection(const struct fa* lhs, const struct fa* rhs)
{
    fa automate;
    fa_create_product(&automate,lhs,rhs);
    bool empty = fa_is_language_empty(&automate);
    fa_destroy(&automate);
    return empty;
}

bool fa_has_transition(const fa* self, unsigned int alphaIndex, unsigned int
from, unsigned int to)
{
    int fromIndex = fa_get_state_index(self, from);
    return state_set_contains(&self->transitions[fromIndex*self->alpha_size+alphaIndex],
                              to);
}

void fa_create_deterministic(fa * self, const fa *nfa)
{
    state_set* tableCorrespondance;
    unsigned int i, states, nbMaxStateDeterministic = custom_pow(2,nfa->state_size);
    tableCorrespondance = (state_set*) malloc(nbMaxStateDeterministic * sizeof(state_set));

    for(i = 0; i < nbMaxStateDeterministic; ++i)
    {
        state_set_create(&tableCorrespondance[i],nfa->state_size,'1',0);
    }

    // Creation du premier état avec tous les initiaux
    for(i = 0 ; i < nfa->state_size; ++i)
    {
        if(nfa->states[i].id == 99999)
            continue;

        if(nfa->states[i].is_initial)
            state_set_add(&tableCorrespondance[0],nfa->states[i].id);
    }

    if(state_set_is_empty(&tableCorrespondance[0]))
    {
        fprintf(stderr, "Error : Can't be deterministic ! Cause : No initial "
                "states");
        return;
    }

    // On réserve la place suffisante pour l'automate determinisé et on ajoute l'état initial
    fa_create(self,nfa->alpha_size,nbMaxStateDeterministic);
    fa_add_state(self,0);
    fa_set_state_initial(self,0);

    tableCorrespondance[0].alphaId = ' ';
    states = 1;

    i = 0;
    // Pour tous les set d'etats dans la table de correspondance
    while(tableCorrespondance[i].alphaId != '1')
    {
        unsigned int k;
        // Pour chaque lettre
        for(k = 0; k < nfa->alpha_size; ++k)
        {
            // On cree un set qui contient la lettre de transition et l'id de l'etat source de cette transition vers
            // l'etat represente par ce set
            state_set set;
            state_set_create(&set, nfa->state_size, (char) ('a' + k), i);

            // Pour tous les etats dans la table de correspondance
            unsigned int j;
            for (j = 0; j < tableCorrespondance[i].size; ++j)
            {
                // On ajoute les etats au set
                state_set *alphaStateSet = fa_find_transition(nfa, k, tableCorrespondance[i].states[j].id);

                if (alphaStateSet != NULL && alphaStateSet->size != 0)
                    state_set_add_set(&set,alphaStateSet);
            }

            if(!state_set_is_empty(&set))
            {
                // On check si le set est deja present dans la table de correpondance
                unsigned int cpt = 0;
                bool found = false;
                while (tableCorrespondance[cpt].alphaId != '1')
                {
                    if (state_set_is_equal(&tableCorrespondance[cpt], &set))
                    {
                        found = true;
                        break;
                    }
                    ++cpt;
                }

                // Si il ne l'est pas, on l'ajoute
                if (!found)
                {
                    tableCorrespondance[states] = set;
                    fa_add_state(self,states);
                    for(cpt = 0; cpt < set.size; ++cpt)
                    {
                        if(nfa->states[fa_get_state_index(nfa,set.states[cpt].id)].is_final)
                        {
                            fa_set_state_final(self,states);
                            break;
                        }
                    }
                    // On ajoute la transition
                    fa_add_transition(self,i,(char) ('a' + k),states);
                    ++states;
                }
                else
                    // On ajoute la transition
                    if(i != 0)
                        fa_add_transition(self,i,(char) ('a' + k),cpt);
            }
        }
        ++i;

    }
    free(tableCorrespondance);
}

bool fa_is_included(const fa * lhs, const fa * rhs)
{
    fa tmp;
    fa_create_complementaire(&tmp,rhs);
    bool res = fa_has_empty_intersection(&tmp,lhs);
    fa_destroy(&tmp);
    return res;
}

unsigned int custom_pow(unsigned int integer, unsigned int exposant)
{
    if(exposant == 1)
        return integer;
    if(exposant == 0)
        return 1;
    if(exposant%2 == 0)
        return custom_pow(integer*integer,exposant/2);
    else
        return integer*custom_pow(integer*integer,(exposant-1)/2);
}

state_set* fa_find_transition(const fa * self, unsigned int alphaIndex,
                              unsigned int state_id)
{
    int index = fa_get_state_index(self, state_id);
    if(index != -1)
    {
        return &self->transitions[index*self->alpha_size+alphaIndex];
    }
    return NULL;
}

void fa_create_complementaire(fa* self, const fa* nfa)
{
    fa tmp;
    fa_create_deterministic(&tmp,nfa);
    fa_make_complete(&tmp);

    fa_create(self,tmp.alpha_size,tmp.state_size+1);
    unsigned i,j,k;
    // On créé les états
    for(i = 0; i < tmp.state_size; ++i)
    {
        if(tmp.states[i].id != 99999)
        {
            fa_add_state(self, tmp.states[i].id);
            if(tmp.states[i].is_final)
                fa_set_state_final(self,tmp.states[i].id);
            if(tmp.states[i].is_initial)
                fa_set_state_initial(self,tmp.states[i].id);
        }
    }

    // On créé les transitions
    for(i = 0; i < tmp.state_size; ++i)
    {
        if(tmp.states[i].id != 99999)
        {
            for(k = 0; k < tmp.state_size; ++k)
            {
                if(tmp.states[k].id != 99999)
                {
                    for(j = 0; j < tmp.alpha_size; ++j)
                    {
                        if(fa_has_transition(&tmp,j,tmp.states[i].id,tmp.states[k].id))
                            fa_add_transition(self,tmp.states[i].id,'a'+j,tmp.states[k].id);
                    }
                }
            }
        }
    }

    for(i = 0; i < tmp.state_size; ++i)
    {
        if(tmp.states[i].id != 99999)
        {
            if(!tmp.states[i].is_final)
                fa_set_state_final(self,tmp.states[i].id);
            else
                fa_set_state_non_final(self,tmp.states[i].id);
        }
    }

    fa_destroy(&tmp);
}

void fa_create_sub_fa(fa* self, const fa* nfa, unsigned state)
{
    if(fa_get_state_index(nfa,state) == -1)
    {
        fprintf(stderr,"Can't create sub fa : state %u is not in nfa",state);
        return;
    }

    fa_create(self,nfa->alpha_size,nfa->state_size);
    fa_add_state(self,state);
    fa_set_state_initial(self,state);

    unsigned alpha_index, stateIndex = 0;
    state_set* currentTransition;

    while(stateIndex < self->state_size && self->states[stateIndex].id != 99999)
    {
        for (alpha_index = 0; alpha_index < nfa->alpha_size; ++alpha_index)
        {
            if ((currentTransition = fa_find_transition(nfa, alpha_index, self->states[stateIndex].id)) != NULL)
            {
                unsigned i = 0;
                while(currentTransition->states[i].id != 99999)
                {
                    if(fa_get_state_index(self,currentTransition->states[i].id) == -1)
                    {
                        fa_add_state(self, currentTransition->states[i].id);
                        if(nfa->states[fa_get_state_index(nfa,currentTransition->states[i].id)].is_initial)
                            fa_set_state_initial(self,currentTransition->states[i].id);
                        if(nfa->states[fa_get_state_index(nfa,currentTransition->states[i].id)].is_final)
                            fa_set_state_final(self,currentTransition->states[i].id);
                    }
                    fa_add_transition(self,self->states[stateIndex].id,'a'+alpha_index,currentTransition->states[i].id);
                    ++i;
                }
            }
        }
        stateIndex++;
    }
}

bool fa_are_nerode_equivalent(const fa* self, unsigned state1, unsigned state2)
{
    fa subFa1, subFa2;

    fa_create_sub_fa(&subFa1,self,state1);
    fa_create_sub_fa(&subFa2,self,state2);

    return fa_is_included(&subFa1,&subFa2) && fa_is_included(&subFa2,&subFa1);
}

void fa_create_minimal_nerode(fa* self, const fa* other)
{
    // On crée une copie de l'automate initial
    fa_create(self,other->alpha_size,other->state_size);

    unsigned i,j,k;
    for(i = 0; i < other->state_size; ++i)
    {
        if(other->states[i].id != 99999)
        {
            fa_add_state(self, other->states[i].id);
            if(other->states[i].is_final)
                fa_set_state_final(self,other->states[i].id);

            if(other->states[i].is_initial)
                fa_set_state_initial(self,other->states[i].id);
        }
    }

    for(i = 0; i < other->state_size; ++i)
    {
        if(other->states[i].id != 99999)
            for(j = 0; j < other->alpha_size; ++j)
            {
                for(k = 0; k < other->state_size; ++k)
                {
                    if(other->states[k].id != 99999
                       && fa_has_transition(other, j, other->states[i].id, other->states[k].id))
                            fa_add_transition(self, other->states[i].id, (char) ('a' + j), other->states[k].id);
                }
            }
    }

    bool estModifie = true;
    while(estModifie)
    {
        unsigned compteur = 0;
        estModifie = false;
        while (self->states[compteur].id != 99999 && compteur < self->state_size)
        {
            unsigned compteur2 = 0;
            while (self->states[compteur2].id != 99999 && compteur2 < self->state_size)
            {
                if (compteur != compteur2 && fa_are_nerode_equivalent(self, self->states[compteur].id,
                                                                 self->states[compteur2].id))
                {
                    estModifie = true;
                    fa_merge_states(self,self->states[compteur].id,self->states[compteur2].id);
                    break;
                }
                ++compteur2;
            }

            if(estModifie)
                break;

            ++compteur;
        }
    }
}

void fa_create_minimal_moore(fa* self, const fa* other)
{
    // Fonction de test d'égalité des classes
    bool testEgalite(unsigned* classeN, unsigned* classeN1, unsigned nbEtat)
    {
        unsigned i;
        for(i = 0; i < nbEtat; ++i)
            if(classeN[i] != classeN1[i])
                return false;

        return true;
    }

    int findClass(unsigned* classeN, unsigned** classeParLettre, unsigned index, unsigned nbState, unsigned
    nbLettres)
    {
        unsigned i;
        for(i = 0; i < index; ++i)
        {
            unsigned alpha;
            if(classeN[index] == classeN[i])
            {
                for (alpha = 0; alpha < nbLettres; ++alpha)
                {
                    if(classeParLettre[alpha][i] == classeParLettre[alpha][index])
                    {
                        if (alpha == nbLettres - 1)
                            return i;
                        continue;
                    }
                    else
                        break;
                }
            }
        }
        return -1;
    }

    fa* deterministic = (fa *) other;

    if(!fa_is_deterministic(other))
    {
        fa_create_deterministic(deterministic,other);
    }

    // Init
    unsigned* classeN = (unsigned *) malloc(other->state_size * sizeof(unsigned));
    unsigned* classeN1 = (unsigned *) malloc(other->state_size * sizeof(unsigned));
    unsigned ** classeParLettre = (unsigned **) malloc(other->alpha_size);
    unsigned i;
    for(i = 0; i < other->state_size; ++i)
        classeParLettre[i] = (unsigned *) malloc(other->state_size);

    // Initialize classes
    for(i = 0; i < other->state_size; ++i)
    {
        if(other->states[i].id != 99999 && other->states[i].is_final)
            classeN1[i] = 2;
        else
            classeN1[i] = 1;
    }

    // Algorithme de Moore
    do
    {
        for (i = 0; i < other->state_size; ++i)
        {
            classeN[i] = classeN1[i];
        }

        // Définition des classes par lettres
        unsigned alpha;
        for(alpha = 0; alpha < other->alpha_size; ++alpha)
        {
            for (i = 0; i < other->state_size; ++i)
            {
                if (other->states[i].id != 99999)
                {
                    state_set* transition = fa_find_transition(other,alpha,i);
                    if(transition->size == 1)
                        classeParLettre[alpha][i] = classeN[fa_get_state_index(other,transition->states[0].id)];
                    else if(transition->size == 0)
                        classeParLettre[alpha][i] = 0;
                }
            }
        }

        unsigned value = 0;

        // Definition des classes pour l'étape n
        for (i = 0; i < other->state_size; ++i)
        {
            int found;
            if((found = findClass(classeN,classeParLettre,i, other->state_size, other->alpha_size)) == -1)
            {
                classeN1[i] = value;
                value++;
            }
            else
                classeN1[i] = classeN1[found];

        }

        printf("Separator\n");

        for (i = 0; i < other->state_size; ++i)
        {
            printf("Classe N : %u Classe N +1 : %u\n",classeN[i],classeN1[i]);
        }
    }while(!testEgalite(classeN,classeN1,other->state_size));

    unsigned alpha;
    for (alpha = 0; alpha < other->alpha_size; ++alpha)
    {
        printf("Letter : %c \n", 'a'+alpha);
        for (i = 0; i < other->state_size; ++i)
        {
            printf("Classe state %d : %u \n", i, classeParLettre[alpha][i]);
        }
    }
    // Création de l'automate


    // Free memory
    free(classeN);
    free(classeN1);
    free(classeParLettre);
}