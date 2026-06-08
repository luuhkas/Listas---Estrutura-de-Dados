# Lista 8 - Arvores Binarias

Todos os exercicios foram feitos sobre o projeto `ProjArvoreBinaria` do professor,
como pede o enunciado. As funcoes novas foram implementadas em
`base/ArvoreBinaria.c` e os testes ficam em `src/main.c`.

A arvore usada nos exercicios 1 a 5 eh montada com `{50,30,70,20,40,60,80}`,
ficando balanceada:

```txt
            50
          /    \
        30      70
       /  \    /  \
     20   40  60   80
```

## 1) int contaFolhas_ArvBin(ArvBin *raiz)

No folha eh o no que nao tem nenhum filho. A funcao eh recursiva: se a arvore
estiver vazia retorna 0; se o no for folha (esq e dir == NULL) retorna 1; senao
soma as folhas da subarvore esquerda com as da direita. Na arvore de teste
retorna 4 (20, 40, 60 e 80).

```c
int contaFolhas_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 0;
    if(*raiz == NULL)
        return 0;
    if((*raiz)->esq == NULL && (*raiz)->dir == NULL)
        return 1;
    return contaFolhas_ArvBin(&((*raiz)->esq)) + contaFolhas_ArvBin(&((*raiz)->dir));
}
```

## 2) void imprimeRelacoes_ArvBin(ArvBin *raiz)

Imprime cada no dizendo se ele eh RAIZ, PAI (no interno) ou FOLHA e mostrando
quem sao os filhos esquerdo e direito. Usei um auxiliar `imprimeNO` que recebe o
no e um sinal `ehRaiz`, porque so a partir do no nao da pra saber se ele eh a
raiz. Saida no teste:

```txt
50 (RAIZ, filho esq: 30, filho dir: 70)
30 (PAI, filho esq: 20, filho dir: 40)
20 (FOLHA)
40 (FOLHA)
70 (PAI, filho esq: 60, filho dir: 80)
60 (FOLHA)
80 (FOLHA)
```

## 3) int contaValor_ArvBin(ArvBin *raiz, int valor)

Percorre a arvore inteira somando 1 cada vez que encontra o valor procurado.
Como o `insere_ArvBin` do projeto nao aceita valores repetidos, na pratica o
retorno eh sempre 0 ou 1, mas deixei a funcao contando de forma geral (caso
existissem repetidos ela ja contaria certo). No teste, o 40 aparece 1 vez e o
99 aparece 0 vezes.

```c
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
```

## 4) void imprimeFolhasDecrescente_ArvBin(ArvBin *raiz)

Para sair em ordem decrescente faco a varredura ao contrario do em ordem:
direita -> raiz -> esquerda. Numa arvore de busca isso passa pelos valores do
maior para o menor. So imprimo quando o no for folha. Saida no teste:
`80 60 40 20`.

```c
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
```

## 5) int saoIguais_ArvBin(ArvBin *a, ArvBin *b)

Duas arvores sao iguais quando tem a mesma forma E os mesmos valores nas mesmas
posicoes. O auxiliar `iguaisNO` compara os dois nos ao mesmo tempo: se os dois
forem vazios, sao iguais; se so um for vazio, sao diferentes; se os valores
forem diferentes, sao diferentes; senao tem que ser iguais a esquerda e a
direita. No teste, comparando com uma copia retorna 1, e com uma arvore que tem
um valor trocado retorna 0.

```c
int iguaisNO(struct NO* a, struct NO* b){
    if(a == NULL && b == NULL)
        return 1;
    if(a == NULL || b == NULL)
        return 0;
    if(a->info != b->info)
        return 0;
    return iguaisNO(a->esq, b->esq) && iguaisNO(a->dir, b->dir);
}
```

## 6) void eliminaPares_ArvBin(ArvBin *raiz)

Elimina todos os valores pares. Para nao ter que mexer nos ponteiros enquanto
percorro a arvore (o que daria muito problema), fiz mais simples: procuro um
valor par qualquer com `buscaPar_NO` e, se achar, removo ele usando o
`remove_ArvBin` que ja existe no projeto. Repito ate nao sobrar nenhum par.
Assim quem cuida de religar a arvore eh a propria remocao do projeto.

No teste, partindo de `{8,3,10,1,6,14,4,7,13}` (pares: 8,10,6,14,4) sobra so
`1 3 7 13`.

```c
void eliminaPares_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    int valor;
    while(buscaPar_NO(*raiz, &valor))
        remove_ArvBin(raiz, valor);
}
```

## 7) int saoSimilares_ArvBin(ArvBin *a, ArvBin *b)

Similares = mesma distribuicao de nos (mesma forma), sem olhar os valores. Eh o
mesmo do exercicio 5, so que sem a comparacao do `info`: as duas vazias sao
similares; se so uma eh vazia nao sao; senao tem que ser similares a esquerda e
a direita. No teste, a arvore base e a arvore com um valor trocado (mesma forma)
dao similares = 1, e uma arvore de forma diferente da similares = 0.

```c
int similaresNO(struct NO* a, struct NO* b){
    if(a == NULL && b == NULL)
        return 1;
    if(a == NULL || b == NULL)
        return 0;
    return similaresNO(a->esq, b->esq) && similaresNO(a->dir, b->dir);
}
```

## 8) Insercao e impressao das letras

Os elementos sao inseridos na ordem `M, F, S, D, J, P, U, A, E, H, Q, T, W, K`.
O `insere_ArvBin` ja serve para letras: o `char` eh comparado como inteiro (codigo
ASCII), entao a arvore fica ordenada alfabeticamente. Para imprimir as letras
criei as varreduras em char (`%c` no lugar de `%d`). Saidas no teste:

- Pre ordem (mostra a estrutura da insercao): `M F D A E J H K S P Q U T W`
- Em ordem (sai em ordem alfabetica): `A D E F H J K M P Q S T U W`

A arvore montada fica (K fica a direita de H; Q a direita de P; W a direita de U):

```txt
                 M
              /     \
            F         S
          /   \      /  \
        D      J    P    U
       / \    /      \   / \
      A   E  H        Q T   W
              \
               K
```

## 9) Arvore de expressao matematica

**Observacao sobre o enunciado:** o texto escrito fala `(6-3) * (4-1) + 5`, mas
a FIGURA mostra o operador da direita como `+` (4+1), e o proprio enunciado diz
que o resultado eh 20. Conferindo: `(6-3) * (4-1) + 5 = 3*3+5 = 14`, enquanto
`(6-3) * (4+1) + 5 = 3*5+5 = 20`. Ou seja, o `(4-1)` do texto eh um erro de
digitacao; quem da o 20 eh a figura com `+`. Por isso montei a arvore conforme a
figura.

### a) Funcao de insercao que trata numeros e operadores

A insercao da arvore de expressao NAO eh de arvore de busca: a posicao de cada no
depende da ordem da expressao, nao do valor. Recebo a expressao na ordem prefixa
(o operador vem antes dos operandos) e monto recursivamente: se o caractere eh
operador, crio o no e monto a subarvore esquerda e depois a direita; se eh
numero, eh folha. A expressao da figura na ordem prefixa eh `+ * - 6 3 + 4 1 5`.

```c
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
```

Isso monta exatamente a arvore da imagem:

```txt
              +
           /     \
          *        5
        /   \
       -     +
      / \   / \
     6   3 4   1
```

### b) Funcao que calcula o resultado

Recursiva: se o no eh folha, eh um numero (converto o char do digito para inteiro
com `- '0'`). Se eh operador, calculo as duas subarvores e aplico a conta. No
teste o resultado da `20`.

```c
int calculaNO(struct NO* no){
    if(no == NULL)
        return 0;
    if(no->esq == NULL && no->dir == NULL)
        return no->info - '0';
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
```

### c) Impressao nas notacoes infixa, prefixa e posfixa

- **Infixa** (esquerda, raiz, direita): coloquei parenteses em volta de cada
  operacao para deixar clara a ordem das contas. Saida: `(((6 - 3) * (4 + 1)) + 5)`.
- **Prefixa** (raiz, esquerda, direita) = varredura pre ordem em char.
  Saida: `+ * - 6 3 + 4 1 5`.
- **Posfixa** (esquerda, direita, raiz) = varredura pos ordem em char.
  Saida: `6 3 - 4 1 + * 5 +`.

```c
void infixa_ArvBin(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL)
        return;
    struct NO* no = *raiz;
    if(no->esq == NULL && no->dir == NULL){
        printf("%c", no->info);
        return;
    }
    printf("(");
    infixa_ArvBin(&(no->esq));
    printf(" %c ", no->info);
    infixa_ArvBin(&(no->dir));
    printf(")");
}
```
