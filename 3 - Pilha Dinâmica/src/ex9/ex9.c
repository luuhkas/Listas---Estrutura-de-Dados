#include <stdio.h>
#include <stdlib.h>
#include "pilha_headers.h"

void menu()
{
    printf("\n1-Inicializa pilha.\n");
    printf("2-Verifica se a pilha e vazia.\n");
    printf("3-Verifica se a pilha e cheia.\n");
    printf("4-Empilha o elemento na pilha.\n");
    printf("5-Desempilha elemento da pilha.\n");
    printf("6-Le topo de um pilha.\n");
    printf("7-Converte um numero decimal em binario.\n");
    printf("8-Sair.\n");
    printf("Opcao: ");
}

void converterBinario(int numero)
{
    Pilha *pilha = criarPilha();

    if (pilha == NULL)
        return;

    if (numero == 0)
    {
        printf("0\n");
        free(pilha);
        return;
    }

    while (numero > 0)
    {
        push(pilha, numero % 2);
        numero = numero / 2;
    }

    while (pilha->topo != NULL)
    {
        printf("%d", topo(pilha));
        pop(pilha);
    }

    printf("\n");
    free(pilha);
}

int main(void)
{
    Pilha *pilha = NULL;
    int opcao;
    int valor;

    do
    {
        menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            pilha = criarPilha();

            if (pilha != NULL)
                printf("Pilha inicializada.\n");
            break;

        case 2:
            if (pilha == NULL || pilha->topo == NULL)
                printf("A pilha esta vazia.\n");
            else
                printf("A pilha nao esta vazia.\n");
            break;

        case 3:
            printf("A pilha dinamica nao esta cheia.\n");
            break;

        case 4:
            if (pilha == NULL)
            {
                printf("Inicialize a pilha primeiro.\n");
                break;
            }

            printf("Digite o valor: ");
            scanf("%d", &valor);

            push(pilha, valor);
            break;

        case 5:
            if (pilha == NULL || pilha->topo == NULL)
                printf("A pilha esta vazia.\n");
            else
            {
                pop(pilha);
                printf("Elemento removido.\n");
            }
            break;

        case 6:
            if (pilha == NULL || pilha->topo == NULL)
                printf("A pilha esta vazia.\n");
            else
                printf("Topo: %d\n", topo(pilha));
            break;

        case 7:
            printf("Digite um numero decimal: ");
            scanf("%d", &valor);

            printf("Binario: ");
            converterBinario(valor);
            break;

        case 8:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida.\n");
        }

    } while (opcao != 8);

    return 0;
}

/*
Esse exercicio foi mais para juntar as funcoes da pilha em um menu. Usei o switch
para cada opcao e deixei o laco repetir ate o usuario escolher sair.
Na parte de converter decimal para binario, fui empilhando os restos da divisao por 2.
Depois foi so desempilhar e imprimir, porque a pilha ja coloca os bits na ordem certa.
*/
