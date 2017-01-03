//
// Created by Kraghan on 05/10/2016.
//
#include "fa.h"
#include "graph.h"

int main()
{
    //fa automates[10];

    fa automate;

    /*unsigned int nbAutomate = 0, currentAutomate = 0;
    bool isRunning = true;

    unsigned int nbEtat, tailleAlpha, question = 9999, questionAutomate = 9999,
            state,state2, id1, id2;
    char alpha;

    printf("Bonjour, voici un generateur d'automate fini\n");

    do {
        printf("Que voulez-vous faire ?");
        printf("\n\t 0 : Quitter");
        printf("\n\t 1 : Creer un nouvel automate");
        if(nbAutomate > 0)
        {
            printf("\n\t 2 : Modifier un automate");
            if (nbAutomate >= 2)
            {
                printf("\n\t 3 : Verifier si l'intersection de deux automates"
                               " est vide");
                if (nbAutomate < 9)
                    printf("\n\t 4 : Faire l'intersection de deux automates");
            }
        }
        do {
            scanf("%u", &questionAutomate);
        } while (questionAutomate > 4 || questionAutomate < 0);
        switch (questionAutomate)
        {
            case 0 :
                isRunning = false;
                continue;
            case 1 :
                printf("Combien d'etat contient votre automate ? (Si vous prevoyez de completer l'automate, pensez a ajouter un "
                               "etat supplementaire)\n");
                scanf("%u", &nbEtat);
                printf("\nQuelle est la taille de votre alphabet ? \n");
                scanf("%u", &tailleAlpha);
                fa_create(&automates[nbAutomate], tailleAlpha, nbEtat);
                ++nbAutomate;
                currentAutomate = nbAutomate;
                automate = automates[currentAutomate-1];
                break;
            case 2 :
                id1 = 0;
                printf("\nNumero de l'automate à modifier : ");
                do{
                    scanf("%u",&id1);
                }while(id1 == 0 && id1 > nbAutomate);
                currentAutomate = id1 - 1;
                break;
            case 3 :
                id1 = 0; id2 = 0;

                printf("\nTester l'intersection de l'automate numero (de 1 à "
                               "%d:",nbAutomate);
                do{
                    scanf("%u",&id1);
                }while(id1 == 0 && id1 > nbAutomate);

                printf("avec l'automate numero : ");
                do{
                    scanf("%u",&id2);
                }while((id2 == 0 && id2 > nbAutomate) || id2 == id1);

                if(fa_has_empty_intersection(&automates[id1-1],
                                             &automates[id2-1]))
                    printf("Intersection vide\n");
                else
                    printf("Intersection non vide\n");
                continue;
            case 4 :
                id1 = 0; id2 = 0;
                printf("\nFaire l'intersection de l'automate numero (de 1 a "
                               "%d) :",nbAutomate);
                do{
                    scanf("%u",&id1);
                }while(id1 == 0 && id1 > nbAutomate);
                printf("avec l'automate numero : ");
                do{
                    scanf("%u",&id2);
                }while((id2 == 0 && id2 > nbAutomate) || id2 == id1);
                fa_create_product(&automates[nbAutomate],&automates[id1 - 1],
                                  &automates[id2 - 1]);
                ++nbAutomate;
                printf("\nAutomate numero %d cree",nbAutomate);
                continue;
            default:
                break;
        }

        do {
            printf("\nQue voulez-vous faire ?");
            printf("\n\t 1 : Ajouter un etat (Etat actuellement cree : %u)",
                   fa_count_state(&automate));
            printf("\n\t 2 : Ajouter une transition (Transition actuellement creee : %u)",
                   fa_count_transitions(&automate));
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
            printf("\n\t 0 : Revenir a la selection des automates\n");
            do {
                scanf("%u", &question);
            } while (question > 14 || question < 0);
            switch (question) {
                case 0:
                    currentAutomate = 0;
                    break;
                case 1:
                    printf("\nAjout d'un etat : \n");
                    printf("Identifiant de votre etat ? (id > 0)\n");
                    scanf("%u", &state);
                    fa_add_state(&automate, state);
                    break;
                case 2:
                    alpha = ' ';
                    printf("\nAjout d'une transition : \n");
                    printf("Identifiant de votre etat source ? (id > 0)\n");
                    scanf("%u", &state);
                    printf("Identifiant de votre etat destination ? (id > 0)\n");
                    scanf("%u", &state2);
                    printf("Caractere de transition\n");
                    do {
                        scanf("%c", &alpha);
                    }while(alpha < 'a' || alpha > 'z');
                    fa_add_transition(&automate, state, alpha, state2);
                    break;
                case 3:
                    printf("\nDefinir un etat comme etat initial : \n");
                    printf("Identifiant de votre etat ? (id > 0)\n");
                    scanf("%u", &state);
                    fa_set_state_initial(&automate, state);
                    break;
                case 4:
                    printf("\nDefinir un etat comme etat final : \n");
                    printf("Identifiant de votre etat ? (id > 0)\n");
                    scanf("%u", &state);
                    fa_set_state_final(&automate, state);
                    break;
                case 5:
                    fa_print(&automate, stdout);
                    break;
                case 6:
                    printf("\nSuppression d'une transition : \n");
                    printf("Identifiant de votre etat source ? (id > 0)\n");
                    scanf("%u", &state);
                    printf("Identifiant de votre etat destination ? (id > 0)\n");
                    scanf("%u", &state2);
                    printf("Caractère de transition ");
                    scanf("%c", &alpha);
                    fa_remove_transition(&automate, state, alpha, state2);
                    break;
                case 7:
                    printf("\nSuppression d'un etat : \n");
                    printf("Identifiant de votre etat ? (id > 0)\n");
                    scanf("%u", &state);
                    fa_remove_state(&automate, state);
                    break;
                case 8:
                    if (fa_is_deterministic(&automate))
                        printf("Automate deterministe\n");
                    else
                        printf("Automate non deterministe\n");
                    break;
                case 9:
                    if (fa_is_complete(&automate))
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
                    scanf("%u", &state);
                    printf("Identifiant de votre second etat ? (id > 0)\n");
                    scanf("%u", &state2);
                    fa_merge_states(&automate, state, state2);
                    break;
                case 12:
                    if (fa_is_language_empty(&automate))
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
        } while (currentAutomate != 0);
    }while (isRunning);

    unsigned int i;
    for(i = 0; i < nbAutomate; i++)
    {
        fa_destroy(&automates[i]);
    }*/

    // For testing only
    fa_create(&automate, 3, 6);
    fa_add_state(&automate,0);
    fa_set_state_initial(&automate,0);
    fa_add_state(&automate,1);
    fa_add_state(&automate,2);
    fa_add_state(&automate,3);
    fa_add_state(&automate,4);
    fa_add_state(&automate,5);
    fa_set_state_final(&automate,5);
    fa_add_transition(&automate,0,'c',1);
    fa_add_transition(&automate,0,'a',2);
    fa_add_transition(&automate,1,'b',3);
    fa_add_transition(&automate,2,'b',4);
    fa_add_transition(&automate,3,'a',5);
    fa_add_transition(&automate,4,'a',5);

    fa test;
    fa_create_minimal_moore(&test,&automate);
    //fa_print(&test,stdout);

    fa_destroy(&automate);
    //fa_destroy(&test);

    return 0;
}