#include <stdio.h>
#include "matriz_esparsa.h"

int main(void)
{
    MatrizEsparsa *matriz = NULL;
    MatrizEsparsa *novaMatriz;
    Node *resultado;
    int opcao;
    int linhas;
    int colunas;
    int linha;
    int coluna;
    int valor;
    int executando = 1;

    while (executando)
    {
        printf("\n===== Matriz Esparsa =====\n");
        printf("1 - Criar matriz\n");
        printf("2 - Inserir valor\n");
        printf("3 - Remover valor\n");
        printf("4 - Consultar posicao\n");
        printf("5 - Buscar valor\n");
        printf("6 - Imprimir vizinhos\n");
        printf("7 - Imprimir matriz\n");
        printf("8 - Imprimir forma esparsa\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1)
        {
            printf("Entrada invalida.\n");
            return 1;
        }

        switch (opcao)
        {
        case 1:
            printf("Quantidade de linhas: ");
            if (scanf("%d", &linhas) != 1)
            {
                printf("Entrada invalida.\n");
                executando = 0;
                break;
            }

            printf("Quantidade de colunas: ");
            if (scanf("%d", &colunas) != 1)
            {
                printf("Entrada invalida.\n");
                executando = 0;
                break;
            }

            novaMatriz = criarMatriz(linhas, colunas);

            if (novaMatriz == NULL)
                printf("Nao foi possivel criar a matriz. Use dimensoes maiores que zero.\n");
            else
            {
                desalocarMatriz(matriz);
                matriz = novaMatriz;
                printf("Matriz esparsa %dx%d criada com sucesso.\n", linhas, colunas);
                imprimirMatriz(matriz);
            }
            break;

        case 2:
            if (matriz == NULL)
            {
                printf("Crie uma matriz primeiro.\n");
                break;
            }

            printf("Linha: ");
            if (scanf("%d", &linha) != 1)
            {
                printf("Entrada invalida.\n");
                executando = 0;
                break;
            }

            printf("Coluna: ");
            if (scanf("%d", &coluna) != 1)
            {
                printf("Entrada invalida.\n");
                executando = 0;
                break;
            }

            printf("Valor: ");
            if (scanf("%d", &valor) != 1)
            {
                printf("Entrada invalida.\n");
                executando = 0;
                break;
            }

            if (inserirValor(matriz, linha, coluna, valor))
            {
                if (valor == 0)
                    printf("Valor zero em (%d,%d): posicao removida da estrutura esparsa.\n", linha, coluna);
                else
                    printf("Valor %d inserido na posicao (%d,%d).\n", valor, linha, coluna);
                imprimirMatriz(matriz);
            }
            else
                printf("Nao foi possivel inserir em (%d,%d). Verifique os limites da matriz.\n", linha, coluna);
            break;

        case 3:
            if (matriz == NULL)
            {
                printf("Crie uma matriz primeiro.\n");
                break;
            }

            printf("Linha: ");
            if (scanf("%d", &linha) != 1)
            {
                printf("Entrada invalida.\n");
                executando = 0;
                break;
            }

            printf("Coluna: ");
            if (scanf("%d", &coluna) != 1)
            {
                printf("Entrada invalida.\n");
                executando = 0;
                break;
            }

            if (removerValor(matriz, linha, coluna))
            {
                printf("Posicao (%d,%d) removida da estrutura esparsa.\n", linha, coluna);
                imprimirMatriz(matriz);
            }
            else
                printf("Posicao (%d,%d) nao possui valor armazenado.\n", linha, coluna);
            break;

        case 4:
            if (matriz == NULL)
            {
                printf("Crie uma matriz primeiro.\n");
                break;
            }

            printf("Linha: ");
            if (scanf("%d", &linha) != 1)
            {
                printf("Entrada invalida.\n");
                executando = 0;
                break;
            }

            printf("Coluna: ");
            if (scanf("%d", &coluna) != 1)
            {
                printf("Entrada invalida.\n");
                executando = 0;
                break;
            }

            resultado = consultarPosicao(matriz, linha, coluna);

            if (resultado == NULL)
            {
                if (linha < 0 || coluna < 0 || linha >= matriz->linhas || coluna >= matriz->colunas)
                    printf("Posicao (%d,%d) invalida.\n", linha, coluna);
                else
                    printf("Posicao (%d,%d) nao possui valor armazenado (vale 0).\n", linha, coluna);
            }
            else
                printf("Posicao (%d,%d) possui valor %d.\n", linha, coluna, resultado->valor);
            break;

        case 5:
            if (matriz == NULL)
            {
                printf("Crie uma matriz primeiro.\n");
                break;
            }

            printf("Valor para buscar: ");
            if (scanf("%d", &valor) != 1)
            {
                printf("Entrada invalida.\n");
                executando = 0;
                break;
            }

            if (valor == 0)
            {
                printf("Zero nao e armazenado na matriz esparsa.\n");
                break;
            }

            resultado = buscarValor(matriz, valor);

            if (resultado == NULL)
                printf("Valor %d nao encontrado.\n", valor);
            else
                printf("Valor %d encontrado na posicao (%d,%d).\n", valor, resultado->linha, resultado->coluna);
            break;

        case 6:
            if (matriz == NULL)
            {
                printf("Crie uma matriz primeiro.\n");
                break;
            }

            printf("Linha: ");
            if (scanf("%d", &linha) != 1)
            {
                printf("Entrada invalida.\n");
                executando = 0;
                break;
            }

            printf("Coluna: ");
            if (scanf("%d", &coluna) != 1)
            {
                printf("Entrada invalida.\n");
                executando = 0;
                break;
            }

            imprimirVizinhos(matriz, linha, coluna);
            break;

        case 7:
            if (matriz == NULL)
                printf("Crie uma matriz primeiro.\n");
            else
                imprimirMatriz(matriz);
            break;

        case 8:
            if (matriz == NULL)
                printf("Crie uma matriz primeiro.\n");
            else
                imprimirEsparsa(matriz);
            break;

        case 0:
            executando = 0;
            break;

        default:
            printf("Opcao invalida.\n");
            break;
        }
    }

    desalocarMatriz(matriz);
    printf("Programa finalizado.\n");

    return 0;
}