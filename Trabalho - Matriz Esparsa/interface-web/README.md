# Interface Web - Matriz Esparsa

Esta pasta contem uma interface web separada para visualizar o funcionamento
do programa C de matriz esparsa, sem alterar os arquivos em `src/`.

A interface mostra:

- Painel de estatisticas em tempo real (dimensao, posicoes totais, nao-zeros,
  nos alocados pela formula `m + n + r + 1`)
- Painel de **comparacao de memoria** entre matriz densa e esparsa, com analise
  dinamica de quando a esparsa compensa para a matriz atual
- Diagrama SVG da estrutura interna (lista cruzada com nos-cabeca), atualizado
  dinamicamente conforme voce insere ou remove valores
- **Demo animada do exemplo do Ziviani** com narracao passo a passo do
  algoritmo de insercao: localizar cabecas, percorrer listas, religar ponteiros
- Lista esparsa (apenas coordenadas com valor diferente de zero)
- Saida original do programa C, exatamente como aparece no terminal

## Como executar

Na pasta `interface-web`, rode:

```sh
python3 server.py
```

Depois abra:

```text
http://127.0.0.1:8080
```

A pagina monta as entradas do menu, executa o programa C compilado e mostra a
saida no navegador. Se o codigo em C foi alterado desde a ultima execucao, o
servidor recompila automaticamente.

Evite abrir esta pasta diretamente pelo Live Server ou abrindo o `index.html`
pelo navegador. A interface usa o servidor `server.py` para chamar o programa
em C pela rota `/run`.

## Demo animada

O botao "Carregar exemplo do Ziviani" no painel de controles insere os 6
valores classicos `(0,0,50)`, `(1,0,10)`, `(1,2,20)`, `(3,0,-30)`, `(3,2,-60)`,
`(3,3,5)` um a um, com narracao detalhada de cada passo do algoritmo de
insercao: localizacao das cabecas de linha e coluna, percurso ordenado pelas
listas existentes, identificacao do `antLinha` e `antColuna`, criacao do
novo no e religacao dos ponteiros nas duas listas.

A velocidade da demo pode ser ajustada (Rapida / Normal / Lenta) no painel de
controles.

## Observacao importante

A interface web eh apenas uma visualizacao auxiliar. O **trabalho de fato**
continua sendo o programa em C nos arquivos da pasta `src/`, que continua
funcionando exatamente como esta no terminal:

```sh
gcc -Wall -Wextra src/main.c src/matriz_esparsa.c -o build/trabalho_matriz_esparsa
./build/trabalho_matriz_esparsa
```
