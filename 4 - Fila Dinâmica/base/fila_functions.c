#include <stdio.h>
#include <stdlib.h>
#include "fila_headers.h"

// Estrutura base da fila dinamica: quem entra vai para o fim e quem sai vem do inicio.

Fila *criarFila()
{
    Fila *fila;
    if ((fila = malloc(sizeof(Fila))) == NULL)
    {
        printf("Erro de alocacao memoria\n");
        return NULL;
    }

    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

void imprimirFila(Fila *fila)
{
    if (fila == NULL)
        return;

    Node *node = fila->inicio;
    while (node != NULL)
    {
        printf("Dado: %d\n", node->data);
        node = node->next;
    }
}

int enqueue(Fila *fila, int data)
{
    if (fila == NULL)
        return 1;

    Node *node;
    if ((node = malloc(sizeof(Node))) == NULL)
    {
        printf("Erro de alocacao de memoria\n");
        return 1;
    }

    node->data = data;
    node->next = NULL;

    if (fila->inicio == NULL)
    {
        fila->inicio = node;
        fila->fim = node;
        return 0;
    }

    fila->fim->next = node;
    fila->fim = node;

    return 0;
}

int dequeue(Fila *fila)
{
    if (fila == NULL || fila->inicio == NULL)
        return 1;

    Node *node = fila->inicio;
    fila->inicio = node->next;

    if (fila->inicio == NULL)
        fila->fim = NULL;

    free(node);
    return 0;
}

int frente(Fila *fila)
{
    if (fila == NULL || fila->inicio == NULL)
        return 0;

    return fila->inicio->data;
}
