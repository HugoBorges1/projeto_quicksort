# Quicksort com mediana de 3 (`qs_mediana3.c`)

Este algoritmo implementa a técnica da **Mediana de 3** que busca resolver o caso ($O(N^2)$) em vetores ordenados sem sacrificar a velocidade de execução.

A técnica da Mediana de 3 tem como único objetivo **garantir que o pivô nunca seja o maior nem o menor elemento do subvetor**, escolhendo um elemento intermediário com um custo computacional constante.

## Como o algoritmo funciona

A cada chamada recursiva, antes de iniciar a separação dos dados, o algoritmo executa três passos cirúrgicos na função `partition_mediana`:

### 1. Seleção dos três pontos
Em vez de olhar para o vetor inteiro, o algoritmo "olha" apenas para três posições estratégicas:
* O primeiro elemento (`A[p]`)
* O elemento do meio (`A[mid]`)
* O último elemento (`A[r]`)

### 2. Ordenação local
O programa faz no máximo 3 comparações simples (`if`) para ordenar apenas esses três elementos entre si. 
Após essas três trocas (`swap`), garantimos matematicamente que:
* O menor dos três fica no início (`A[p]`).
* O maior dos três fica no final (`A[r]`).
* O valor intermediário fica no meio (`A[mid]`).

### 3. Posicionamento do pivô
Sabendo que o elemento em `A[mid]` é a mediana perfeita entre as pontas, o algoritmo o elege como o pivô da rodada. Ele então troca o valor do meio com a última posição (`A[r]`) para que a função `partition` original possa executar o seu trabalho normalmente, dividindo o vetor de forma equilibrada.

## Análise de performance

Abaixo estão os tempos de execução (em segundos) do algoritmo Quicksort com Mediana de 3 para os diferentes cenários e tamanhos de vetores calculados:

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
      <td style="padding: 8px;">1.796448</td>
      <td style="padding: 8px;">1.216785</td>
      <td style="padding: 8px;">1.315829</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><b>100mi</b></td>
      <td style="padding: 8px;">19.405822</td>
      <td style="padding: 8px;">12.898493</td>
      <td style="padding: 8px;">19.085570</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><b>1bi</b></td>
      <td style="padding: 8px;">190.535368</td>
      <td style="padding: 8px;">125.660830</td>
      <td style="padding: 8px;">128.134831</td>
    </tr>
  </tbody>
</table>
