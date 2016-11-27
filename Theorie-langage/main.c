//
// Created by Kraghan on 05/10/2016.
//
#include "fa.h"
#include "graph.h"

int main()
{
    fa automate;

    bool isRunning = true;

    unsigned int nbEtat, tailleAlpha, question,state,state2;
    char alpha;

    printf("Bonjour, voici un generateur d'automate fini\n");
    printf("Combien d'etat contient votre automate ? (Si vous prevoyez de completer l'automate, pensez a ajouter un "
                   "etat supplementaire)\n");
    scanf("%u",&nbEtat);
    printf("\nQuelle est la taille de votre alphabet ? \n");
    scanf("%u",&tailleAlpha);
    fa_create(&automate,tailleAlpha,nbEtat);
    do{
        printf("\nQue voulez-vous faire ?");
        printf("\n\t 1 : Ajouter un etat (Etat actuellement cree : %u)",fa_count_state(&automate));
        printf("\n\t 2 : Ajouter une transition (Transition actuellement creee : %u)",fa_count_transitions(&automate));
        printf("\n\t 3 : Creer un etat initial");
        printf("\n\t 4 : Creer un etat final");
        printf("\n\t 5 : Afficher les infos sur l'automate");
        printf("\n\t 6 : Supprimer une transition");
        printf("\n\t 7 : Supprimer un etat");
        printf("\n\t 8 : Tester si deterministe");
        printf("\n\t 9 : Tester si complet");
        printf("\n\t 10 : Rendre complet");
        printf("\n\t 11 : Fusionner des etats");
        printf("\n\t 12 : Tester si reconnait langage vide");
        printf("\n\t 13 : Supprimer les etats non accessibles");
        printf("\n\t 14 : Supprimer les etats non co-accessibles");
        printf("\n\t 0 : Exit\n");
        do {
            scanf("%u", &question);
        }while(question > 14 || question < 0);
        switch (question)
        {
            case 0:
                isRunning = false;
                break;
            case 1:
                printf("\nAjout d'un etat : \n");
                printf("Identifiant de votre etat ? (id > 0)\n");
                scanf("%u",&state);
                fa_add_state(&automate,state);
                break;
            case 2:
                printf("\nAjout d'une transition : \n");
                printf("Identifiant de votre etat source ? (id > 0)\n");
                scanf("%u",&state);
                printf("Identifiant de votre etat destination ? (id > 0)\n");
                scanf("%u",&state2);
                printf("Caractère de transition ");
                scanf("%c",&alpha);
                fa_add_transition(&automate,state,alpha,state2);
                break;
            case 3:
                printf("\nDefinir un etat comme etat initial : \n");
                printf("Identifiant de votre etat ? (id > 0)\n");
                scanf("%u",&state);
                fa_set_state_initial(&automate,state);
                break;
            case 4:
                printf("\nDefinir un etat comme etat final : \n");
                printf("Identifiant de votre etat ? (id > 0)\n");
                scanf("%u",&state);
                fa_set_state_final(&automate,state);
                break;
            case 5:
                fa_print(&automate,stdout);
                break;
            case 6:
                printf("\nSuppression d'une transition : \n");
                printf("Identifiant de votre etat source ? (id > 0)\n");
                scanf("%u",&state);
                printf("Identifiant de votre etat destination ? (id > 0)\n");
                scanf("%u",&state2);
                printf("Caractère de transition ");
                scanf("%c",&alpha);
                fa_remove_transition(&automate,state,alpha,state2);
                break;
            case 7:
                printf("\nSuppression d'un etat : \n");
                printf("Identifiant de votre etat ? (id > 0)\n");
                scanf("%u",&state);
                fa_remove_state(&automate,state);
                break;
            case 8:
                if(fa_is_deterministic(&automate))
                    printf("Automate deterministe\n");
                else
                    printf("Automate non deterministe\n");
                break;
            case 9:
                if(fa_is_complete(&automate))
                    printf("Automate complet\n");
                else
                    printf("Automate non complet\n");
                break;
            case 10:
                fa_make_complete(&automate);
                break;
            case 11:
                printf("\nFusion de deux etats : \n");
                printf("Identifiant de votre premier etat ? (id > 0)\n");
                scanf("%u",&state);
                printf("Identifiant de votre second etat ? (id > 0)\n");
                scanf("%u",&state2);
                fa_merge_states(&automate,state,state2);
                break;
            case 12:
                if(fa_is_language_empty(&automate))
                    printf("Automate reconnaissant le langage vide\n");
                else
                    printf("Automate ne reconnaissant pas le langage vide\n");
                break;
            case 13:
                fa_remove_non_accessible_state(&automate);
                break;
            case 14:
                fa_remove_non_co_accessible_state(&automate);
                break;
            default:
                break;
        }
    }while(isRunning);

    fa_destroy(&automate);

    // For testing only

    /*fa automate, automate2, automateFusion;

    fa_create(&automate, 2, 2);

    fa_add_state(&automate, 0);
    fa_add_state(&automate, 1);
    fa_set_state_initial(&automate, 0);
    fa_set_state_final(&automate, 1);
    fa_add_transition(&automate, 0, 'a', 0);
    fa_add_transition(&automate, 0, 'b', 1);
    fa_add_transition(&automate, 1, 'a', 1);
    //fa_print(&automate, stdout);

    fa_create(&automate2, 2, 3);

    fa_add_state(&automate2, 0);
    fa_add_state(&automate2, 1);
    fa_add_state(&automate2, 2);
    fa_set_state_initial(&automate2, 0);
    fa_set_state_final(&automate2, 2);
    fa_add_transition(&automate2, 0, 'b', 0);
    fa_add_transition(&automate2, 0, 'a', 1);
    fa_add_transition(&automate2, 1, 'b', 1);
    fa_add_transition(&automate2, 1, 'b', 2);
    fa_add_transition(&automate2, 2, 'b', 2);

    fa_create_product(&automateFusion,&automate,&automate2);

    fa_destroy(&automate);
    fa_destroy(&automate2);
    fa_destroy(&automateFusion);*/

    return 0;
}