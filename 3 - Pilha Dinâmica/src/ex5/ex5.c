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
    
    Node *node;
    if ((node = malloc(sizeof(Node))) == NULL)
    {
        printf("Erro de alocacao de memoria");
        return;
    }

    node = pilha1->topo;

}