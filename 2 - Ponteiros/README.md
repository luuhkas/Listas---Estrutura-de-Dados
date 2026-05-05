# Ponteiros

Ponteiro eh uma variavel que guarda um endereco de memoria.

Em vez de guardar diretamente um valor, ele guarda onde esse valor esta.

Exemplo:

```c
int x = 10;
int *p = &x;
```

Nesse caso:

- `x` guarda o valor `10`;
- `&x` eh o endereco de `x`;
- `p` guarda esse endereco;
- `*p` acessa o valor que esta nesse endereco.

## Operadores importantes

- `&`: pega o endereco de uma variavel.
- `*`: acessa o conteudo apontado por um ponteiro.

Exemplo:

```c
printf("%d", *p);
```

Isso imprime o valor de `x`, porque `p` aponta para `x`.

## Por que ponteiros importam

Ponteiros sao usados para:

- alterar valores dentro de funcoes;
- trabalhar com vetores e strings;
- alocar memoria dinamicamente;
- criar estruturas como listas, pilhas e filas.

## Cuidados

- Ponteiro sem inicializar pode apontar para lixo de memoria.
- Depois de `free`, o ponteiro nao deve ser usado sem receber outro endereco valido.
- Antes de acessar `*p`, confira se `p != NULL`.

## Neste diretorio

Os exercicios praticam passagem por referencia, manipulacao de memoria e uso de ponteiros para entender melhor como C trabalha por baixo.

