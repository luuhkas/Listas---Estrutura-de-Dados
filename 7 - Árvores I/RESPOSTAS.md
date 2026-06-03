# Lista 7 - Arvores I

Todos os exercicios foram feitos sobre o projeto `ProjArvoreBinaria` do professor,
como pede o enunciado. As funcoes que faltavam foram implementadas em
`base/ArvoreBinaria.c` e os testes ficam em `src/main.c`.

A arvore usada nos testes eh montada com os valores `{50,100,30,20,40,45,35,37}`,
ficando assim:

```txt
           50
          /  \
        30    100
       /  \
     20    40
          /  \
        35    45
          \
           37
```

## 1) Como operam insere_ArvBin e remove_ArvBin

**insere_ArvBin(ArvBin* raiz, int valor)**

Insere mantendo a propriedade de arvore binaria de busca. Cria um no novo e,
se a arvore estiver vazia, ele vira a raiz. Caso contrario, percorre a arvore a
partir da raiz comparando o valor: se for maior que o no atual vai para a
direita, se for menor vai para a esquerda, ate chegar em um ponto vazio (NULL).
Guarda sempre o no anterior (`ant`) para saber onde pendurar o no novo. Se o
valor ja existir na arvore, ele libera o no criado e nao insere (nao aceita
valores repetidos). Retorna 1 se inseriu e 0 se nao inseriu.

**remove_ArvBin(ArvBin *raiz, int valor)**

Procura o valor descendo na arvore pela mesma regra (maior vai para a direita,
menor vai para a esquerda), guardando o no anterior. Quando encontra o no, chama
`remove_atual` para tirar esse no e religar a arvore, tratando se o no eh a raiz
ou um filho da esquerda/direita do anterior. Retorna 1 se removeu e 0 se o valor
nao estava na arvore.

A remocao tem tres casos, resolvidos dentro de `remove_atual` (ver exercicio 5):
no sem filho a esquerda, e no com os dois filhos (usa o maior valor da subarvore
esquerda como substituto).

## 2) preOrdem_ArvBin e as varreduras EM ordem e POS ordem

**preOrdem_ArvBin (PRE ordem)** visita primeiro a raiz, depois a subarvore
esquerda e depois a direita (raiz -> esq -> dir). Saida no teste:
`50 30 20 40 35 37 45 100`.

Com base nela escrevi as outras duas varreduras, mudando so a posicao do
`printf` da raiz:

**emOrdem_ArvBin (EM ordem)**: esquerda -> raiz -> direita. Em uma arvore de
busca, sai em ordem crescente. Saida: `20 30 35 37 40 45 50 100`.

```c
void emOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvBin(&((*raiz)->esq));
        printf("%d\n",(*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}
```

**posOrdem_ArvBin (POS ordem)**: esquerda -> direita -> raiz. Visita os dois
filhos antes da raiz. Saida: `20 37 35 45 40 30 100 50`.

```c
void posOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%d\n",(*raiz)->info);
    }
}
```

## 3) int totalNO_ArvBin(ArvBin *raiz)

Funcao recursiva que conta os nos. Se a arvore (ou subarvore) estiver vazia
retorna 0. Senao, o total eh a quantidade de nos da subarvore esquerda mais a da
direita mais 1 (o proprio no). No teste retorna 8.

```c
int totalNO_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 0;
    if(*raiz == NULL)
        return 0;
    int total_esq = totalNO_ArvBin(&((*raiz)->esq));
    int total_dir = totalNO_ArvBin(&((*raiz)->dir));
    return (total_esq + total_dir + 1);
}
```

## 4) int Cons_Arvore / consulta_ArvBin(ArvBin *raiz, int valor)

Consulta se um valor existe. Aproveita a propriedade da arvore de busca: comeca
na raiz e, enquanto o no nao for NULL, compara o valor. Se for igual retorna 1
(existe), se for maior vai para a direita e se for menor vai para a esquerda. Se
chegar em NULL sem achar, retorna 0. No teste, consulta 45 retorna 1 e consulta
99 retorna 0.

```c
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
```

## 5) struct NO* Remove_ArvoreAtual / remove_atual(struct NO* atual)

Essa funcao recebe um no e o remove, devolvendo o no que deve ficar no lugar
dele. No projeto ela ja vem pronta com o nome `remove_atual` (declarada no header
e usada por `remove_ArvBin`), entao ela atende o exercicio 5. Como ela funciona:

- Se o no nao tem filho a esquerda, basta devolver o filho da direita no lugar
  dele (e liberar o no). Isso cobre o caso de no folha (devolve NULL) e de no com
  so um filho a direita.
- Se tem filho a esquerda, ela procura o maior valor da subarvore esquerda (vai
  o mais a direita possivel a partir do filho esquerdo). Esse no vira o
  substituto: ela religa os ponteiros para que o substituto assuma o lugar do no
  removido, mantendo a arvore de busca valida, e libera o no original.

```c
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
    if(no1 != atual){
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}
```

No teste, ao remover o 50 (a raiz), ele eh substituido pelo 45 (maior valor da
subarvore esquerda) e a arvore continua correta, como mostra a varredura EM
ordem depois da remocao.
