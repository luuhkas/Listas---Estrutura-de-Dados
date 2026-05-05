#include <stdio.h>
#include <stdlib.h>
#include "pilha_headers.h"

void verificarFormato(char texto[])
{
    Pilha *pilha = criarPilha();

    if (pilha == NULL)
        return;

    int i = 0;
    while (texto[i] != '\0' && texto[i] != 'C')
    {
        if (texto[i] != 'A' && texto[i] != 'B')
        {
            printf("Formato invalido\n");
            while (pilha->topo != NULL)
            {
                Node *node = pilha->topo;
                pilha->topo = node->next;
                free(node);
            }
            free(pilha);
            return;
        }

        Node *node = malloc(sizeof(Node));
        if (node == NULL)
        {
            printf("Erro de alocacao de memoria\n");
            while (pilha->topo != NULL)
            {
                Node *aux = pilha->topo;
                pilha->topo = aux->next;
                free(aux);
            }
            free(pilha);
            return;
        }

        node->data = texto[i];
        node->next = pilha->topo;
        pilha->topo = node;
        i++;
    }

    if (texto[i] != 'C')
    {
        printf("Formato invalido\n");
        while (pilha->topo != NULL)
        {
            Node *node = pilha->topo;
            pilha->topo = node->next;
            free(node);
        }
        free(pilha);
        return;
    }
    i++;

    while (texto[i] != '\0')
    {
        if (pilha->topo == NULL || texto[i] != pilha->topo->data)
        {
            printf("Formato invalido\n");
            while (pilha->topo != NULL)
            {
                Node *node = pilha->topo;
                pilha->topo = node->next;
                free(node);
            }
            free(pilha);
            return;
        }

        Node *node = pilha->topo;
        pilha->topo = node->next;
        free(node);

        i++;
    }
    if (pilha->topo == NULL)
        printf("Formato valido\n");
    else
        printf("Formato invalido\n");

    free(pilha);
}

int main(void)
{
    char texto[] = "ABABBACABBABA";
    verificarFormato(texto);

    return 0;
}

/*
Nesse exercicio eu empilhei tudo que vinha antes do C, porque essa parte seria o x.
Depois do C eu fui comparando cada letra com o topo da pilha, ja que a pilha deixa
os valores na ordem inversa.
O cuidado foi verificar se so tinham letras A ou B antes do C, se o C existia, e se
no final a pilha ficou vazia. Se sobrar alguma coisa, o formato nao esta certo.
*/
