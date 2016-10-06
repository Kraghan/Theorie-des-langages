//
// Created by Kraghan on 05/10/2016.
//
#include "fa.h"

int main()
{
    fa automate;

    faCreate(&automate,2,5);

    faSetStateFinal(&automate,1);
    faSetStateFinal(&automate,4);
    faSetStateInitial(&automate,0);
    faSetStateInitial(&automate,1);
    faAddTransition(&automate,0,'a',1);
    faAddTransition(&automate,0,'a',3);
    faAddTransition(&automate,0,'a',2);
    faAddTransition(&automate,1,'b',3);
    faAddTransition(&automate,2,'a',3);
    faAddTransition(&automate,2,'b',4);
    faAddTransition(&automate,3,'a',3);
    faAddTransition(&automate,3,'b',4);
    faAddTransition(&automate,4,'a',4);

    faPrint(&automate,stdout);

    faDestroy(&automate);

    return 0;
}