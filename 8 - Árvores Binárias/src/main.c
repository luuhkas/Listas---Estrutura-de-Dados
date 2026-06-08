#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

int main(){
    // Arvore base para os exercicios 1 a 5.
    // Inserindo {50,30,70,20,40,60,80} fica assim:
    //            50
    //          /    \
    //        30      70
    //       /  \    /  \
    //     20   40  60   80
    int N = 7, dados[7] = {50,30,70,20,40,60,80};
    ArvBin* arv = cria_ArvBin();
    int i;
    for(i=0; i < N; i++)
        insere_ArvBin(arv, dados[i]);

    printf("Arvore base em ordem (esq, raiz, dir):\n");
    emOrdem_ArvBin(arv);

    // Exercicio 1 - nos folha
    printf("\n--- Exercicio 1: total de nos folha ---\n");
    printf("Folhas: %d\n", contaFolhas_ArvBin(arv));

    // Exercicio 2 - imprime identificando raiz, pais e folhas
    printf("\n--- Exercicio 2: raiz, pais e folhas ---\n");
    imprimeRelacoes_ArvBin(arv);

    // Exercicio 3 - quantas vezes um valor aparece
    printf("\n--- Exercicio 3: quantas vezes o valor aparece ---\n");
    printf("Valor 40 aparece %d vez(es)\n", contaValor_ArvBin(arv, 40));
    printf("Valor 99 aparece %d vez(es)\n", contaValor_ArvBin(arv, 99));

    // Exercicio 4 - folhas em ordem decrescente
    printf("\n--- Exercicio 4: nos folha em ordem decrescente ---\n");
    imprimeFolhasDecrescente_ArvBin(arv);

    // Exercicio 5 - arvores iguais
    // arv2 igual a arv; arv3 com a mesma forma mas um valor trocado (80 -> 99).
    ArvBin* arv2 = cria_ArvBin();
    for(i=0; i < N; i++)
        insere_ArvBin(arv2, dados[i]);
    int dados3[7] = {50,30,70,20,40,60,99};
    ArvBin* arv3 = cria_ArvBin();
    for(i=0; i < N; i++)
        insere_ArvBin(arv3, dados3[i]);

    printf("\n--- Exercicio 5: arvores iguais ---\n");
    printf("arv == arv2 (mesmos valores): %d\n", saoIguais_ArvBin(arv, arv2));
    printf("arv == arv3 (um valor trocado): %d\n", saoIguais_ArvBin(arv, arv3));

    // Exercicio 7 - arvores similares (mesma forma, valores nao importam)
    // arv4 tem forma diferente (so 3 nos).
    int dados4[3] = {50,30,70};
    ArvBin* arv4 = cria_ArvBin();
    for(i=0; i < 3; i++)
        insere_ArvBin(arv4, dados4[i]);

    printf("\n--- Exercicio 7: arvores similares ---\n");
    printf("arv ~ arv3 (mesma forma, valor trocado): %d\n", saoSimilares_ArvBin(arv, arv3));
    printf("arv ~ arv4 (forma diferente): %d\n", saoSimilares_ArvBin(arv, arv4));

    // Exercicio 6 - elimina os valores pares
    // Uso uma arvore a parte misturando pares e impares.
    // {8,3,10,1,6,14,4,7,13} -> pares: 8,10,6,14,4 ; impares: 3,1,7,13
    int M = 9, dadosP[9] = {8,3,10,1,6,14,4,7,13};
    ArvBin* arvP = cria_ArvBin();
    for(i=0; i < M; i++)
        insere_ArvBin(arvP, dadosP[i]);

    printf("\n--- Exercicio 6: elimina valores pares ---\n");
    printf("Antes (em ordem):\n");
    emOrdem_ArvBin(arvP);
    eliminaPares_ArvBin(arvP);
    printf("Depois de tirar os pares (em ordem):\n");
    emOrdem_ArvBin(arvP);

    // Exercicio 8 - insere e imprime as letras
    char letras[14] = {'M','F','S','D','J','P','U','A','E','H','Q','T','W','K'};
    ArvBin* arvL = cria_ArvBin();
    for(i=0; i < 14; i++)
        insere_ArvBin(arvL, letras[i]);

    printf("\n--- Exercicio 8: arvore de letras ---\n");
    printf("Pre ordem (mostra a estrutura): ");
    preOrdemChar_ArvBin(arvL);
    printf("\nEm ordem (sai em ordem alfabetica): ");
    emOrdemChar_ArvBin(arvL);
    printf("\n");

    // Exercicio 9 - arvore de expressao matematica
    // Passo a expressao na ordem prefixa. Pela figura: + * - 6 3 + 4 1 5
    // que monta ((6-3) * (4+1)) + 5.
    ArvBin* arvE = criaExpressao_ArvBin("+*-63+415");

    printf("\n--- Exercicio 9: arvore de expressao ---\n");
    printf("Resultado da expressao: %d\n", calculaExpressao_ArvBin(arvE));
    printf("Infixa:  ");
    infixa_ArvBin(arvE);
    printf("\nPrefixa: ");
    preOrdemChar_ArvBin(arvE);
    printf("\nPosfixa: ");
    posOrdemChar_ArvBin(arvE);
    printf("\n");

    libera_ArvBin(arv);
    libera_ArvBin(arv2);
    libera_ArvBin(arv3);
    libera_ArvBin(arv4);
    libera_ArvBin(arvP);
    libera_ArvBin(arvL);
    libera_ArvBin(arvE);
    printf("\nFim!\n");
    return 0;
}
