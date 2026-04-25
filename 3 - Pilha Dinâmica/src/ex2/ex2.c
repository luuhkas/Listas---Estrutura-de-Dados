#include <stdio.h>
#include <stdlib.h>
#include "pilha_headers.h"

int popN(Pilha *pilha, int n)
{
    if (pilha == NULL || n <= 0)
        return 1;

    // restricao para obrigar ter a quatidade de nos que serao liberados
    Node *node = pilha->topo;
    for(int i = 0; i < n; i++)
    {
        if (node == NULL)
            return 1;

        node = node->next;
    }

    // pop similar aos outros so que em um laco para n repeticoes
    for(int i = 0; i < n; i++)
    {
        Node *node = pilha->topo;
        pilha->topo = node->next;
        free(node);
    }

    return 0;
}

int main(void)
{
    Pilha *pilha = criarPilha();
    for (int i = 0; i < 4; i++)
        push(pilha, i);

    imprimirPilha(pilha);
    printf("Depois do push\n");

    popN(pilha, 3);
    imprimirPilha(pilha);
    printf("Depois do popN\n");

    return 0;
}

/*
Parecido com o pop2, mas o problema aqui foi pensar nas restricoes
como fazer para so usar o popN quando tivesse pelo menos N nos.
*/