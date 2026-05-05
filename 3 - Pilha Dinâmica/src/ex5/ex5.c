#include <stdio.h>
#include <stdlib.h>
#include "pilha_headers.h"

void testePilha(Pilha *pilha1, Pilha *pilha2)
{
    if (pilha1 == NULL || pilha2 == NULL)
    {
        printf("Erro de alocacao de memoria");
        return;
    }

    Node *node1 = pilha1->topo;
    Node *node2 = pilha2->topo;

    while (node1 != NULL && node2 != NULL)
    {
        if (node1->data != node2->data)
        {
            printf("As pilhas sao diferentes\n");
            return;
        }

        node1 = node1->next;
        node2 = node2->next;
    }

    if (node1 == NULL && node2 == NULL)
        printf("As pilhas sao iguais\n");
    else
        printf("As pilhas sao diferentes\n");
}

int main(void)
{
    Pilha *pilha1 = criarPilha();
    for (int i = 0; i < 3; i++)
        push(pilha1, i);
    Pilha *pilha2 = criarPilha();
    for (int i = 1; i < 4; i++)
        push(pilha2, i);
    
    printf("Pilha1 depois do push:\n");
    imprimirPilha(pilha1);
    printf("Pilha2 depois do push:\n");
    imprimirPilha(pilha2);

    testePilha(pilha1, pilha2);

    return 0;
}

/*
Aqui a ideia foi usar dois ponteiros auxiliares, um para cada pilha, e ir andando
nas duas ao mesmo tempo. Se algum dado for diferente, ja da para saber que as pilhas
nao sao iguais.
No final eu precisei verificar se as duas chegaram em NULL juntas, porque se uma
terminar antes da outra quer dizer que elas tem tamanhos diferentes.
*/
