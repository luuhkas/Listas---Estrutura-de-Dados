#include <stdio.h>
#include <stdlib.h>
#include "pilha_headers.h"

int pop2(Pilha *pilha)
{
    if (pilha == NULL || pilha->topo == NULL || pilha->topo->next == NULL)
        return 1;

    for (int i = 0; i < 2; i++)
    {
        Node *node = pilha->topo;
        pilha->topo = node->next;

        free(node);
    }

    return 0;
}

int push2(Pilha *pilha, int data)
{
    if (pilha == 0)
        return 1;



    for (int i = 0; i < 2; i++)
    {
        Node *node;
        if ((node = malloc(sizeof(Node))) == NULL)
        {
            printf("Erro de alocacao de memoria\n");
            return 1;
        }
        
        node->data = data;
        node->next = pilha->topo;
        pilha->topo = node;
    }

    return 0;
}

int main(void)
{
   Pilha *pilha = criarPilha();
   
   push2(pilha, 2);
   printf("Apos o push2:\n");
   imprimirPilha(pilha);

   pop2(pilha);
   printf("Apos o pop2:\n");
   imprimirPilha(pilha);

   return 0;
}

/*
As funcoes estao todas no arquivo pilha_functions.c
Agora falando do exercicio, foi bem tranquilo, no push2, eu so precisei
colocar em um laco para fazer daus vezes, da parte de criar o no ate o topo
da pilha apontar para o proximo no.
Já no pop, foi quase a mesma coisa, com a diferenca de me atentar a restringir
quando a pilha nao tiver 2 nos.
*/