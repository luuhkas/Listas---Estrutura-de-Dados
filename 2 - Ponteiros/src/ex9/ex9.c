#include <stdio.h>
#include <stdlib.h>

int **matrixAloc(int m, int n)
{
    int **matrix;

    // chamada '1`. alocacao de memoria pro vetor de ponteiros
    if ((matrix = malloc(sizeof(int *) * m)) == NULL)
    {
        printf("Erro de alocacao de memoria");
        exit(1);
    }

    // chamada 'm'. alocacao de memoria de cada vetor das linhas da matriz
    for (int i = 0; i < m; i++)
    {
        if ((matrix[i] = malloc(sizeof(int) * n)) == NULL)
        {
            printf("Erro de alocacao de memoria");
            exit(-1);
        }
    }
    return matrix;
}

// laco de repeticao para dar free tanto nos vetores das linhas, quanto no vetor de ponteiros
void freeMatrixAloc(int **matrix, int m, int n)
{
    for (int i = 0; i < m; i++)
        free(matrix[i]);
    free(matrix);
}

int main(void)
{
    int **matrix, m = 5, n = 6;

    matrix = matrixAloc(m, n);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = rand() % 100;
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}

/*
Questao mais iinteressante da lista, basicamente o coracao dela é pensar sobre como fazer
as 1+m chamadas. Depois de um tempo cheguei na conclusao que essa é a quantidade de mallocs que deveriam ser feitos.
Outra parte dificil foi explicar nos comentarios essa parte de vetor de ponteiros.
Basicamente vetor é um ponteiro, entao nesse caso, estou criando um ponteiro duplo que vai apontar para m ponteiros que correspondem as linhas da matriz.
*/