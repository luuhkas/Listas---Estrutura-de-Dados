#include <stdio.h>
#include <stdlib.h>

int inverte_vetor(int *v1, int *v2, int n)
{
    v2[0] = v1[5]; // necessario ser inicializado fora do loop para poder comecar a comparar no laco
    int max = v2[0], min = v2[0]; // mesma coisa, precisar iniciar antes do laco
    
    printf("Os elementos do vetor v2 sao: ");
    for(int i = 1, j = n - 1; i <= n; i++, j--) // comecando na posicao 1 pq a 0 ja foi inicializada previamente
    {
        v2[i] = v1[j];
        printf("%d ", v2[i]);

        if(v2[i] > max) // logica para descobrir o maior
            max = v2[i];
    }
    return max;
}

int main(void)
{
    int v1[5] = {1, 2, 3, 4, 5}, *v2;

    if((v2 = malloc(sizeof(int) * 5)) == NULL)
    {
        printf("Erro de alocacao de memoria");
        return 1;
    }
    printf("\nO maior valor eh: %d\n", inverte_vetor(v1, v2, 5));

    free(v2);
    return 0;
}

/*
A lógica nessa questão foi de criar um ponteiro de tamanho fixo oara seguir o exemplo do exercício
e o outro eu criei de tamanho dinamico, apenas dando espaco a ele.
A função apenas fazia o papel de preencher de forma invertida, copiando
os valores do primeiro vetor previamente criado.
*/