#include <stdio.h>
#include <stdlib.h>
#include "lista_dupla_headers.h"

Lista *criarLista()
{
    Lista *lista;
    if ((lista = malloc(sizeof(Lista))) == NULL)
    {
        printf("Erro de alocacao de memoria\n");
        return NULL;
    }

    *lista = NULL;
    return lista;
}

void liberarLista(Lista *lista)
{
    if (lista == NULL)
        return;

    Node *node;
    while (*lista != NULL)
    {
        node = *lista;
        *lista = node->prox;
        free(node);
    }

    free(lista);
}

int inserirFim(Lista *lista, int data)
{
    if (lista == NULL)
        return 1;

    Node *node;
    if ((node = malloc(sizeof(Node))) == NULL)
    {
        printf("Erro de alocacao de memoria\n");
        return 1;
    }

    node->data = data;
    node->ant = NULL;
    node->prox = NULL;

    if (*lista == NULL)
    {
        *lista = node;
        return 0;
    }

    Node *aux = *lista;
    while (aux->prox != NULL)
        aux = aux->prox;

    aux->prox = node;
    node->ant = aux;
    return 0;
}

int inserirInicio(Lista *lista, int data)
{
    if (lista == NULL)
        return 1;

    Node *node;
    if ((node = malloc(sizeof(Node))) == NULL)
    {
        printf("Erro de alocacao de memoria\n");
        return 1;
    }

    node->data = data;
    node->ant = NULL;
    node->prox = *lista;

    if (*lista != NULL)
        (*lista)->ant = node;

    *lista = node;
    return 0;
}

int inserirOrdenado(Lista *lista, int data)
{
    if (lista == NULL)
        return 1;

    if (*lista == NULL || (*lista)->data >= data)
        return inserirInicio(lista, data);

    Node *node;
    if ((node = malloc(sizeof(Node))) == NULL)
    {
        printf("Erro de alocacao de memoria\n");
        return 1;
    }

    node->data = data;

    Node *atual = *lista;
    while (atual->prox != NULL && atual->prox->data < data)
        atual = atual->prox;

    node->ant = atual;
    node->prox = atual->prox;

    if (atual->prox != NULL)
        atual->prox->ant = node;

    atual->prox = node;
    return 0;
}

void imprimirLista(Lista *lista)
{
    if (lista == NULL)
        return;

    Node *node = *lista;
    while (node != NULL)
    {
        printf("Dado: %d\n", node->data);
        node = node->prox;
    }
}

void imprimirListaReversa(Lista *lista)
{
    if (lista == NULL || *lista == NULL)
        return;

    Node *node = *lista;
    while (node->prox != NULL)
        node = node->prox;

    while (node != NULL)
    {
        printf("Dado: %d\n", node->data);
        node = node->ant;
    }
}

int removerValor(Lista *lista, int data)
{
    if (lista == NULL || *lista == NULL)
        return 1;

    Node *node = *lista;
    while (node != NULL && node->data != data)
        node = node->prox;

    if (node == NULL)
        return 1;

    if (node->ant == NULL)
        *lista = node->prox;
    else
        node->ant->prox = node->prox;

    if (node->prox != NULL)
        node->prox->ant = node->ant;

    free(node);
    return 0;
}

int removerInicio(Lista *lista)
{
    if (lista == NULL || *lista == NULL)
        return 1;

    Node *node = *lista;
    *lista = node->prox;

    if (*lista != NULL)
        (*lista)->ant = NULL;

    free(node);
    return 0;
}

int removerFim(Lista *lista)
{
    if (lista == NULL || *lista == NULL)
        return 1;

    Node *node = *lista;
    while (node->prox != NULL)
        node = node->prox;

    if (node->ant == NULL)
        *lista = NULL;
    else
        node->ant->prox = NULL;

    free(node);
    return 0;
}

int tamanhoLista(Lista *lista)
{
    if (lista == NULL)
        return 0;

    int count = 0;
    Node *node = *lista;

    while (node != NULL)
    {
        count++;
        node = node->prox;
    }

    return count;
}

int listaVazia(Lista *lista)
{
    return lista == NULL || *lista == NULL;
}

int listaCheia(Lista *lista)
{
    (void)lista;
    return 0;
}
