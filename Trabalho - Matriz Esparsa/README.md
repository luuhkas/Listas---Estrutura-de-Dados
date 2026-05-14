# Trabalho - Matriz Esparsa

Projeto em C que implementa uma matriz esparsa usando lista cruzada com nos-cabeca.

A matriz armazena apenas os valores diferentes de zero. Cada valor armazenado eh
um no que pertence a duas listas circulares ao mesmo tempo: a lista da linha
(ligada pelo ponteiro `direita`) e a lista da coluna (ligada pelo ponteiro `abaixo`).

A estrutura usada eh a representacao classica de matriz esparsa descrita por
Nivio Ziviani no livro *Projeto de Algoritmos com Implementacoes em Pascal e C*.

## Estrutura

- `src/`: codigo do trabalho.
- `build/`: executaveis gerados localmente.
- `DOCUMENTO.md`: explicacao dos metodos criados e dos desafios.

## Como compilar

Use:

```sh
gcc -Wall -Wextra src/main.c src/matriz_esparsa.c -o build/trabalho_matriz_esparsa
```

Depois execute:

```sh
./build/trabalho_matriz_esparsa
```

O programa principal abre um menu no terminal para criar a matriz, inserir valor,
remover valor, consultar posicao, buscar valor, imprimir vizinhos, imprimir a matriz
completa e imprimir a forma esparsa com apenas as coordenadas armazenadas.

## Como testar

Use:

```sh
gcc -Wall -Wextra src/testes.c src/matriz_esparsa.c -o build/testes_matriz_esparsa
./build/testes_matriz_esparsa
```
