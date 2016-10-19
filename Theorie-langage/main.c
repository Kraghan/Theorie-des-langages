//
// Created by Kraghan on 05/10/2016.
//
#include "fa.h"

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
    faCreate(&automate,tailleAlpha,nbEtat);
    do{
        printf("\nQue voulez-vous faire ?");
        printf("\n\t 1 : Ajouter un etat (Etat actuellement cree : %u)",faCountState(&automate));
        printf("\n\t 2 : Ajouter une transition (Transition actuellement creee : %u)",faCountTransitions(&automate));
        printf("\n\t 3 : Creer un etat initial");
        printf("\n\t 4 : Creer un etat final");
        printf("\n\t 5 : Afficher les infos sur l'automate");
        printf("\n\t 6 : Supprimer une transition");
        printf("\n\t 7 : Supprimer un etat");
        printf("\n\t 8 : Tester si deterministe");
        printf("\n\t 9 : Tester si complet");
        printf("\n\t 10 : Rendre complet");
        printf("\n\t 11 : Fusionner des etats");
        printf("\n\t 0 : Exit\n");
        do {
            scanf("%u", &question);
        }while(question > 11 || question < 0);
        switch (question)
        {
            case 0:
                isRunning = false;
                break;
            case 1:
                printf("\nAjout d'un etat : \n");
                printf("Identifiant de votre etat ? (id > 0)\n");
                scanf("%u",&state);
                faAddState(&automate,state);
                break;
            case 2:
                printf("\nAjout d'une transition : \n");
                printf("Identifiant de votre etat source ? (id > 0)\n");
                scanf("%u",&state);
                printf("Identifiant de votre etat destination ? (id > 0)\n");
                scanf("%u",&state2);
                printf("Caractère de transition ");
                scanf("%c",&alpha);
                faAddTransition(&automate,state,alpha,state2);
                break;
            case 3:
                printf("\nDefinir un etat comme etat initial : \n");
                printf("Identifiant de votre etat ? (id > 0)\n");
                scanf("%u",&state);
                faSetStateInitial(&automate,state);
                break;
            case 4:
                printf("\nDefinir un etat comme etat final : \n");
                printf("Identifiant de votre etat ? (id > 0)\n");
                scanf("%u",&state);
                faSetStateFinal(&automate,state);
                break;
            case 5:
                faPrint(&automate,stdout);
                break;
            case 6:
                printf("\nSuppression d'une transition : \n");
                printf("Identifiant de votre etat source ? (id > 0)\n");
                scanf("%u",&state);
                printf("Identifiant de votre etat destination ? (id > 0)\n");
                scanf("%u",&state2);
                printf("Caractère de transition ");
                scanf("%c",&alpha);
                faRemoveTransition(&automate,state,alpha,state2);
                break;
            case 7:
                printf("\nSuppression d'un etat : \n");
                printf("Identifiant de votre etat ? (id > 0)\n");
                scanf("%u",&state);
                faRemoveState(&automate,state);
                break;
            case 8:
                if(faIsDeterministic(&automate))
                    printf("Automate deterministe\n");
                else
                    printf("Automate non deterministe\n");
                break;
            case 9:
                if(faIsComplete(&automate))
                    printf("Automate complet\n");
                else
                    printf("Automate non complet\n");
                break;
            case 10:
                faMakeComplete(&automate);
                break;
            case 11:
                printf("\nFusion de deux etats : \n");
                printf("Identifiant de votre premier etat ? (id > 0)\n");
                scanf("%u",&state);
                printf("Identifiant de votre second etat ? (id > 0)\n");
                scanf("%u",&state2);
                faMergeStates(&automate,state,state2);
                break;
            default:
                break;
        }
    }while(isRunning);

    faDestroy(&automate);

    return 0;
}