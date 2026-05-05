#include <stdio.h>
#include <stdlib.h>
#include "fila_headers.h"

void preencherOrdenada(Fila *f1, Fila *f2, Fila *f3)
{
    if (f1 == NULL || f2 == NULL || f3 == NULL)
        return;

    while (f1->inicio != NULL && f2->inicio != NULL)
    {
        if (frente(f1) <= frente(f2))
        {
            enqueue(f3, frente(f1));
            dequeue(f1);
        }
        else
        {
            enqueue(f3, frente(f2));
            dequeue(f2);
        }
    }

    while (f1->inicio != NULL)
    {
        enqueue(f3, frente(f1));
        dequeue(f1);
    }

    while (f2->inicio != NULL)
    {
        enqueue(f3, frente(f2));
        dequeue(f2);
    }
}

int main(void)
{
    Fila *f1 = criarFila();
    Fila *f2 = criarFila();
    Fila *f3 = criarFila();

    enqueue(f1, 1);
    enqueue(f1, 3);
    enqueue(f1, 5);

    enqueue(f2, 2);
    enqueue(f2, 4);
    enqueue(f2, 6);

    preencherOrdenada(f1, f2, f3);

    printf("Fila final em ordem crescente:\n");
    imprimirFila(f3);

    return 0;
}

/*
Aqui eu comparei sempre o inicio das duas filas que ja estavam ordenadas.
O menor valor ia para a terceira fila e era removido da fila original.
Quando uma das filas acabava, eu colocava o resto da outra na terceira fila.
*/
