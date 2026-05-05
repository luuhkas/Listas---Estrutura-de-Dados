#include <stdio.h>
#include <stdlib.h>
#include "pilha_headers.h"

void contarParImpar(Pilha *pilha)
{
    if (pilha == NULL)
    {
        printf("Erro de alocacao de memoria\n");
        return;
    }
    int pares = 0;
    int impares = 0;

    Node *node = pilha->topo;
    while (node != NULL)
    {
        if (node->data % 2 == 0)
            pares++;
        else
            impares++;

        node = node->next;
    }

    printf("Quantidade de pares: %d\n", pares);
    printf("Quantidade de impares: %d\n", impares);
}

int main(void)
{
    Pilha *pilha = criarPilha();

    for (int i = 0; i < 6; i++)
        push(pilha, i);

    contarParImpar(pilha);

    return 0;
}

/*
Esse exercicio ficou bem simples porque foi so percorrer a pilha e testar se o valor
do no era par ou impar usando o resto da divisao por 2.
Usei um contador para os pares e outro para os impares, e no final imprimi os dois.
*/
