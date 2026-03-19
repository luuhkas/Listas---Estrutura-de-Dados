#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int code;
    char name[50];
    float price;
} *Produto;

int main(void)
{
    int n;
    Produto produto;

    printf("Digite quantos produtos deseja cadastrar: ");
    scanf("%d", &n);

    if((produto = malloc(sizeof(Produto) * n)) == NULL)
    {
        printf("Erro de alocacao dinamica");
        return 1;
    }

    for(int i = 0; i < n; i++)
    {
    printf("\nDigite o codigo do produto %d: ", i + 1);
    scanf("%d", &produto[i].code);

    printf("\nDigite o nome do produto %d: ", i + 1);
    scanf(" %s", produto[i].name);

    printf("\nDigite o valor do produto %d: ", i + 1);
    scanf("%f", &produto[i].price);
    }

    printf("\nSua lista de produtos:\n\n");

    for(int i = 0; i < n; i++)
        printf("Code: %d | Name: %s\n", produto[i].code, produto[i].name);

    printf("\nDigite o codigo do produto para consultar seu preco: ");
    int consulta;
    scanf("%d", &consulta);

    for(int i = 0; i < n; i++)
    {
        if (produto[i].code == consulta)
            printf("\nO valor do produto de codigo: %d eh: %.2f reais\n", produto[i].code, produto[i].price);
        else printf("Produto não encontrado!\n");    
    }

    free(produto);
    return 0;
}

/*
Questão longa, porém não tive muitas dificuldades. Requer conhecimento básico de struct.
E também a lógica de criar a struct como um ponteiro para transformar seus elementos em vetores.
Dessa forma ficou mais fácil de acessar as casas equivalentes de acordo com a casa do vetor.
De resto foi apenas bastante printf.
*/