#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h" //inclui os Prototipos

struct NO{
    int info;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada no
    free(raiz);//libera a raiz
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

void preOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("No %d: %d\n",(*raiz)->info,altura_NO(*raiz));
        preOrdem_ArvAVL(&((*raiz)->esq));
        preOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        printf("No %d: H(%d) fb(%d)\n",(*raiz)->info,altura_NO(*raiz),fatorBalanceamento_NO(*raiz));
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void posOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvAVL(&((*raiz)->esq));
        posOrdem_ArvAVL(&((*raiz)->dir));
        printf("%d\n",(*raiz)->info);
    }
}

int consulta_ArvAVL(ArvAVL *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

//=================================
void RotacaoLL(ArvAVL *raiz){//LL
    printf("RotacaoLL\n");
    struct NO *B;
    B = (*raiz)->esq;
    (*raiz)->esq = B->dir;
    B->dir = *raiz;
    (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*raiz)->altura) + 1;
    *raiz = B;
}

//---------------------------------
// EXERCICIO 4: rotacao simples a esquerda (RR).
// Eh o espelho da RotacaoLL e estava faltando no projeto do professor
// (ela ja era chamada por RotacaoLR, RotacaoRL, insere e remove).
// O no desbalanceado esta pesado a direita: o filho da direita (B) sobe
// e vira raiz da subarvore, e o no antigo desce para a esquerda de B.
void RotacaoRR(ArvAVL *raiz){//RR
    printf("RotacaoRR\n");
    struct NO *B;
    B = (*raiz)->dir;            // B = filho direito, que vai subir
    (*raiz)->dir = B->esq;       // o "neto" da esquerda de B passa a ser filho direito do no antigo
    B->esq = *raiz;              // o no antigo desce para a esquerda de B
    (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*raiz)->altura) + 1;
    *raiz = B;                   // B vira a nova raiz da subarvore
}
//---------------------------------

void RotacaoLR(ArvAVL *raiz){//LR
    RotacaoRR(&(*raiz)->esq);
    RotacaoLL(raiz);
}

void RotacaoRL(ArvAVL *raiz){//RL
    RotacaoLL(&(*raiz)->dir);
    RotacaoRR(raiz);
}

int insere_ArvAVL(ArvAVL *raiz, int valor){
    int res;
    if(*raiz == NULL){//arvore vazia ou no folha
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        novo->info = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if(valor < atual->info){
        if((res = insere_ArvAVL(&(atual->esq), valor)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(valor < (*raiz)->esq->info ){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(valor > atual->info){
            if((res = insere_ArvAVL(&(atual->dir), valor)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if((*raiz)->dir->info < valor){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}

struct NO* procuraMenor(struct NO* atual){
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int remove_ArvAVL(ArvAVL *raiz, int valor){
	if(*raiz == NULL){// valor nao existe
	    printf("valor nao existe!!\n");
	    return 0;
	}

    int res;
	if(valor < (*raiz)->info){
	    if((res = remove_ArvAVL(&(*raiz)->esq,valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}

	if((*raiz)->info < valor){
	    if((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}

	if((*raiz)->info == valor){
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){// no tem 1 filho ou nenhum
			struct NO *oldNode = (*raiz);
			if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
			free(oldNode);
		}else { // no tem 2 filhos
			struct NO* temp = procuraMenor((*raiz)->dir);
			(*raiz)->info = temp->info;
			remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);
            if(fatorBalanceamento_NO(*raiz) >= 2){
				if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL)
            (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
		return 1;
	}

	(*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;

	return res;
}

//=================================
// EXERCICIO 7: verifica se uma arvore eh AVL.
// Uma AVL eh uma arvore de busca em que, em TODO no, a diferenca de altura
// entre as subarvores esquerda e direita eh no maximo 1 (|fb| <= 1).
// Calculo a altura real de cada no na hora (sem confiar no campo ->altura,
// que pode nao estar preenchido numa arvore montada "na mao").

int alturaReal_NO(struct NO* no){
    if(no == NULL)
        return -1;
    return maior(alturaReal_NO(no->esq), alturaReal_NO(no->dir)) + 1;
}

int ehAVL_NO(struct NO* no){
    if(no == NULL)
        return 1;// arvore/subarvore vazia eh AVL
    int he = alturaReal_NO(no->esq);
    int hd = alturaReal_NO(no->dir);
    if(labs(he - hd) >= 2)
        return 0;// achou um no desbalanceado
    // e os dois lados tambem precisam ser AVL
    return ehAVL_NO(no->esq) && ehAVL_NO(no->dir);
}

int ehAVL_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    return ehAVL_NO(*raiz);
}

//=================================
// EXERCICIO 8: dada uma arvore de busca QUALQUER (mesmo desbalanceada),
// devolve uma NOVA arvore AVL com os mesmos valores.
// Ideia: 1) percorro em ordem -> sai um vetor JA ordenado;
//        2) insiro sempre o elemento do MEIO primeiro (e recursivamente os
//           meios das metades). Inserindo o meio como raiz a arvore ja nasce
//           balanceada, e o proprio insere_ArvAVL garante que continua AVL.

void coletaEmOrdem(struct NO* no, int *vet, int *n){
    if(no == NULL)
        return;
    coletaEmOrdem(no->esq, vet, n);
    vet[(*n)++] = no->info;
    coletaEmOrdem(no->dir, vet, n);
}

void insereMeio(ArvAVL *nova, int *vet, int ini, int fim){
    if(ini > fim)
        return;
    int meio = (ini + fim) / 2;
    insere_ArvAVL(nova, vet[meio]);
    insereMeio(nova, vet, ini, meio - 1);
    insereMeio(nova, vet, meio + 1, fim);
}

ArvAVL* transforma_ArvAVL(ArvAVL *raiz){
    ArvAVL* nova = cria_ArvAVL();
    if(raiz == NULL || *raiz == NULL)
        return nova;// arvore vazia -> AVL vazia

    int total = totalNO_ArvAVL(raiz);
    int *vet = (int*) malloc(total * sizeof(int));
    int n = 0;
    coletaEmOrdem(*raiz, vet, &n);// vet fica ordenado
    insereMeio(nova, vet, 0, n - 1);
    free(vet);
    return nova;
}

//=================================
// Auxiliar de teste para o EXERCICIO 1.
// Monta os nos ligando-os direto (sem passar pelo insere, que rebalancearia),
// para reproduzir exatamente as 4 arvores do enunciado - inclusive as que NAO
// sao AVL - e poder conferi-las com o ehAVL do exercicio 7.
struct NO* noBruto(int info, struct NO* esq, struct NO* dir){
    struct NO* no = (struct NO*) malloc(sizeof(struct NO));
    no->info = info;
    no->esq = esq;
    no->dir = dir;
    no->altura = 0;// nao usado pelo ehAVL, que recalcula a altura real
    return no;
}

ArvAVL* arvoreExercicio1(int qual){
    ArvAVL* raiz = cria_ArvAVL();
    if(qual == 1){
        // 57(22(10(0,15)), 60(_,88)) -> no 22 tem fb 2, NAO eh AVL
        *raiz = noBruto(57,
                    noBruto(22, noBruto(10, noBruto(0,NULL,NULL), noBruto(15,NULL,NULL)), NULL),
                    noBruto(60, NULL, noBruto(88,NULL,NULL)));
    }else if(qual == 2){
        // 57(22(10(0,15)), 60(58(_,59),88)) -> no 22 tem fb 2, NAO eh AVL
        *raiz = noBruto(57,
                    noBruto(22, noBruto(10, noBruto(0,NULL,NULL), noBruto(15,NULL,NULL)), NULL),
                    noBruto(60, noBruto(58, NULL, noBruto(59,NULL,NULL)), noBruto(88,NULL,NULL)));
    }else if(qual == 3){
        // 57 sozinho -> eh AVL
        *raiz = noBruto(57, NULL, NULL);
    }else{
        // 8(4(2(1,3),6(5,7)), 12(_,14(13,15))) -> no 12 tem fb 2, NAO eh AVL
        *raiz = noBruto(8,
                    noBruto(4, noBruto(2, noBruto(1,NULL,NULL), noBruto(3,NULL,NULL)),
                               noBruto(6, noBruto(5,NULL,NULL), noBruto(7,NULL,NULL))),
                    noBruto(12, NULL, noBruto(14, noBruto(13,NULL,NULL), noBruto(15,NULL,NULL))));
    }
    return raiz;
}
