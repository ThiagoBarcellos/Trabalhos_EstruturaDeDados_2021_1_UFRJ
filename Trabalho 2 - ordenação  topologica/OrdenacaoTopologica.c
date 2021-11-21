#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L /* Faz o getLine() não dar warning*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vert
{
    int chave;
    struct vert *adj;
    int apontaPara;
} vert;

void ordenarVertices(int *print, int vertices, vert *v, int tamanho)
{
    vert *check = (vert *)malloc(sizeof(vert));
    for (int i = 0; i <= tamanho; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            check = v[j].adj;
            while (check != NULL)
            {
                if (print[i] == check->chave)
                {
                    v[j].apontaPara--;
                    if (v[j].apontaPara == 0)
                    {
                        print[tamanho] = v[j].chave;
                        tamanho++;
                        i = 0;
                        j = 0;
                    }
                }
                check = check->adj;
            }
        }
    }
}

int main()
{
    vert *v, *temp, *check;
    int *print, tamanho = 0;
    char *linha = NULL;
    size_t tamLinha = 0;
    int vertices, arestas;
    scanf("%d %d\n", &vertices, &arestas);

    v = (vert *)malloc(vertices * sizeof(vert));
    for (int i = 0; i < vertices; i++)
    {
        v[i].chave = i + 1;
        v[i].adj = NULL;
    }

    print = (int *)malloc(vertices * sizeof(int));

    for (int i = 1; i <= vertices; i++)
    {

        getline(&linha, &tamLinha, stdin);
        int pos = 0;
        int numLido = 0;
        int numChars;

        while (sscanf(&linha[pos], " %d %n", &numLido, &numChars) > 0)
        {
            pos += numChars;
            if (strlen(linha) != 0)
            {
                temp = (vert *)malloc(sizeof(vert));
                temp->chave = numLido;
                temp->adj = NULL;
                if (v[i - 1].adj == NULL)
                {
                    v[i - 1].adj = temp;
                }
                else
                {
                    check = (vert *)malloc(sizeof(vert));
                    check = &v[i - 1];
                    while (check->adj != NULL)
                    {
                        check = check->adj;
                    }
                    check->adj = temp;
                }
            }
        }
    }

    for (int i = 0; i < vertices; i++)
    {
        tamanho = 0;
        check = &v[i];
        while (check->adj != NULL)
        {
            check = check->adj;
            tamanho++;
        }
        v[i].apontaPara = tamanho;
    }
    tamanho = 0;

    for (int i = 0; i < vertices; i++)
    {
        if (v[i].apontaPara == 0)
        {
            print[tamanho] = v[i].chave;
            tamanho++;
        }
    }

    ordenarVertices(print, vertices, v, tamanho);

    for (int i = vertices - 1; i >= 0; i--)
    {
        printf("%d ", print[i]);
    }

    return 0;
}