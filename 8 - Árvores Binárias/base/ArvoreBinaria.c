#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h" //inclui os Prot�tipos

struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
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

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada n�
    free(raiz);//libera a raiz
}

int insere_ArvBin(ArvBin* raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;
    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL)
        *raiz = novo;
    else{
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while(atual != NULL){
            ant = atual;
            if(valor == atual->info){
                free(novo);
                return 0;//elemento j� existe
            }

            if(valor > atual->info)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(valor > ant->info)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

// http://www.ime.usp.br/~pf/algoritmos/aulas/binst.html
int remove_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            if(atual == *raiz)
                *raiz = remove_atual(atual);
            else{
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

int estaVazia_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

struct NO* remove_atual(struct NO* atual) {
    struct NO *no1, *no2;
    if(atual->esq == NULL){
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL){
        no1 = no2;
        no2 = no2->dir;
    }
    // no2 � o n� anterior a r na ordem e-r-d
    // no1 � o pai de no2
    if(no1 != atual){
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

int altura_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}


void preOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%d\n",(*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}

// Varredura EM ordem (esquerda, raiz, direita)
// Em uma arvore binaria de busca imprime os valores em ordem crescente.
void emOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvBin(&((*raiz)->esq));
        printf("%d\n",(*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}

// Varredura POS ordem (esquerda, direita, raiz)
// Visita primeiro os dois filhos e so depois a raiz.
void posOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%d\n",(*raiz)->info);
    }
}

// Conta de forma recursiva quantos nos existem na arvore.
// Total = nos da subarvore esquerda + nos da subarvore direita + a propria raiz.
int totalNO_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 0;
    if(*raiz == NULL)
        return 0;
    int total_esq = totalNO_ArvBin(&((*raiz)->esq));
    int total_dir = totalNO_ArvBin(&((*raiz)->dir));
    return (total_esq + total_dir + 1);
}

// Consulta se um valor existe na arvore usando a propriedade da arvore de busca:
// vai para a direita se o valor for maior e para a esquerda se for menor.
int consulta_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info)
            return 1;
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}


// ===================== Lista 8 - Arvores Binarias =====================

// Exercicio 1 - conta quantos nos folha a arvore possui.
// No folha eh o no que nao tem filho a esquerda nem a direita. Se a arvore
// estiver vazia retorna 0; se o no for folha conta 1; senao soma as folhas das
// duas subarvores.
int contaFolhas_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 0;
    if(*raiz == NULL)
        return 0;
    if((*raiz)->esq == NULL && (*raiz)->dir == NULL)
        return 1;
    return contaFolhas_ArvBin(&((*raiz)->esq)) + contaFolhas_ArvBin(&((*raiz)->dir));
}

// Exercicio 2 - imprime cada no dizendo se eh raiz, pai (no interno) ou folha,
// e mostrando quem sao os filhos. Uso um auxiliar que recebe o no e um sinal
// dizendo se ele eh a raiz, ja que a raiz nao tem como ser descoberta sozinha.
void imprimeNO(struct NO* no, int ehRaiz){
    if(no == NULL)
        return;
    if(no->esq == NULL && no->dir == NULL){
        printf("%d (FOLHA)\n", no->info);
    }else{
        if(ehRaiz)
            printf("%d (RAIZ", no->info);
        else
            printf("%d (PAI", no->info);
        if(no->esq != NULL)
            printf(", filho esq: %d", no->esq->info);
        if(no->dir != NULL)
            printf(", filho dir: %d", no->dir->info);
        printf(")\n");
    }
    imprimeNO(no->esq, 0);
    imprimeNO(no->dir, 0);
}

void imprimeRelacoes_ArvBin(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL)
        return;
    imprimeNO(*raiz, 1);//comeca pela raiz
}

// Exercicio 3 - conta quantas vezes um valor aparece na arvore.
// Percorre a arvore inteira somando 1 cada vez que encontra o valor. Como o
// insere_ArvBin nao aceita repetidos, na pratica o retorno eh 0 ou 1, mas a
// funcao ja conta certo caso existissem valores iguais.
int contaValor_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    if(*raiz == NULL)
        return 0;
    int cont = 0;
    if((*raiz)->info == valor)
        cont = 1;
    return cont + contaValor_ArvBin(&((*raiz)->esq), valor) + contaValor_ArvBin(&((*raiz)->dir), valor);
}

// Exercicio 4 - imprime so os nos folha em ordem decrescente.
// Faco uma varredura direita -> raiz -> esquerda (o contrario do em ordem), que
// numa arvore de busca passa pelos valores do maior para o menor, e imprimo
// apenas quando o no for folha.
void imprimeFolhasDecrescente_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        imprimeFolhasDecrescente_ArvBin(&((*raiz)->dir));
        if((*raiz)->esq == NULL && (*raiz)->dir == NULL)
            printf("%d\n",(*raiz)->info);
        imprimeFolhasDecrescente_ArvBin(&((*raiz)->esq));
    }
}

// Exercicio 5 - verifica se duas arvores sao iguais (mesma forma E mesmos
// valores na mesma posicao). Auxiliar recursivo: as duas vazias = iguais; uma
// vazia e a outra nao = diferentes; valores diferentes = diferentes; senao tem
// que ser iguais a esquerda e a direita.
int iguaisNO(struct NO* a, struct NO* b){
    if(a == NULL && b == NULL)
        return 1;
    if(a == NULL || b == NULL)
        return 0;
    if(a->info != b->info)
        return 0;
    return iguaisNO(a->esq, b->esq) && iguaisNO(a->dir, b->dir);
}

int saoIguais_ArvBin(ArvBin *a, ArvBin *b){
    if(a == NULL || b == NULL)
        return 0;
    return iguaisNO(*a, *b);
}

// Exercicio 6 - elimina todos os valores pares da arvore.
// Para nao mexer nos ponteiros enquanto percorro, faco assim: procuro um valor
// par qualquer na arvore e, se achar, removo ele com o remove_ArvBin que ja
// existe. Repito ate nao sobrar nenhum par.
int buscaPar_NO(struct NO* no, int *valor){
    if(no == NULL)
        return 0;
    if(no->info % 2 == 0){
        *valor = no->info;
        return 1;
    }
    if(buscaPar_NO(no->esq, valor))
        return 1;
    return buscaPar_NO(no->dir, valor);
}

void eliminaPares_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    int valor;
    while(buscaPar_NO(*raiz, &valor))
        remove_ArvBin(raiz, valor);
}

// Exercicio 7 - verifica se duas arvores sao similares, ou seja, tem a mesma
// distribuicao de nos (a mesma forma), nao importando os valores. Igual ao
// exercicio 5, mas sem comparar o info dos nos.
int similaresNO(struct NO* a, struct NO* b){
    if(a == NULL && b == NULL)
        return 1;
    if(a == NULL || b == NULL)
        return 0;
    return similaresNO(a->esq, b->esq) && similaresNO(a->dir, b->dir);
}

int saoSimilares_ArvBin(ArvBin *a, ArvBin *b){
    if(a == NULL || b == NULL)
        return 0;
    return similaresNO(*a, *b);
}

// Exercicio 8 - varreduras que imprimem o info como char.
// Sao iguais as varreduras de int (pre e em ordem), so muda o %d para %c, para
// dar pra ver as letras inseridas na arvore.
void preOrdemChar_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%c ",(*raiz)->info);
        preOrdemChar_ArvBin(&((*raiz)->esq));
        preOrdemChar_ArvBin(&((*raiz)->dir));
    }
}

void emOrdemChar_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdemChar_ArvBin(&((*raiz)->esq));
        printf("%c ",(*raiz)->info);
        emOrdemChar_ArvBin(&((*raiz)->dir));
    }
}

void posOrdemChar_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdemChar_ArvBin(&((*raiz)->esq));
        posOrdemChar_ArvBin(&((*raiz)->dir));
        printf("%c ",(*raiz)->info);
    }
}

// Exercicio 9a - monta a arvore de expressao matematica.
// Aqui a insercao NAO eh de arvore de busca: a posicao do no depende da ordem
// da expressao, nao do valor. Recebo a expressao na ordem prefixa (operador
// antes dos operandos) e monto recursivamente: se o caractere eh operador,
// crio o no e monto a subarvore esquerda e a direita; se eh numero, eh folha.
int ehOperador(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

struct NO* montaExpressao(char *prefixa, int *i){
    char c = prefixa[*i];
    (*i)++;
    struct NO* novo = (struct NO*) malloc(sizeof(struct NO));
    novo->info = c;
    novo->esq = NULL;
    novo->dir = NULL;
    if(ehOperador(c)){
        novo->esq = montaExpressao(prefixa, i);
        novo->dir = montaExpressao(prefixa, i);
    }
    return novo;
}

ArvBin* criaExpressao_ArvBin(char *prefixa){
    ArvBin* raiz = cria_ArvBin();
    int i = 0;
    *raiz = montaExpressao(prefixa, &i);
    return raiz;
}

// Exercicio 9b - calcula o resultado da expressao guardada na arvore.
// Se o no eh folha, eh um numero (converto o char do digito para inteiro com
// - '0'). Se eh operador, calculo as duas subarvores e aplico a conta.
int calculaNO(struct NO* no){
    if(no == NULL)
        return 0;
    if(no->esq == NULL && no->dir == NULL)
        return no->info - '0';//folha eh um numero
    int e = calculaNO(no->esq);
    int d = calculaNO(no->dir);
    switch(no->info){
        case '+': return e + d;
        case '-': return e - d;
        case '*': return e * d;
        case '/': return e / d;
    }
    return 0;
}

int calculaExpressao_ArvBin(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL)
        return 0;
    return calculaNO(*raiz);
}

// Exercicio 9c - imprime a expressao na notacao infixa (esquerda, raiz, direita).
// Coloco parenteses em volta de cada operacao para deixar clara a ordem das
// contas. As notacoes prefixa e posfixa sao as varreduras pre e pos ordem em
// char (preOrdemChar_ArvBin e posOrdemChar_ArvBin), usadas no main.
void infixa_ArvBin(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL)
        return;
    struct NO* no = *raiz;
    if(no->esq == NULL && no->dir == NULL){
        printf("%c", no->info);//folha = numero, sem parenteses
        return;
    }
    printf("(");
    infixa_ArvBin(&(no->esq));
    printf(" %c ", no->info);
    infixa_ArvBin(&(no->dir));
    printf(")");
}
