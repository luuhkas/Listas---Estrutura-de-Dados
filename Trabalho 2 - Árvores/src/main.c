#include <stdio.h>
#include <string.h>
#include "arvore.h"

/* Separa a linha digitada em comando + argumento.
 * O argumento e tudo que vem depois do primeiro espaco (pode conter
 * espacos, como em "cd Meus Documentos").                                */
static void separarComando(char *linha, char **comando, char **arg)
{
    linha[strcspn(linha, "\r\n")] = '\0';

    *comando = linha;
    char *espaco = strchr(linha, ' ');

    if (espaco == NULL)
    {
        *arg = linha + strlen(linha); /* aponta para "" */
        return;
    }

    *espaco = '\0';
    *arg = espaco + 1;

    while (**arg == ' ') /* pula espacos extras antes do argumento */
        (*arg)++;
}

/* Tenta carregar o in.txt em alguns locais comuns, para o programa funcionar
 * tanto rodando de dentro de src/ quanto da pasta do projeto ou pelo "Run" da
 * IDE (que usa a raiz do workspace como diretorio atual). Tambem aceita o
 * caminho como argumento: ./trabalho_arvores <caminho/in.txt>                */
static int carregarEntrada(No *raiz, Trie *indice, int argc, char **argv)
{
    if (argc > 1)
        return lerArquivo(raiz, indice, argv[1]);

    const char *candidatos[] = {
        "in.txt",
        "src/in.txt",
        "../src/in.txt",
        "Trabalho 2 - Árvores/src/in.txt"};

    for (size_t i = 0; i < sizeof(candidatos) / sizeof(candidatos[0]); i++)
    {
        if (lerArquivo(raiz, indice, candidatos[i]))
        {
            printf("Entrada carregada de: %s\n", candidatos[i]);
            return 1;
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    No *raiz = criarRaiz();
    Trie *indice = criarTrie();

    if (!carregarEntrada(raiz, indice, argc, argv))
        printf("Aviso: 'in.txt' nao encontrado. Iniciando com a arvore vazia.\n");

    No *atual = raiz;
    char linha[1024];
    char caminho[4096];

    printf("Simulador de diretorios (Trabalho 2 - Arvores).\n");
    printf("Digite 'help' para ver os comandos.\n");

    while (1)
    {
        obterCaminho(atual, caminho);
        printf("\n%s> ", caminho);

        if (fgets(linha, sizeof(linha), stdin) == NULL) /* Ctrl+D encerra */
            break;

        char *comando;
        char *arg;
        separarComando(linha, &comando, &arg);

        if (comando[0] == '\0')
            continue;

        if (strcmp(comando, "cd") == 0)
            atual = comandoCd(raiz, atual, arg);
        else if (strcmp(comando, "search") == 0)
            comandoSearch(indice, arg);
        else if (strcmp(comando, "rm") == 0)
            atual = comandoRm(atual, indice, arg);
        else if (strcmp(comando, "list") == 0)
            comandoList(atual);
        else if (strcmp(comando, "mkdir") == 0)
            comandoMkdir(atual, indice, arg);
        else if (strcmp(comando, "mem") == 0)
            medirMemoria(raiz, indice);
        else if (strcmp(comando, "clear") == 0)
            comandoClear();
        else if (strcmp(comando, "help") == 0)
            comandoHelp();
        else if (strcmp(comando, "exit") == 0)
            break;
        else
            printf("Comando desconhecido: '%s'. Digite 'help'.\n", comando);
    }

    /* exit: libera todo o espaco alocado antes de encerrar. */
    liberarArvore(raiz);
    liberarTrie(indice);
    printf("Memoria liberada. Ate mais!\n");

    return 0;
}
