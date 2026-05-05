#include <stdio.h>
#include <stdlib.h>
#include "lista_headers.h"

void fusaoOrdenada(Lista *l1, Lista *l2, Lista *resultado)
{
    if (l1 == NULL || l2 == NULL || resultado == NULL)
        return;

    Node *n1 = *l1;
    Node *n2 = *l2;
    Node *ultimo = NULL;

    while (n1 != NULL && n2 != NULL)
    {
        Node *escolhido;

        if (n1->data <= n2->data)
        {
            escolhido = n1;
            n1 = n1->next;
        }
        else
        {
            escolhido = n2;
            n2 = n2->next;
        }

        if (*resultado == NULL)
            *resultado = escolhido;
        else
            ultimo->next = escolhido;

        ultimo = escolhido;
    }

    if (n1 != NULL)
    {
        if (*resultado == NULL)
            *resultado = n1;
        else
            ultimo->next = n1;
    }
    else
    {
        if (*resultado == NULL)
            *resultado = n2;
        else
            ultimo->next = n2;
    }

    *l1 = NULL;
    *l2 = NULL;
}

int main(void)
{
    Lista *l1 = criarLista();
    Lista *l2 = criarLista();
    Lista *resultado = criarLista();

    inserirFim(l1, 1);
    inserirFim(l1, 3);
    inserirFim(l1, 5);

    inserirFim(l2, 2);
    inserirFim(l2, 4);
    inserirFim(l2, 6);

    fusaoOrdenada(l1, l2, resultado);

    printf("Lista depois da fusao ordenada:\n");
    imprimirLista(resultado);

    return 0;
}

/*
Nesse exercicio eu nao criei nos novos para fazer a fusao.
Fui escolhendo o menor no entre as duas listas e religando esses nos na lista resultado.
No final, o restante da lista que ainda tinha elementos foi ligado direto no resultado.
*/
