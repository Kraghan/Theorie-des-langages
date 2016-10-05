//
// Created by Kraghan on 05/10/2016.
//
#include "fa.h"

int main()
{
    fa automate;

    faCreate(&automate,2,5);

    faSetStateFinal(&automate,4);
    faSetStateFinal(&automate,3);
    faSetStateInitial(&automate,0);
    faSetStateInitial(&automate,1);

    faPrint(&automate,stdout);

    faDestroy(&automate);

    return 0;
}