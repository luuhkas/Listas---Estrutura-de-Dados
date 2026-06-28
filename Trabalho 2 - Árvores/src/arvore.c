#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

/* ======================================================================= */
/* Criacao e construcao da arvore                                          */
/* ======================================================================= */

No *criarNo(const char *nome, TipoNo tipo)
{
    No *no = malloc(sizeof(No));

    if (no == NULL)
        return NULL;

    strncpy(no->nome, nome, MAX_NOME - 1);
    no->nome[MAX_NOME - 1] = '\0';
    no->tipo = tipo;
    no->pai = NULL;
    no->primeiroFilho = NULL;
    no->proxIrmao = NULL;

    return no;
}

No *criarRaiz(void)
{
    /* A raiz e uma pasta especial; seu nome "/" so aparece no prompt. */
    return criarNo("/", PASTA);
}

void adicionarFilho(No *pai, No *filho)
{
    filho->pai = pai;

    /* Insere no fim da lista de irmaos para preservar a ordem de entrada. */
    if (pai->primeiroFilho == NULL)
    {
        pai->primeiroFilho = filho;
        return;
    }

    No *atual = pai->primeiroFilho;
    while (atual->proxIrmao != NULL)
        atual = atual->proxIrmao;

    atual->proxIrmao = filho;
}

No *buscarFilho(No *pasta, const char *nome)
{
    No *filho = pasta->primeiroFilho;

    while (filho != NULL)
    {
        if (strcmp(filho->nome, nome) == 0)
            return filho;
        filho = filho->proxIrmao;
    }

    return NULL;
}

/* Decide o tipo de um segmento do caminho.
 * O enunciado garante que arquivo sempre tem extensao, logo um segmento
 * que contem '.' e tratado como arquivo; caso contrario e pasta.         */
static TipoNo tipoDoSegmento(const char *segmento)
{
    return (strchr(segmento, '.') != NULL) ? ARQUIVO : PASTA;
}

/* Insere um caminho completo (linha do in.txt) na arvore, criando os nos
 * intermediarios que ainda nao existirem. Cada no criado entra no indice. */
static void inserirCaminho(No *raiz, Trie *indice, char *caminho)
{
    No *atual = raiz;
    char *segmento = strtok(caminho, "/");

    while (segmento != NULL)
    {
        char *proximo = strtok(NULL, "/");

        /* Apenas o ultimo segmento pode ser arquivo; os do meio sao pastas. */
        TipoNo tipo = (proximo == NULL) ? tipoDoSegmento(segmento) : PASTA;

        No *filho = buscarFilho(atual, segmento);
        if (filho == NULL)
        {
            filho = criarNo(segmento, tipo);
            adicionarFilho(atual, filho);
            trieInserir(indice, filho->nome, filho);
        }

        atual = filho;
        segmento = proximo;
    }
}

int lerArquivo(No *raiz, Trie *indice, const char *caminhoArquivo)
{
    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL)
        return 0;

    char linha[1024];
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        /* Remove o '\n' (ou '\r\n') do fim da linha. */
        linha[strcspn(linha, "\r\n")] = '\0';

        if (linha[0] == '\0')
            continue;

        inserirCaminho(raiz, indice, linha);
    }

    fclose(arquivo);
    return 1;
}

/* ======================================================================= */
/* Indice (Trie)                                                           */
/* ======================================================================= */

static TrieNo *criarTrieNo(void)
{
    /* calloc deixa todos os filhos em NULL e ocorrencias em NULL. */
    return calloc(1, sizeof(TrieNo));
}

Trie *criarTrie(void)
{
    Trie *indice = malloc(sizeof(Trie));
    if (indice == NULL)
        return NULL;

    indice->raiz = criarTrieNo();
    return indice;
}

/* Desce na trie seguindo os bytes de "chave", criando nos pelo caminho. */
static TrieNo *descerCriando(Trie *indice, const char *chave)
{
    TrieNo *no = indice->raiz;

    for (int i = 0; chave[i] != '\0'; i++)
    {
        unsigned char c = (unsigned char) chave[i];
        if (no->filhos[c] == NULL)
            no->filhos[c] = criarTrieNo();
        no = no->filhos[c];
    }

    return no;
}

/* Desce na trie sem criar; retorna NULL se o caminho nao existir. */
static TrieNo *descer(Trie *indice, const char *chave)
{
    TrieNo *no = indice->raiz;

    for (int i = 0; chave[i] != '\0'; i++)
    {
        unsigned char c = (unsigned char) chave[i];
        if (no->filhos[c] == NULL)
            return NULL;
        no = no->filhos[c];
    }

    return no;
}

void trieInserir(Trie *indice, const char *nome, No *no)
{
    TrieNo *folha = descerCriando(indice, nome);

    OcorrenciaNo *oc = malloc(sizeof(OcorrenciaNo));
    oc->no = no;
    oc->prox = folha->ocorrencias;
    folha->ocorrencias = oc;
}

void trieRemoverOcorrencia(Trie *indice, const char *nome, No *no)
{
    TrieNo *folha = descer(indice, nome);
    if (folha == NULL)
        return;

    OcorrenciaNo *atual = folha->ocorrencias;
    OcorrenciaNo *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->no == no)
        {
            if (anterior == NULL)
                folha->ocorrencias = atual->prox;
            else
                anterior->prox = atual->prox;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

OcorrenciaNo *trieBuscar(Trie *indice, const char *nome)
{
    TrieNo *folha = descer(indice, nome);
    return (folha != NULL) ? folha->ocorrencias : NULL;
}

/* Visita recursivamente toda a subarvore da trie a partir de "no",
 * imprimindo a localizacao de cada ocorrencia encontrada. Usada para a
 * busca por prefixo. Retorna quantas ocorrencias foram impressas.        */
static int imprimirOcorrenciasSubarvore(TrieNo *no)
{
    if (no == NULL)
        return 0;

    int total = 0;
    char caminho[4096];

    OcorrenciaNo *oc = no->ocorrencias;
    while (oc != NULL)
    {
        obterCaminho(oc->no, caminho);
        printf("  [%s] %s\n", (oc->no->tipo == PASTA) ? "pasta" : "arquivo", caminho);
        total++;
        oc = oc->prox;
    }

    for (int c = 0; c < ALFABETO; c++)
        total += imprimirOcorrenciasSubarvore(no->filhos[c]);

    return total;
}

/* ======================================================================= */
/* Utilitarios                                                             */
/* ======================================================================= */

void obterCaminho(No *no, char *out)
{
    /* A raiz nao tem pai e representa "/". */
    if (no->pai == NULL)
    {
        strcpy(out, "/");
        return;
    }

    /* Empilha os ancestrais (sem a raiz) e imprime de cima para baixo. */
    No *pilha[MAX_NOME];
    int n = 0;
    No *p = no;

    while (p->pai != NULL)
    {
        pilha[n++] = p;
        p = p->pai;
    }

    out[0] = '\0';
    for (int i = n - 1; i >= 0; i--)
    {
        strcat(out, "/");
        strcat(out, pilha[i]->nome);
    }
}

/* ======================================================================= */
/* Comandos                                                                */
/* ======================================================================= */

No *comandoCd(No *raiz, No *atual, const char *arg)
{
    if (arg[0] == '\0')
    {
        printf("Uso: cd <diretorio>\n");
        return atual;
    }

    if (strcmp(arg, ".") == 0)
        return atual;

    if (strcmp(arg, "/") == 0)
        return raiz;

    if (strcmp(arg, "..") == 0)
        return (atual->pai != NULL) ? atual->pai : atual;

    No *alvo = buscarFilho(atual, arg);
    if (alvo != NULL)
    {
        if (alvo->tipo == PASTA)
            return alvo;

        printf("'%s' e um arquivo, nao um diretorio.\n", arg);
        return atual;
    }

    /* Nao existe: oferece as pastas-filho cujo nome comeca com "arg". */
    size_t prefixoLen = strlen(arg);
    int achou = 0;

    for (No *filho = atual->primeiroFilho; filho != NULL; filho = filho->proxIrmao)
    {
        if (filho->tipo == PASTA && strncmp(filho->nome, arg, prefixoLen) == 0)
        {
            if (!achou)
                printf("Diretorio '%s' nao encontrado. Voce quis dizer:\n", arg);
            printf("  %s\n", filho->nome);
            achou = 1;
        }
    }

    if (!achou)
        printf("Diretorio nao encontrado.\n");

    return atual;
}

void comandoSearch(Trie *indice, const char *arg)
{
    if (arg[0] == '\0')
    {
        printf("Uso: search <nome>\n");
        return;
    }

    /* 1) Tenta casamento exato pelo indice (O(tamanho do nome)). */
    OcorrenciaNo *oc = trieBuscar(indice, arg);
    if (oc != NULL)
    {
        char caminho[4096];
        printf("Encontrado:\n");
        while (oc != NULL)
        {
            obterCaminho(oc->no, caminho);
            printf("  [%s] %s\n", (oc->no->tipo == PASTA) ? "pasta" : "arquivo", caminho);
            oc = oc->prox;
        }
        return;
    }

    /* 2) Sem exato: usa a busca por prefixo da trie como sugestao. */
    TrieNo *no = descer(indice, arg);
    if (no != NULL)
    {
        printf("Nenhum resultado exato. Comecam com '%s':\n", arg);
        if (imprimirOcorrenciasSubarvore(no) > 0)
            return;
    }

    printf("Nada encontrado para '%s'.\n", arg);
}

/* Remove "no" da lista de filhos do seu pai (desencadeia da lista de irmaos). */
static void desligarDoPai(No *no)
{
    No *pai = no->pai;
    if (pai == NULL)
        return;

    if (pai->primeiroFilho == no)
    {
        pai->primeiroFilho = no->proxIrmao;
        return;
    }

    No *anterior = pai->primeiroFilho;
    while (anterior != NULL && anterior->proxIrmao != no)
        anterior = anterior->proxIrmao;

    if (anterior != NULL)
        anterior->proxIrmao = no->proxIrmao;
}

/* Libera recursivamente uma subarvore, tirando cada no do indice antes. */
static void liberarSubarvore(No *no, Trie *indice)
{
    No *filho = no->primeiroFilho;
    while (filho != NULL)
    {
        No *prox = filho->proxIrmao;
        liberarSubarvore(filho, indice);
        filho = prox;
    }

    trieRemoverOcorrencia(indice, no->nome, no);
    free(no);
}

No *comandoRm(No *atual, Trie *indice, const char *arg)
{
    if (arg[0] == '\0')
    {
        printf("Uso: rm <nome>\n");
        return atual;
    }

    No *alvo = buscarFilho(atual, arg);
    if (alvo == NULL)
    {
        printf("'%s' nao existe nesta pasta.\n", arg);
        return atual;
    }

    desligarDoPai(alvo);
    liberarSubarvore(alvo, indice);
    printf("'%s' removido.\n", arg);
    return atual;
}

void comandoList(No *atual)
{
    if (atual->primeiroFilho == NULL)
    {
        printf("(pasta vazia)\n");
        return;
    }

    for (No *filho = atual->primeiroFilho; filho != NULL; filho = filho->proxIrmao)
    {
        if (filho->tipo == PASTA)
            printf("  %s/\n", filho->nome);
        else
            printf("  %s\n", filho->nome);
    }
}

void comandoMkdir(No *atual, Trie *indice, const char *arg)
{
    if (arg[0] == '\0')
    {
        printf("Uso: mkdir <nome>\n");
        return;
    }

    if (buscarFilho(atual, arg) != NULL)
    {
        printf("Ja existe '%s' nesta pasta.\n", arg);
        return;
    }

    No *nova = criarNo(arg, PASTA);
    adicionarFilho(atual, nova);
    trieInserir(indice, nova->nome, nova);
    printf("Pasta '%s' criada.\n", arg);
}

void comandoClear(void)
{
    /* Escolhe o comando conforme o sistema operacional (Windows usa "cls",
     * os demais usam "clear"). Se a chamada falhar, imprime varias linhas
     * em branco como alternativa, conforme previsto no enunciado.          */
#ifdef _WIN32
    int resultado = system("cls");
#else
    int resultado = system("clear");
#endif
    if (resultado != 0)
    {
        for (int i = 0; i < 50; i++)
            printf("\n");
    }
}

void comandoHelp(void)
{
    printf("\nComandos disponiveis:\n");
    printf("  cd <dir>      Entra em uma pasta. 'cd ..' sobe, 'cd /' vai a raiz.\n");
    printf("                Se a pasta nao existir, sugere nomes que comecam igual.\n");
    printf("  search <nome> Procura uma pasta/arquivo (pelo indice) e mostra o caminho.\n");
    printf("  rm <nome>     Remove uma pasta/arquivo da pasta atual (liberacao recursiva).\n");
    printf("  list          Lista o conteudo da pasta atual ('/' marca subpastas).\n");
    printf("  mkdir <nome>  Cria uma pasta na pasta atual.\n");
    printf("  mem           Mostra o comparativo de memoria filho-irmao x vetor fixo.\n");
    printf("  clear         Limpa a tela.\n");
    printf("  help          Mostra esta ajuda.\n");
    printf("  exit          Libera a memoria e encerra o programa.\n\n");
}

/* ======================================================================= */
/* Comparativo de memoria (ponto extra)                                    */
/* ======================================================================= */

static int contarNos(No *no)
{
    if (no == NULL)
        return 0;

    int total = 1;
    for (No *filho = no->primeiroFilho; filho != NULL; filho = filho->proxIrmao)
        total += contarNos(filho);

    return total;
}

static int contarTrieNos(TrieNo *no)
{
    if (no == NULL)
        return 0;

    int total = 1;
    for (int c = 0; c < ALFABETO; c++)
        total += contarTrieNos(no->filhos[c]);

    return total;
}

void medirMemoria(No *raiz, Trie *indice)
{
    int nos = contarNos(raiz);

    /* (1) Parte que a ESCOLHA de representacao controla: o gerenciamento
     *     dos filhos. Filho-irmao usa 2 ponteiros (primeiroFilho/proxIrmao);
     *     o vetor fixo usaria GRAU_MAX ponteiros + 1 contador.            */
    size_t gerenciaFilhoIrmao = 2 * sizeof(No *);
    size_t gerenciaVetorFixo = GRAU_MAX * sizeof(No *) + sizeof(int);

    /* (2) Struct completa por no. O nome[MAX_NOME] e o ponteiro de pai sao
     *     iguais nas duas, entao a diferenca acima fica "diluida" no total. */
    size_t structFilhoIrmao = sizeof(No);
    size_t structVetorFixo = sizeof(No) - gerenciaFilhoIrmao + gerenciaVetorFixo;

    int trieNos = contarTrieNos(indice->raiz);
    size_t bytesTrie = (size_t) trieNos * sizeof(TrieNo);

    printf("\n===== Comparativo de memoria =====\n");
    printf("Nos na arvore: %d   (sizeof(No) = %zu, nome[%d] domina o tamanho)\n\n",
           nos, sizeof(No), MAX_NOME);

    printf("Parte controlada pela representacao (gerenciamento de filhos):\n");
    printf("  %-26s %5zu bytes/no\n", "filho-irmao (2 ponteiros):", gerenciaFilhoIrmao);
    printf("  %-26s %5zu bytes/no   (~%.0fx mais)\n", "vetor fixo (GRAU_MAX=50):",
           gerenciaVetorFixo, (double) gerenciaVetorFixo / (double) gerenciaFilhoIrmao);

    printf("\nStruct completa por no (inclui nome[256] + pai, iguais nas duas):\n");
    printf("  %-26s %5zu bytes/no   -> total %8zu bytes\n", "filho-irmao:",
           structFilhoIrmao, nos * structFilhoIrmao);
    printf("  %-26s %5zu bytes/no   -> total %8zu bytes   (~%.1fx)\n", "vetor fixo:",
           structVetorFixo, nos * structVetorFixo,
           (double) structVetorFixo / (double) structFilhoIrmao);
    printf("  -> o ganho real existe e cresce com GRAU_MAX, mas o nome fixo o dilui.\n");

    printf("\nCusto do indice (Trie): %d nos x %zu bytes = %zu bytes.\n",
           trieNos, sizeof(TrieNo), bytesTrie);
    printf("(indice troca memoria por velocidade: search O(|nome|) x varredura O(N);\n");
    printf(" a Patricia, Ziviani 5.4.2, comprime esses nos de passagem.)\n\n");
}

/* ======================================================================= */
/* Liberacao                                                               */
/* ======================================================================= */

void liberarArvore(No *no)
{
    if (no == NULL)
        return;

    No *filho = no->primeiroFilho;
    while (filho != NULL)
    {
        No *prox = filho->proxIrmao;
        liberarArvore(filho);
        filho = prox;
    }

    free(no);
}

static void liberarTrieNo(TrieNo *no)
{
    if (no == NULL)
        return;

    OcorrenciaNo *oc = no->ocorrencias;
    while (oc != NULL)
    {
        OcorrenciaNo *prox = oc->prox;
        free(oc);
        oc = prox;
    }

    for (int c = 0; c < ALFABETO; c++)
        liberarTrieNo(no->filhos[c]);

    free(no);
}

void liberarTrie(Trie *indice)
{
    if (indice == NULL)
        return;

    liberarTrieNo(indice->raiz);
    free(indice);
}
