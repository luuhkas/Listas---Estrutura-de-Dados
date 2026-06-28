#pragma once

/*
 * Trabalho 2 - Arvores (AEDS III)
 * Arvore generica de diretorio para simular uma linha de comando.
 *
 * Estrutura central (a "arvore generica" pedida no enunciado):
 *   Representacao FILHO-IRMAO (primeiro filho / proximo irmao).
 *   Cada no tem apenas 3 ponteiros, independente de quantos filhos:
 *     - pai            : sobe na arvore (cd .., monta o caminho)
 *     - primeiroFilho  : aponta para o primeiro filho da pasta
 *     - proxIrmao      : aponta para o proximo filho do mesmo pai
 *   Referencia: Ziviani, Projeto de Algoritmos (representacao de arvores);
 *               CLRS sec. 10.4, "Representing rooted trees".
 *
 * Indice de busca (ponto extra sugerido pelo professor):
 *   TRIE (arvore digital) que mapeia  nome -> lista de nos com aquele nome.
 *   Torna o "search" O(tamanho do nome) em vez de O(N) varrendo a arvore,
 *   e da suporte a busca por prefixo.
 *   Referencia: Ziviani, Projeto de Algoritmos, sec. 5.4 (Trie / Patricia).
 */

#define MAX_NOME 256 /* tamanho maximo do nome de uma pasta/arquivo  */
#define ALFABETO 256 /* trie sobre o alfabeto de bytes (aceita espaco/acento) */
#define GRAU_MAX 50  /* grau usado SO na comparacao de memoria (vetor fixo)  */

/* Um no pode ser uma pasta ou um arquivo (arquivo = tem extensao). */
typedef enum
{
    PASTA,
    ARQUIVO
} TipoNo;

/* No da arvore generica na representacao filho-irmao. */
typedef struct No
{
    char nome[MAX_NOME];
    TipoNo tipo;
    struct No *pai;
    struct No *primeiroFilho;
    struct No *proxIrmao;
} No;

/* Lista de ocorrencias guardada na folha da trie (nomes podem repetir). */
typedef struct OcorrenciaNo
{
    No *no;
    struct OcorrenciaNo *prox;
} OcorrenciaNo;

/* No da trie: um filho por byte possivel + lista de nos que terminam aqui. */
typedef struct TrieNo
{
    struct TrieNo *filhos[ALFABETO];
    OcorrenciaNo *ocorrencias;
} TrieNo;

/* Encapsula a raiz da trie para passar o indice como um objeto so. */
typedef struct Trie
{
    TrieNo *raiz;
} Trie;

/* ----------------------------------------------------------------------- */
/* Criacao e construcao da arvore                                          */
/* ----------------------------------------------------------------------- */

/* Cria o no raiz da arvore (pasta especial de nome "/"). */
No *criarRaiz(void);

/* Aloca e inicializa um no solto (ainda sem pai). */
No *criarNo(const char *nome, TipoNo tipo);

/* Liga "filho" no fim da lista de filhos de "pai" (preserva a ordem de entrada). */
void adicionarFilho(No *pai, No *filho);

/* Procura um filho direto de "pasta" pelo nome. Retorna NULL se nao achar. */
No *buscarFilho(No *pasta, const char *nome);

/* Le o arquivo in.txt e monta a arvore, registrando cada no no indice.
 * Retorna 1 em caso de sucesso, 0 se nao conseguiu abrir o arquivo.       */
int lerArquivo(No *raiz, Trie *indice, const char *caminhoArquivo);

/* ----------------------------------------------------------------------- */
/* Indice (Trie)                                                           */
/* ----------------------------------------------------------------------- */

Trie *criarTrie(void);
void trieInserir(Trie *indice, const char *nome, No *no);
void trieRemoverOcorrencia(Trie *indice, const char *nome, No *no);
OcorrenciaNo *trieBuscar(Trie *indice, const char *nome); /* lista exata ou NULL */

/* ----------------------------------------------------------------------- */
/* Comandos da linha de comando                                            */
/* ----------------------------------------------------------------------- */

No *comandoCd(No *raiz, No *atual, const char *arg);          /* retorna novo diretorio atual */
void comandoSearch(Trie *indice, const char *arg);
No *comandoRm(No *atual, Trie *indice, const char *arg);      /* retorna diretorio atual (pode mudar) */
void comandoList(No *atual);
void comandoMkdir(No *atual, Trie *indice, const char *arg);
void comandoClear(void);
void comandoHelp(void);

/* ----------------------------------------------------------------------- */
/* Utilitarios                                                             */
/* ----------------------------------------------------------------------- */

/* Monta em "out" o caminho completo de um no (ex.: /Meus Documentos/fontes). */
void obterCaminho(No *no, char *out);

/* Comparativo de memoria: filho-irmao x vetor fixo de filhos (ponto extra). */
void medirMemoria(No *raiz, Trie *indice);

/* Liberacao recursiva de toda a arvore (usada no exit). */
void liberarArvore(No *no);

/* Libera toda a trie. */
void liberarTrie(Trie *indice);
