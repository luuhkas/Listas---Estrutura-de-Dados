#include <stdio.h>
#include <stdlib.h>

int main (void)
{

    int n;

    printf("Digite o tamanho do vetor:");
    scanf("%d", &n);

    int* vet = malloc(sizeof(int) * n); // não precisou do cast pq é garantido que vet é *int

    for(int i = 0; i < n; i++)
    {
        vet[i] = i;
        printf("%d ", vet[i]);
    }

    return 0;
}

// questão simples de uso do malloc. depois preenchi os elementos do vetor apenas com a finalidade de teste.