#include <stdio.h>
#include <stdlib.h>
#include "pilha_headers.h"

void imprimirInversa(char texto[])
{
    Pilha *pilha = criarPilha();

    if (pilha == NULL)
        return;

    for (int i = 0; texto[i] != '\0'; i++)
    {
        Node *node = malloc(sizeof(Node));

        if (node == NULL)
        {
            printf("Erro de alocacao de memoria\n");
            return;
        }

        node->data = texto[i];
        node->next = pilha->topo;
        pilha->topo = node;
    }

    while (pilha->topo != NULL)
    {
        Node *node = pilha->topo;
        printf("%c", node->data);
        pilha->topo = node->next;
        free(node);
    }

    printf("\n");
    free(pilha);
}

void verificarPalindromo(char texto[])
{
    Pilha *pilha = criarPilha();

    if (pilha == NULL)
        return;

    for (int i = 0; texto[i] != '\0'; i++)
    {
        if (texto[i] == ' ' || texto[i] == '.')
            continue;

        Node *node = malloc(sizeof(Node));

        if (node == NULL)
        {
            printf("Erro de alocacao de memoria\n");
            return;
        }

        node->data = texto[i];
        node->next = pilha->topo;
        pilha->topo = node;
    }

    int i = 0;
    int palindromo = 1;

    while (pilha->topo != NULL)
    {
        while (texto[i] == ' ' || texto[i] == '.')
            i++;

        Node *node = pilha->topo;

        if (texto[i] != node->data)
            palindromo = 0;

        pilha->topo = node->next;
        free(node);
        i++;
    }

    if (palindromo)
        printf("A palavra eh palindromo\n");
    else
        printf("A palavra nao eh palindromo\n");

    free(pilha);
}

int main(void)
{
    char texto1[] = "abcdefg";
    char texto2[] = "arara";

    imprimirInversa(texto1);
    verificarPalindromo(texto2);

    return 0;
}

/*
Na primeira parte, para imprimir invertido, eu empilhei cada letra da string.
Como a pilha sempre tira primeiro o ultimo que entrou, na hora de imprimir ela ja
sai na ordem inversa.
Na parte do palindromo foi parecido, mas comparando o texto original com o que saia
da pilha. O detalhe foi ignorar espacos e pontos, como o enunciado pediu.
*/
