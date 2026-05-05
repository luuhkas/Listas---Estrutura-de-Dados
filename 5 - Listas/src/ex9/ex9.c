#include <stdio.h>
#include <stdlib.h>
#include "lista_headers.h"

int troca(Lista *lista, Node *p)
{
    if (lista == NULL || p == NULL || p->next == NULL)
        return 1;

    Node *anterior = NULL;
    Node *node = *lista;

    while (node != NULL && node != p)
    {
        anterior = node;
        node = node->next;
    }

    if (node == NULL)
        return 1;

    Node *proximo = p->next;

    if (anterior == NULL)
        *lista = proximo;
    else
        anterior->next = proximo;

    p->next = proximo->next;
    proximo->next = p;

    return 0;
}

int main(void)
{
    Lista *lista = criarLista();

    inserirFim(lista, 1);
    inserirFim(lista, 2);
    inserirFim(lista, 3);
    inserirFim(lista, 4);

    printf("Lista antes da troca:\n");
    imprimirLista(lista);

    troca(lista, (*lista)->next);

    printf("\nLista depois da troca:\n");
    imprimirLista(lista);

    return 0;
}

/*
Aqui nao podia trocar so o valor dentro do no, entao eu troquei os ponteiros.
Primeiro achei o no anterior ao p, depois fiz o proximo de p vir antes dele.
Tambem tratei o caso de p ser o primeiro no, porque nesse caso o inicio da lista muda.
*/
