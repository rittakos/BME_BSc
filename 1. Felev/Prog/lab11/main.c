#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"


typedef struct BiFa {
    int ertek;
    struct BiFa *bal, *jobb;
} BiFa;

void WriteTree(BiFa *root)
{
    if (root == NULL)
        return;

    WriteTree(root->bal);
    printf("%d ", root->ertek);
    WriteTree(root->jobb);
}

void FreeTree(BiFa *root)
{
    if (root == NULL)
        return;


    FreeTree(root->bal);
    FreeTree(root->jobb);
    free(root);
}

int NumOfItems(BiFa *root)
{
    if(root == NULL)
        return 0;

    return NumOfItems(root->bal) + NumOfItems(root->jobb) + 1;
}

int SumOfItems(BiFa *root)
{
    if(root == NULL)
        return 0;

    return root->ertek + SumOfItems(root->bal) + SumOfItems(root->jobb);
}

BiFa *beszur(BiFa *gyoker, int ertek) {
    if (gyoker == NULL) {
        BiFa *uj = (BiFa*) malloc(sizeof(BiFa));
        uj->ertek = ertek;
        uj->bal = uj->jobb = NULL;
        return uj;
    }
    if (ertek < gyoker->ertek) {        /* balra szur */
        gyoker->bal = beszur(gyoker->bal, ertek);
    }
    else if (ertek > gyoker->ertek) {   /* jobbra szur */
        gyoker->jobb = beszur(gyoker->jobb, ertek);
    }
    else {
        /* mar benne van */
    }
    return gyoker;
}

BiFa *FindItem(BiFa *root, int num)
{
    if(root == NULL)
        return NULL;
    BiFa *currentItem = root;
    while(currentItem != NULL)
    {
        if(num == currentItem->ertek)
            return currentItem;
        else if(num < currentItem->ertek)
            currentItem = currentItem->bal;
        else
            currentItem = currentItem->jobb;
    }
    return NULL;
}

void Reflect(BiFa *root)
{
    if(root == NULL)
        return;

    struct BiFa* temp;


    Reflect(root->bal);
    Reflect(root->jobb);


    temp = root->bal;
    root->bal = root->jobb;
    root->jobb = temp;
}

void NegalTree(BiFa *root)
{
    if(root == NULL)
        return;

    NegalTree(root->bal);
    root->ertek = -1*root->ertek;
    NegalTree(root->jobb);
}

int main(void) {
    int minta[] = {15, 96, 34, 12, 14, 56, 21, 11, 10, 9, 78, 43, 0};
    BiFa *gyoker = NULL;
    for (int i = 0; minta[i] > 0; i++)
        gyoker = beszur(gyoker, minta[i]);

    /* Ide tedd be a kipróbálandó függvények hívásait! */
    NegalTree(gyoker);
    Reflect(gyoker);
    WriteTree(gyoker);
    printf("\n%d\n", NumOfItems(gyoker));
    printf("%d\n", SumOfItems(gyoker));
    FindItem(gyoker, 56);//nem jo negaltnal mert akkor amik kisebbek voltak nagyobbak lesznek es forditva


    FreeTree(gyoker);
    return 0;
}
