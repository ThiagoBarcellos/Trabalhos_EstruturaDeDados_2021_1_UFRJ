#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _vertice
{
    int number;
    int posX;
    int posY;
    int tam;
    int family;
} vertice;

typedef struct _aresta
{
    int leftSide;
    int rightSide;
    int distance;
    struct _aresta *prox;
} aresta;

typedef struct _RodoviaseFerrovias
{
    int maxStates;
    int minExtensionRoads;
    int minExtensionRailroads;
} rodoviaseferrovias;

int une(vertice **conj, int a, int b)
{
    if (((*conj) + a)->number != ((*conj) + a)->family || ((*conj) + b)->number != ((*conj) + b)->family)
        return 0;
    if (((*conj) + a)->family == ((*conj) + b)->family)
    {
        return 0;
    }
    if (((*conj) + a)->tam < ((*conj) + b)->tam)
    {
        ((*conj) + a)->family = ((*conj) + b)->number;
        ((*conj) + b)->tam += ((*conj) + a)->tam;
    }
    else
    {
        ((*conj) + b)->family = ((*conj) + a)->number;
        ((*conj) + a)->tam += ((*conj) + b)->tam;
    }

    return 1;
}

vertice find(vertice **conj, vertice vert)
{
    if (vert.number != vert.family)
    {
        vert = find(&(*conj), (*((*conj) + (vert.family))));
    }
    return vert;
}

void InsereNo(aresta **ptlist, int distance, int vertA, int vertB)
{
    if ((*ptlist) == NULL || (*ptlist)->distance > distance)
    {
        aresta *new = (aresta *)malloc(sizeof(aresta));
        new->distance = distance;
        new->leftSide = vertA;
        new->rightSide = vertB;
        new->prox = (*ptlist);
        (*ptlist) = new;
    }
    else
    {
        InsereNo(&(*ptlist)->prox, distance, vertA, vertB);
    }
}

void PrintList(rodoviaseferrovias *list, int count)
{
    int i = 0;
    for (i = 0; i < count; i++)
    {
        printf("Case #%d: %d %d %d\n", (i + 1), (list + i)->maxStates, (list + i)->minExtensionRoads, (list + i)->minExtensionRailroads);
    }
}

void calcularArestas(aresta **edge, vertice *conj, int tam)
{
    size_t i = 0;
    size_t j = 0;
    for (i = 0; i < tam; i++)
    {
        for (j = 1 + i; j < tam; j++)
        {
            int diffX = (conj + i)->posX - (conj + j)->posX;
            int diffY = (conj + i)->posY - (conj + j)->posY;
            int distance = sqrt((pow(diffX, 2)) + (pow(diffY, 2)));
            InsereNo(&(*edge), distance, i, j);
        }
    }
}

void criarArvore(aresta *edge, vertice **conj, rodoviaseferrovias **rodnFerr, int i, int threshold)
{
    (*rodnFerr + i)->maxStates = 1;
    (*rodnFerr + i)->minExtensionRailroads = 0;
    (*rodnFerr + i)->minExtensionRoads = 0;
    while (edge != NULL)
    {
        vertice pontEsq = find(&(*conj), (*((*conj) + (edge->leftSide))));
        vertice pontDir = find(&(*conj), (*((*conj) + (edge->rightSide))));

        if (une(&(*conj), pontEsq.number, pontDir.number) == 1)
        {
            if (edge->distance > threshold)
            {
                (*rodnFerr + i)->maxStates += 1;
                (*rodnFerr + i)->minExtensionRailroads += edge->distance;
            }
            else
            {
                (*rodnFerr + i)->minExtensionRoads += edge->distance;
            }
        }

        edge = edge->prox;
    }
}

int main()
{
    int cases, cities, threshold, posX, posY;
    scanf("%d", &cases);
    vertice *verticesCases[cases];
    aresta *arestasCases[cases];
    rodoviaseferrovias *rednFerr = (rodoviaseferrovias *)malloc(cases * sizeof(rodoviaseferrovias));
    size_t i = 0;
    size_t j = 0;
    for (i = 0; i < cases; i++)
    {
        scanf("%d %d", &cities, &threshold);
        vertice *cityGraph = (vertice *)malloc(cities * sizeof(vertice));
        for (j = 0; j < cities; j++)
        {
            scanf("%d %d", &posX, &posY);
            (cityGraph + j)->number = j;
            (cityGraph + j)->posX = posX;
            (cityGraph + j)->posY = posY;
            (cityGraph + j)->tam = 1;
            (cityGraph + j)->family = j;
        }
        verticesCases[i] = cityGraph;
    }
    for (i = 0; i < cases; i++)
    {
        aresta *edge = NULL;
        arestasCases[i] = edge;
        calcularArestas(&arestasCases[i], verticesCases[i], cities);
        criarArvore(arestasCases[i], &verticesCases[i], &rednFerr, i, threshold);

        free(edge);
    }
    PrintList(rednFerr, cases);
    free(rednFerr);

    return 0;
}