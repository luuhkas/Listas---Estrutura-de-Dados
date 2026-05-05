#include <stdio.h>
#include <stdlib.h>
#include "lista_headers.h"

void removerRepetidos(Lista *lista)
{
    if (lista == NULL)
        return;

    Node *node = *lista;

    while (node != NULL)
    {
        Node *anterior = node;
        Node *aux = node->next;

        while (aux != NULL)
        {
            if (aux->data == node->data)
            {
                anterior->next = aux->next;
                free(aux);
                aux = anterior->next;
            }
            else
            {
                anterior = aux;
                aux = aux->next;
            }
        }

        node = node->next;
    }
}

int main(void)
{
    Lista *lista = criarLista();

    inserirFim(lista, 1);
    inserirFim(lista, 2);
    inserirFim(lista, 1);
    inserirFim(lista, 3);
    inserirFim(lista, 2);

    printf("Lista antes de remover repetidos:\n");
    imprimirLista(lista);

    removerRepetidos(lista);

    printf("\nLista depois de remover repetidos:\n");
    imprimirLista(lista);

    return 0;
}

/*
Nesse exercicio eu fixei um no e procurei repetidos dele no restante da lista.
Quando encontrava repetido, eu removia e religava o anterior com o proximo.
Assim o primeiro valor fica e as repeticoes depois dele saem.
*/
