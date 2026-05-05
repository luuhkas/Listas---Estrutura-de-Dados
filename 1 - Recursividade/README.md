# Recursividade

Recursividade acontece quando uma funcao chama ela mesma para resolver uma parte menor do mesmo problema.

A ideia principal eh dividir o problema ate chegar em um caso simples, que a funcao consegue resolver sem chamar ela mesma de novo.

## Como pensar

Toda funcao recursiva precisa de duas partes:

- caso base: condicao que para a recursao;
- chamada recursiva: a funcao chamando ela mesma com um problema menor.

Exemplo simples:

```c
int fatorial(int n)
{
    if (n == 0)
        return 1;

    return n * fatorial(n - 1);
}
```

Nesse exemplo, o caso base eh `n == 0`. Sem ele, a funcao chamaria ela mesma para sempre.

## Cuidados

- Sempre defina bem o caso base.
- A chamada recursiva precisa chegar mais perto do caso base.
- Recursao usa a pilha de chamadas do programa, entao problemas muito grandes podem estourar memoria.
- Muitas solucoes recursivas tambem podem ser feitas com `for` ou `while`.

## Neste diretorio

Os exercicios treinam chamadas recursivas, casos base, retorno de valores e problemas que podem ser quebrados em partes menores.

