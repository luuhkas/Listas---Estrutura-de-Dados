#include <stdio.h>
#include <stdlib.h>
#include "lista_headers.h"

Node *removerValorRecursivo(Node *node, int valor)
{
    if (node == NULL)
        return NULL;

    if (node->data == valor)
    {
        Node *prox = node->next;
        free(node);
        return prox;
    }

    node->next = removerValorRecursivo(node->next, valor);
    return node;
}

int listasIguaisRecursivo(Node *node1, Node *node2)
{
    if (node1 == NULL && node2 == NULL)
        return 1;

    if (node1 == NULL || node2 == NULL)
        return 0;

    if (node1->data != node2->data)
        return 0;

    return listasIguaisRecursivo(node1->next, node2->next);
}

int main(void)
{
    Lista *lista1 = criarLista();
    Lista *lista2 = criarLista();

    inserirFim(lista1, 1);
    inserirFim(lista1, 2);
    inserirFim(lista1, 3);

    inserirFim(lista2, 1);
    inserirFim(lista2, 3);

    *lista1 = removerValorRecursivo(*lista1, 2);

    printf("Lista 1 depois da remocao:\n");
    imprimirLista(lista1);

    if (listasIguaisRecursivo(*lista1, *lista2))
        printf("As listas sao iguais\n");
    else
        printf("As listas sao diferentes\n");

    return 0;
}

/*
Aqui usei recursividade nas duas funcoes. Na remocao, a funcao vai andando ate achar
o valor e religa o no anterior com o proximo.
Na comparacao, eu comparo um no de cada lista por vez, ate as duas acabarem juntas.
*/
