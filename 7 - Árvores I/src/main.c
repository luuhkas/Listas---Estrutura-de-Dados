#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

int main(){
    int N = 8, dados[8] = {50,100,30,20,40,45,35,37};

    ArvBin* raiz = cria_ArvBin();

    int i;
    for(i=0; i < N; i++)
        insere_ArvBin(raiz,dados[i]);

    // Exercicio 1 e 2 - insercao e varreduras
    printf("PRE ordem (raiz, esq, dir):\n");
    preOrdem_ArvBin(raiz);

    printf("\nEM ordem (esq, raiz, dir) - sai em ordem crescente:\n");
    emOrdem_ArvBin(raiz);

    printf("\nPOS ordem (esq, dir, raiz):\n");
    posOrdem_ArvBin(raiz);

    // Exercicio 3 - total de nos
    printf("\nTotal de nos: %d\n", totalNO_ArvBin(raiz));

    // Exercicio 4 - consulta de valores
    printf("\nConsulta 45: %d (1 = existe, 0 = nao existe)\n", consulta_ArvBin(raiz, 45));
    printf("Consulta 99: %d (1 = existe, 0 = nao existe)\n", consulta_ArvBin(raiz, 99));

    // Exercicio 1 e 5 - remocao (remove_ArvBin usa remove_atual)
    printf("\nRemovendo o 50 (raiz)...\n");
    if(remove_ArvBin(raiz,50)){
        printf("Removido. EM ordem apos a remocao:\n");
        emOrdem_ArvBin(raiz);
    }else
        printf("NAO removido\n");

    printf("\nTotal de nos apos a remocao: %d\n", totalNO_ArvBin(raiz));

    libera_ArvBin(raiz);
    printf("\nFim!\n");
    return 0;
}
