#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

int main(){
    int i;

    // =====================================================================
    // Exercicio 2a - montagem passo a passo (as rotacoes saem no terminal).
    // Insiro {50,30,20,70,40,35,37,38,10,32,45,42,25,47,36} e mostro a
    // arvore final em ordem com a altura H e o fator de balanceamento fb de
    // cada no. Como todo no fica com fb 0 ou 1, eh uma AVL.
    // =====================================================================
    int Na = 15, a[15] = {50,30,20,70,40,35,37,38,10,32,45,42,25,47,36};
    ArvAVL* arvA = cria_ArvAVL();
    printf("=== Exercicio 2a: inserindo e rotacionando ===\n");
    for(i=0; i<Na; i++){
        printf("Insere %d: ", a[i]);
        insere_ArvAVL(arvA, a[i]);   // imprime a rotacao quando acontece
        printf("ok\n");
    }
    printf("\nArvore 2a final (em ordem, com H e fb):\n");
    emOrdem_ArvAVL(arvA);
    printf("eh AVL? %d (esperado 1)\n", ehAVL_ArvAVL(arvA));

    // =====================================================================
    // Exercicio 4 - RotacaoRR (rotacao simples a esquerda).
    // Caso classico RR: insiro 10, 20, 30 em ordem crescente. Ao inserir o
    // 30 a arvore fica pesada a direita e dispara exatamente a RotacaoRR,
    // que coloca o 20 na raiz.
    // =====================================================================
    printf("\n=== Exercicio 4: RotacaoRR (insere 10,20,30) ===\n");
    int rr[3] = {10,20,30};
    ArvAVL* arvRR = cria_ArvAVL();
    for(i=0; i<3; i++)
        insere_ArvAVL(arvRR, rr[i]);   // ao inserir 30 imprime "RotacaoRR"
    printf("Depois da RR (em ordem) - a raiz vira 20:\n");
    emOrdem_ArvAVL(arvRR);

    // =====================================================================
    // Exercicio 7 - verifica se eh AVL.
    // Uso o ehAVL para CONFERIR o exercicio 1: monto as 4 arvores do
    // enunciado e classifico cada uma. Esperado: 0, 0, 1, 0.
    // (arvores 1, 2 e 4 tem um no com fb 2; a 3 eh um no sozinho.)
    // =====================================================================
    printf("\n=== Exercicio 7: ehAVL (conferindo o exercicio 1) ===\n");
    int esperado[4] = {0, 0, 1, 0};
    for(i=1; i<=4; i++){
        ArvAVL* arvE1 = arvoreExercicio1(i);
        printf("Arvore %d do exercicio 1: ehAVL = %d (esperado %d)\n",
               i, ehAVL_ArvAVL(arvE1), esperado[i-1]);
        libera_ArvAVL(arvE1);
    }

    // =====================================================================
    // Exercicio 8 - transforma uma arvore de busca qualquer em AVL.
    // Entrada em ordem crescente {1..7}: numa BST comum isso viraria uma
    // escada (altura 6). A transforma reconstroi balanceada (altura 2) e o
    // ehAVL confirma. Mostro a entrada e a saida, ambas em ordem.
    // =====================================================================
    printf("\n=== Exercicio 8: transforma(BST) -> AVL ===\n");
    int orig[7] = {1,2,3,4,5,6,7};
    ArvAVL* arvBusca = cria_ArvAVL();
    for(i=0; i<7; i++)
        insere_ArvAVL(arvBusca, orig[i]);
    printf("Entrada (em ordem):\n");
    emOrdem_ArvAVL(arvBusca);

    ArvAVL* arvNova = transforma_ArvAVL(arvBusca);
    printf("Saida transformada (em ordem, com H e fb):\n");
    emOrdem_ArvAVL(arvNova);
    printf("eh AVL? %d (esperado 1)\n", ehAVL_ArvAVL(arvNova));

    libera_ArvAVL(arvA);
    libera_ArvAVL(arvRR);
    libera_ArvAVL(arvBusca);
    libera_ArvAVL(arvNova);
    printf("\nFim!\n");
    return 0;
}
