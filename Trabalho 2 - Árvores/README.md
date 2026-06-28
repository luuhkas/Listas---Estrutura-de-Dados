# Trabalho 2 — Árvore de Diretórios

Simulador de linha de comando que monta uma **árvore genérica de diretório** a
partir de um arquivo `in.txt` e permite navegar/manipular pastas e arquivos.

Disciplina: Algoritmos e Estrutura de Dados III — UTFPR Santa Helena.

## Estrutura do projeto

```
Trabalho 2 - Árvores/
├── src/
│   ├── arvore.h    # estruturas e declarações
│   ├── arvore.c    # implementação
│   ├── main.c      # laço da linha de comando
│   └── in.txt      # entrada (lista de pastas/arquivos)
├── build/          # executável gerado
├── README.md
└── DOCUMENTO.md    # documento do trabalho (estruturas, métodos, desafios)
```

## Como compilar e executar

A partir da pasta `src/` (o programa lê `in.txt` do diretório atual):

```sh
cd src
gcc -Wall -Wextra -std=c11 -o ../build/trabalho_arvores main.c arvore.c
../build/trabalho_arvores
```

## Comandos

| Comando | Descrição |
|---|---|
| `cd <dir>` | Entra na pasta. `cd ..` sobe, `cd /` vai à raiz. Sugere nomes por prefixo se não achar. |
| `search <nome>` | Procura pasta/arquivo pelo índice (Trie) e mostra o caminho. |
| `rm <nome>` | Remove pasta/arquivo da pasta atual (liberação recursiva). |
| `list` | Lista o conteúdo da pasta atual (`/` marca subpastas). |
| `mkdir <nome>` | Cria uma pasta na pasta atual. |
| `mem` | Comparativo de memória filho-irmão × vetor fixo (extra). |
| `clear` | Limpa a tela. |
| `help` | Mostra a ajuda. |
| `exit` | Libera a memória e encerra. |

## Formato do `in.txt`

Uma entrada por linha; `/` separa os níveis; arquivos têm extensão.

```
Meus Documentos/fontes/main.c
Meus Downloads/t2.rar
```

## Destaques

- **Árvore genérica filho-irmão** (3 ponteiros por nó) — ver `DOCUMENTO.md`.
- **Índice Trie** para busca rápida por nome e por prefixo.
- **Comparativo de memória** (`mem`) e ausência de vazamentos (verificado com `leaks`).
