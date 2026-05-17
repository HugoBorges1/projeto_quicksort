# Quicksort com pivô aleatório (`qs_pivo_aleatorio.c`)

Este algoritmo implementa uma abordagem **probabilística** que busca resolver o pior caso ($O(N^2)$) em vetores ordenados. Em vez de depender de posições fixas ou calcular medianas exatas, este algoritmo confia na aleatoriedade matemática para evitar gargalos assintóticos.

O objetivo do Quicksort Randomizado é **quebrar qualquer padrão existente nos dados de entrada**, escolhendo o pivô de forma totalmente imprevisível. Assim, a chance de o algoritmo sortear o pior elemento consecutivamente em milhões de chamadas recursivas torna-se estatisticamente quase nula.

## Como o algoritmo funciona

A cada chamada recursiva, antes de iniciar a separação dos dados, o algoritmo executa três passos simples na função `randomized_partition`:

### 1. Sorteio do índice
Em vez de focar nas extremidades ou no meio, o algoritmo utiliza o gerador de números randômicos nativo da linguagem C (`rand()`) para sortear um índice qualquer dentro dos limites do subvetor atual (entre `p` e `r`).

### 2. Troca estratégica (Swap)
Uma vez que o índice aleatório foi sorteado, o algoritmo pega o valor contido nessa posição e troca de lugar com o último elemento do subvetor (`A[r]`). 

### 3. Posicionamento do pivô
Após colocar o elemento sorteado na última posição de forma segura, a função chama o `partition` tradicional. Como a função clássica foi programada para usar sempre o último elemento como pivô, ela estará, na verdade, operando sobre o elemento aleatório, dividindo o vetor com a lógica original inalterada e otimizada.

## Análise de performance

Abaixo estão os tempos de execução (em segundos) do algoritmo Quicksort com pivô aleatório para os diferentes cenários e tamanhos de vetores calculados:

<table border="1" style="border-collapse: collapse; text-align: center; width: 100%;">
  <thead>
    <tr>
      <th style="padding: 8px;">Tamanho do Vetor</th>
      <th style="padding: 8px;">Vetores Desordenados</th>
      <th style="padding: 8px;">Ordenados Crescente</th>
      <th style="padding: 8px;">Ordenados Decrescente</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="padding: 8px;"><b>10mi</b></td>
      <td style="padding: 8px;">1.821947</td>
      <td style="padding: 8px;">1.327225</td>
      <td style="padding: 8px;">1.322947</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><b>100mi</b></td>
      <td style="padding: 8px;">19.018934</td>
      <td style="padding: 8px;">13.650596</td>
      <td style="padding: 8px;">19.054682</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><b>1bi</b></td>
      <td style="padding: 8px;">195.234093</td>
      <td style="padding: 8px;">139.787241</td>
      <td style="padding: 8px;">141.315888</td>
    </tr>
  </tbody>
</table>
