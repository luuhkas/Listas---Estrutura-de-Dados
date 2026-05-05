#include <stdio.h>
#include <stdlib.h>
#include "fila_headers.h"

int enqueueCircular(Fila *fila, int data)
{
    if (fila == NULL)
        return 1;

    Node *node = malloc(sizeof(Node));
    if (node == NULL)
        return 1;

    node->data = data;

    if (fila->inicio == NULL)
    {
        fila->inicio = node;
        fila->fim = node;
        node->next = node;
        return 0;
    }

    node->next = fila->inicio;
    fila->fim->next = node;
    fila->fim = node;

    return 0;
}

int furaFila(Fila *fila, int x)
{
    if (fila == NULL)
        return 1;

    Node *node = malloc(sizeof(Node));
    if (node == NULL)
        return 1;

    node->data = x;

    if (fila->inicio == NULL)
    {
        fila->inicio = node;
        fila->fim = node;
        node->next = node;
        return 0;
    }

    node->next = fila->inicio;
    fila->inicio = node;
    fila->fim->next = fila->inicio;

    return 0;
}

void imprimirFilaCircular(Fila *fila)
{
    if (fila == NULL || fila->inicio == NULL)
        return;

    Node *node = fila->inicio;

    do
    {
        printf("Dado: %d\n", node->data);
        node = node->next;
    } while (node != fila->inicio);
}

int main(void)
{
    Fila *fila = criarFila();

    enqueueCircular(fila, 2);
    enqueueCircular(fila, 3);
    enqueueCircular(fila, 4);

    printf("Fila circular antes de furar:\n");
    imprimirFilaCircular(fila);

    furaFila(fila, 1);

    printf("\nFila circular depois de furar:\n");
    imprimirFilaCircular(fila);

    return 0;
}

/*
Nesse exercicio a fila fica circular, entao o next do fim aponta de volta para o inicio.
Para furar a fila em O(1), eu criei um novo no e coloquei ele antes do inicio, sem
precisar andar pela fila inteira.
Tambem precisei mudar a impressao, porque em fila circular o percurso para quando
volta para o inicio.
*/
