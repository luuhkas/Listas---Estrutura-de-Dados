#include <stdio.h>
#include <stdlib.h>
#include "fila_headers.h"

int separa(Fila *f1, Fila *f2, int matricula)
{
    if (f1 == NULL || f2 == NULL || f1->inicio == NULL)
        return 1;

    Node *node = f1->inicio;

    while (node != NULL && node->data != matricula)
        node = node->next;

    if (node == NULL || node->next == NULL)
        return 1;

    f2->inicio = node->next;
    f2->fim = f1->fim;

    node->next = NULL;
    f1->fim = node;

    return 0;
}

int main(void)
{
    Fila *f1 = criarFila();
    Fila *f2 = criarFila();

    for (int i = 1; i <= 6; i++)
        enqueue(f1, i);

    printf("Fila original:\n");
    imprimirFila(f1);

    if (separa(f1, f2, 3) == 0)
    {
        printf("\nPrimeira fila depois do separa:\n");
        imprimirFila(f1);

        printf("\nSegunda fila depois do separa:\n");
        imprimirFila(f2);
    }
    else
        printf("Nao foi possivel separar a fila\n");

    return 0;
}

/*
Nesse exercicio eu procurei a primeira ocorrencia da matricula na fila.
Quando achei, a segunda fila passou a apontar para o proximo no, e a primeira
foi cortada naquele ponto.
O cuidado aqui foi arrumar o fim das duas filas, porque senao elas ficam apontando
para lugares errados depois da separacao.
*/
