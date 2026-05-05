#include <stdio.h>
#include <stdlib.h>
#include "fila_headers.h"

void menu()
{
    printf("\n1-Inicializa fila.\n");
    printf("2-Verifica se a fila e vazia.\n");
    printf("3-Verifica se a fila e cheia.\n");
    printf("4-Enfileira o elemento na fila.\n");
    printf("5-Desefileira elemento da fila.\n");
    printf("6-Le o numero no inicio da fila.\n");
    printf("7-Testar qual fila possui mais elementos.\n");
    printf("8-Furar a fila.\n");
    printf("9-Sair.\n");
    printf("Opcao: ");
}

int tamanhoFila(Fila *fila)
{
    int count = 0;

    if (fila == NULL)
        return count;

    Node *node = fila->inicio;
    while (node != NULL)
    {
        count++;
        node = node->next;
    }

    return count;
}

int furaFila(Fila *fila, int data)
{
    if (fila == NULL)
        return 1;

    Node *node = malloc(sizeof(Node));
    if (node == NULL)
        return 1;

    node->data = data;
    node->next = fila->inicio;
    fila->inicio = node;

    if (fila->fim == NULL)
        fila->fim = node;

    return 0;
}

int main(void)
{
    Fila *fila1 = NULL;
    Fila *fila2 = criarFila();
    int opcao;
    int valor;

    enqueue(fila2, 10);
    enqueue(fila2, 20);

    do
    {
        menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            fila1 = criarFila();
            printf("Fila inicializada.\n");
            break;

        case 2:
            if (fila1 == NULL || fila1->inicio == NULL)
                printf("A fila esta vazia.\n");
            else
                printf("A fila nao esta vazia.\n");
            break;

        case 3:
            printf("A fila dinamica nao esta cheia.\n");
            break;

        case 4:
            if (fila1 == NULL)
            {
                printf("Inicialize a fila primeiro.\n");
                break;
            }

            printf("Digite o valor: ");
            scanf("%d", &valor);
            enqueue(fila1, valor);
            break;

        case 5:
            if (fila1 == NULL || fila1->inicio == NULL)
                printf("A fila esta vazia.\n");
            else
            {
                dequeue(fila1);
                printf("Elemento removido.\n");
            }
            break;

        case 6:
            if (fila1 == NULL || fila1->inicio == NULL)
                printf("A fila esta vazia.\n");
            else
                printf("Inicio: %d\n", frente(fila1));
            break;

        case 7:
            if (tamanhoFila(fila1) > tamanhoFila(fila2))
                printf("A primeira fila tem mais elementos.\n");
            else if (tamanhoFila(fila1) < tamanhoFila(fila2))
                printf("A segunda fila tem mais elementos.\n");
            else
                printf("As duas filas tem a mesma quantidade.\n");
            break;

        case 8:
            if (fila1 == NULL)
            {
                printf("Inicialize a fila primeiro.\n");
                break;
            }

            printf("Digite o valor: ");
            scanf("%d", &valor);
            furaFila(fila1, valor);
            break;

        case 9:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida.\n");
        }

    } while (opcao != 9);

    return 0;
}

/*
Esse exercicio junta as operacoes da fila em um menu, parecido com o menu da pilha.
Como a fila e dinamica, considerei que ela nao fica cheia.
Para testar qual fila tem mais elementos, eu contei os nos das duas filas. Para furar
a fila, coloquei um novo no direto no inicio.
*/
