#include <stdio.h>
#include <stdlib.h>
#include "pilha_headers.h"

Node *nodeRecursivo(Node *node)
{
    if (node == NULL)// caso base
        return NULL; 

    Node *auxNode;
    if ((auxNode = malloc(sizeof(Node))) == NULL)
        return NULL;

    auxNode->data = node->data;
    auxNode->next = nodeRecursivo(node->next);// chamada recursiva

    return auxNode;
}

Pilha *pilha_copia(Pilha *pilha)
{
    if (pilha == NULL)
        return NULL;
    
    Pilha *pilhaAux = criarPilha();
    if (pilhaAux == NULL)
        return NULL;

    Node *node = pilha->topo;
    pilhaAux->topo = nodeRecursivo(node);

    return pilhaAux;
}

int main(void) // main normal apenas 
{
    Pilha *pilha = criarPilha();
    for (int i = 0; i < 4; i++)
        push(pilha, i);

    printf("Depois do push:\n");
    imprimirPilha(pilha);

    printf("Depois da copia\n");
    Pilha *copia = pilha_copia(pilha);
    imprimirPilha(copia);
   
    return 0;
}

/*
Tive a ideia de fazer por recursividade mais como um "desafiio" e achei que ficou muito bom
ainda mais pela ideia de usar a recursividade para ela vir invertidade e depois incrementar na
pilha copia ela fica correta igual a original.
*/