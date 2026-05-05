#include <stdio.h>
#include <stdlib.h>
#include "lista_headers.h"

void removerTodos(Lista *lista, int valor)
{
    if (lista == NULL || valor < 0)
        return;

    while (*lista != NULL && (*lista)->data == valor)
    {
        Node *node = *lista;
        *lista = node->next;
        free(node);
    }

    Node *node = *lista;

    while (node != NULL && node->next != NULL)
    {
        if (node->next->data == valor)
        {
            Node *remover = node->next;
            node->next = remover->next;
            free(remover);
        }
        else
            node = node->next;
    }
}

int main(void)
{
    Lista *lista = criarLista();

    inserirFim(lista, 2);
    inserirFim(lista, 1);
    inserirFim(lista, 2);
    inserirFim(lista, 3);
    inserirFim(lista, 2);

    printf("Lista antes da remocao:\n");
    imprimirLista(lista);

    removerTodos(lista, 2);

    printf("\nLista depois da remocao:\n");
    imprimirLista(lista);

    return 0;
}

/*
Nesse exercicio o cuidado maior foi remover tambem quando o valor aparece no inicio
da lista, porque isso muda o ponteiro inicio.
Depois eu fui olhando sempre o proximo no, para conseguir religar a lista quando
encontrasse o valor que precisava remover.
*/
