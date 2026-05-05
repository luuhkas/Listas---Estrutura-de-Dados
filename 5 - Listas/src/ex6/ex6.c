#include <stdio.h>
#include <stdlib.h>
#include "lista_headers.h"

void concatenar(Lista *l1, Lista *l2)
{
    if (l1 == NULL || l2 == NULL || *l2 == NULL)
        return;

    if (*l1 == NULL)
    {
        *l1 = *l2;
    }
    else
    {
        Node *node = *l1;
        while (node->next != NULL)
            node = node->next;

        node->next = *l2;
    }

    *l2 = NULL;
}

int main(void)
{
    Lista *l1 = criarLista();
    Lista *l2 = criarLista();

    inserirFim(l1, 1);
    inserirFim(l1, 2);

    inserirFim(l2, 3);
    inserirFim(l2, 4);

    concatenar(l1, l2);

    printf("Lista depois da concatenacao:\n");
    imprimirLista(l1);

    return 0;
}

/*
Para concatenar, eu fui ate o ultimo no da primeira lista e liguei ele no inicio
da segunda. Depois deixei a segunda vazia, porque os nos dela passaram a fazer parte
da primeira.
*/
