#include <stdlib.h>
#include <stdio.h>

#define ALT(tno) ((tno) != NULL) ? (tno)->alt : -1

typedef struct _tno
{
    int key;
    int alt;
    struct _tno *left;
    struct _tno *right;
} tno;

int altKnot(tno **knot)
{
    if ((*knot) == NULL)
    {
        return -1;
    }
    else
    {
        return (*knot)->alt;
    }
}

int knotBalance(tno *knot)
{
    return labs(altKnot(knot->left) - altKnot(knot->right));
}

void rotateLL(tno **root)
{
    tno temp = (*root)->left;
    (*root)->left = temp->right;
    temp->right = *root;
    (*root)->alt = compare(altKnot((*root)->left), altKnot((*root)->right)) + 1;
    temp->alt = compare(altKnot((*root)->left), (*knot)->alt) + 1;
    (*root) = temp;
}

void rotateRR(tno **root)
{
    tno temp = (*root)->right;
    (*root)->right = temp->left;
    temp->left = *root;
    (*root)->alt = compare(altKnot((*root)->left), altKnot((*root)->right)) + 1;
    temp->alt = compare(altKnot((*root)->alt), (*knot)->alt) + 1;
    (*root) = temp;
}

void rotateLR(tno **root)
{
    rotateRR(&(*root)->left);
    rotateLL(root);
}

void rotateRL(tno **root)
{
    rotateLL(&(*root)->right);
    rotateRR(root);
}

int compare(int x, int y)
{
    if (x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

int addKey(tno *knot, int key)
{
    int res;
    if (*knot == NULL)
    {
        tno new = (tno)malloc(sizeof(tno));
        if (new == NULL)
        {
            return 0;
        }
        new->key = key;
        new->alt = 0;
        new->left = NULL;
        new->right = NULL;

        *knot = new;
        return 1;
    }

    tno temp = *knot;
    if (key < temp->key){
        if ((res = addkey(&(temp->left), key)) == 1){
            if (knotBalance(temp) >= 2){
                if (key < (*knot)->left->key){
                    rotateLL(knot);
                }
                else{
                    rotateLR(knot);
                }
            }
        }
    }
    else{
        if (key > temp->key){
            if ((res = addkey(&(temp->right), key)) == 1){
                if (knotBalance(temp) >= 2){
                    if (key > (*knot)->right->key){
                        rotateRR(knot);
                    }
                    else{
                        rotateRL(knot);
                    }
                }
            }
        }
        else{
            return 0;
        }
    }
    temp->alt = compare(altKnot((*temp->left)->alt), altKnot((*temp->right)->alt)) + 1;

    return res;
}

void printTree(tno *knot)
{
    if (knot == 0)
    {
        return;
    }
    printTree(knot->left);
    printf("key: %d (alt: %d)\n", knot->key, knot->alt);
    printTree(knot->right);
}

int main()
{
    char string[50];
    int key;
    tno *knot = (tno *)malloc(1 * sizeof(tno));
    printf("Enter a key:\n");
    scanf("%s", string);
    sscanf(string, "%d", &key);
    knot->key = key;
    knot->alt = 1;
    knot->right = NULL;
    knot->left = NULL;

    while (1)
    {
        char temp[50];
        scanf("\n%[^\n]", string);
        if (string[0] == 'I' || string[0] == 'i')
        {
            sscanf(string, "%s %d", temp, &key);
            addkey(&knot, key);
        }
        else if (string[0] == 'P' || string[0] == 'p')
        {
            printTree(knot);
        }
        else
            break;
    }

    return 0;
}