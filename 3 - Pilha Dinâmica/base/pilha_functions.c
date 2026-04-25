#include <stdio.h>
#include <stdlib.h>
#include "pilha_headers.h"

// estou motando a estrutura do 0 com a finidade de treinar/lembrar

// aqui basta alocar o espaco na memoria e apontar o topo para NULL, pilha criada
Pilha *criarPilha()
{
    Pilha *pilha;
    if ((pilha = malloc(sizeof(Pilha))) == NULL)
    {
        printf("Erro de alocacao memoria\n");
        return NULL;
    }

    pilha->topo = NULL;
    return pilha;
}

void imprimirPilha(Pilha *pilha)
{
    if (pilha == NULL)
        return;

    // declara um no que aponta pra onde a pilha(ponteiro) aponta.
    Node *no = pilha->topo;
    while (no != NULL) // enquanto nao chegar a NULL (fim da pilha) continua andando de no em no
    {
        printf("Dado: %d\n", no->data); // imprimir o dado que esta na pilha, que nesse caso eh uma pilha de inteiros
        no = no->next;                  // no passa a apontar para o proximo no (o que faz passar pelos nos da pilha)
    }
}

int push(Pilha *pilha, int data)
{
    if (pilha == NULL)
        return 1;

    Node *node;
    if ((node = malloc(sizeof(Node))) == NULL)
    {
        printf("Erro de alocacao de memoria");
        return -1;
    }

    // o segredo do push esta aqui: (na pilha quem entra primeiro é o último, por isso o next sempre aponta para o valor anterior ao atual atribuido)
    node->data = data;        // atribuicao do valor no no da pilha
    node->next = pilha->topo; // o ponteiro next da pilha aponta pra onde o topo esta apontando. no caso o next eh sempre onde o topo estava apontando de inicio.
    pilha->topo = node;       // topo passa a aponta pro atual no da pilha que recebeu o dado.

    return 0;
}

// essa é bem tranquila pq eh so para percorrer a pilha e dar free no no
int pop(Pilha *pilha)
{
    // condicoes para ver se o topo esta apontando para NULL ou se a pilha existe. se cumpridas, retorna como um erro
    if (pilha == NULL || pilha->topo == NULL)
        return 1;

    Node *node = pilha->topo; // cria um no que aponta para o topo da pilha
    pilha->topo = node->next; // o topo da pilha passa a ser o proximo no

    free(node); // free seguro pq o topo da pilha ja andou e o no que antes era apontado pelo topo eh removido.
    return 0;
}

// retorna o valor do dado que o no do topo da pilha
int topo(Pilha *pilha)
{
    if (pilha == NULL || pilha->topo == NULL)
        return 0;

    return pilha->topo->data;
}
