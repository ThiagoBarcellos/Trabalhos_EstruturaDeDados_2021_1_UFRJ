#include <stdio.h>
#include <stdlib.h>

typedef struct _tno
{
	int chave;
	struct _tno *prox;
} tno;

void InsereNo(tno **ptlist, int x)
{
	if ((*ptlist) == NULL || (*ptlist)->chave > x)
	{
		tno *novo = malloc(sizeof(tno));
		novo->chave = x;
		novo->prox = (*ptlist);
		(*ptlist) = novo;
	}
	else
	{
		InsereNo(&(*ptlist)->prox, x);
	}
}

void PrintList(tno *list)
{
	while(list != NULL){
		printf("%d -> ", list->chave);
		list = list->prox;
	}
}

int main()
{
	int key;
	tno *knot;
	for (size_t i = 0; i < 5; i++)
	{
		printf("\n");
		printf("Enter a key:\n");
		scanf("%d", &key);
		InsereNo(&knot, key);
		PrintList(knot);
	}

	return 0;
}