#include <stdio.h>
#include <stdlib.h>

typedef struct _tno
{
    int key;
    int soma;
    struct _tno *esq;
    struct _tno *dir;
} tno;

void PreencheSomas(tno **ptlist)
{
    int soma = (*ptlist)->key;
    if ((*ptlist)->esq != NULL){
        PreencheSomas(&(*ptlist)->esq);
        soma += ((*ptlist)->esq)->soma;
    }
    if ((*ptlist)->dir != NULL){
        PreencheSomas(&(*ptlist)->dir);
        soma += ((*ptlist)->dir)->soma;
    }
    (*ptlist)->soma = soma;
}

void InserirChave(tno **ptraiz, int x)
{
    if ((*ptraiz) == NULL)
    {
        (*ptraiz) = (tno *)malloc(sizeof(tno));
        (*ptraiz)->key = x;
        (*ptraiz)->esq = NULL;
        (*ptraiz)->dir = NULL;
        (*ptraiz)->soma = 0;
    }
    else if ((*ptraiz)->key > x)
    {
        InserirChave(&(*ptraiz)->esq, x);
    }
    else
    {
        InserirChave(&(*ptraiz)->dir, x);
    }
}

void printTree(tno *knot)
{
    if (knot == 0)
    {
        return;
    }
    printTree(knot->esq);
    printf("key: %d (soma: %d)\n", knot->key, knot->soma);
    printTree(knot->dir);
}

int main()
{
    int key = 0;
    tno *ptraiz;
    for (size_t i = 0; i < 5; i++)
    {
        printf("Insira um valor\n");
        scanf("%d", &key);
        InserirChave(&ptraiz, key);
        printTree(ptraiz);
    }
    printf("PreenchendoSomas\n");
    PreencheSomas(&ptraiz);
    printf("Printando\n");
    printTree(ptraiz);

    return 0;
}