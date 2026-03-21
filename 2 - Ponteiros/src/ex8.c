#include <stdio.h>
#include <stdlib.h>

void readArray(int *vet, int size)
{
    for(int i = 0; i < size; i++, vet++)
    {
        printf("Digite o vetor de posicao %d: ", i + 1);
        scanf("%d", vet);
    }
}

int main(void)
{
    int n, *vet;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    if((vet = malloc(sizeof(int) * n)) == NULL)
    {
        printf("Erro de alocacao de memoria!\n");
        return 1;
    }

    readArray(vet, n);

    printf("\n\n");

    for (int i = 0; i < n; i++, vet++)
        printf("vetor de posicao: %d: %d\n", i + 1, *vet);

    free(vet);
    return 0;
}

/*
Essa questão eu nao cheguei a ter dificuldade, mas fiquei confuso sobre o que
o enunciado pedia, mas acredito que eu tenha feito certo. Montei uma função apenas
para pedir ao usuario os elementos do vetor e ela le esses elementos e guarda no vetor.
Decidir fazer usando aritimética de vetores, o que daria no mesmo caso eu fosse usando as casas do vetor.
Das duas formas representar o endereço do vetor. Fiz dessa forma pq me parece que estou usando aritmética de vetores
e da outra forma não. Eu prefiro alocar na memória já verificando se deu certo, me acostumei a fazer dessa forma.
De resto não teve nenhuma lógica nova, foi apenas seguindo o que o enunciado pedia.
*/