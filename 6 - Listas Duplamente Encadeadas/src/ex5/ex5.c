#include <stdio.h>
#include <stdlib.h>

typedef struct fila
{
    int info;
    struct fila *prox;
    struct fila *ant;
} Fila;

typedef struct nodesc
{
    Fila *ini;
    Fila *fim;
} NoDesc;

int inicializa_noDesc(NoDesc **no)
{
    *no = malloc(sizeof(NoDesc));

    if (*no == NULL)
        return 0;

    (*no)->ini = NULL;
    (*no)->fim = NULL;
    return 1;
}

int enfileirar(NoDesc *n, int elem)
{
    if (n == NULL)
        return 0;

    Fila *node = malloc(sizeof(Fila));
    if (node == NULL)
        return 0;

    node->info = elem;
    node->prox = NULL;
    node->ant = n->fim;

    if (n->ini == NULL)
    {
        n->ini = node;
        n->fim = node;
    }
    else
    {
        n->fim->prox = node;
        n->fim = node;
    }

    return 1;
}

int desenfileirar(NoDesc *n, int *elem)
{
    if (n == NULL || n->ini == NULL || elem == NULL)
        return 0;

    Fila *node = n->ini;
    *elem = node->info;

    n->ini = node->prox;

    if (n->ini == NULL)
        n->fim = NULL;
    else
        n->ini->ant = NULL;

    free(node);
    return 1;
}

void imprimirFila(NoDesc *n)
{
    if (n == NULL)
        return;

    Fila *node = n->ini;

    while (node != NULL)
    {
        printf("%d ", node->info);
        node = node->prox;
    }

    printf("\n");
}

void liberarFila(NoDesc *n)
{
    if (n == NULL)
        return;

    Fila *node;
    while (n->ini != NULL)
    {
        node = n->ini;
        n->ini = node->prox;
        free(node);
    }

    free(n);
}

int main(void)
{
    NoDesc *fila;
    int removido;

    if (!inicializa_noDesc(&fila))
        return 1;

    enfileirar(fila, 10);
    enfileirar(fila, 20);
    enfileirar(fila, 30);

    printf("Fila antes de desenfileirar:\n");
    imprimirFila(fila);

    if (desenfileirar(fila, &removido))
        printf("\nValor removido: %d\n", removido);

    printf("\nFila depois de desenfileirar:\n");
    imprimirFila(fila);

    liberarFila(fila);
    return 0;
}

/*
Nesse exercicio eu usei o no descritor para guardar o inicio e o fim da fila.
Na hora de enfileirar, o novo no entra no fim. Na hora de desenfileirar, removi o
primeiro no e ajustei o inicio, porque a fila segue a regra do primeiro que entra sair primeiro.
*/
