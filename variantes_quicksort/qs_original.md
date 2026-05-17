# Quicksort "Original" (`qs_original.c`)

Esta é a implementação tradicional do algoritmo Quicksort, escrita exatamente como descrita em grande parte da literatura académica clássica (como o famoso livro *Introduction to Algorithms* de Thomas H. Cormen). Ele serve como ponto de partida nesse experimento.

O objetivo deste algoritmo é demonstrar a eficiência do particionamento lógico em cenários comuns, mas também expor, na prática, o grande "problema" do Quicksort, que é sua vulnerabilidade a dados pré-ordenados, que aciona o pior caso de complexidade O($n^2$).

## Como o algoritmo funciona

A lógica do Quicksort Clássico baseia-se na simplicidade. Sem sorteios complexos ou cálculos de medianas, a cada chamada recursiva, o algoritmo segue os seguintes passos na função `partition`:

### 1. A escolha cega do pivô
O algoritmo confia que o **último elemento** do subvetor será um bom divisor. Ele atribui diretamente o valor de `A[r]` à variável pivô `x`:
```c
int x = A[r];
```

### 2. O particionamento
O programa percorre o subvetor com um laço de repetição (`for`). Toda vez que encontra um número menor ou igual ao pivô, ele o "joga" para o lado esquerdo através de uma troca de posições (`swap`). Ao final do laço, os números menores estão à esquerda, os maiores à direita, e o pivô é colocado exatamente no centro (a sua posição final e definitiva).

### 3. A divisão e conquista (Recursão)
Com o pivô no lugar, o algoritmo "quebra" o vetor em dois subvetores menores (um à esquerda do pivô e outro à direita) e chama a si mesmo repetidas vezes até que todos os números estejam ordenados.

## Análise de performance

A escolha do último elemento como pivô é extremamente rápida e funciona maravilhosamente bem se os dados estiverem misturados (aleatórios). No entanto, ela esconde uma armadilha fatal se o vetor já estiver ordenado.

Abaixo estão os tempos de execução (em segundos) extraídos dos testes:

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
      <td style="padding: 8px;">1.817523 s</td>
      <td style="padding: 8px;">~ 5,9 horas</td>
      <td style="padding: 8px;">~ 5,9 horas</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><b>100mi</b></td>
      <td style="padding: 8px;">18.948404 s</td>
      <td style="padding: 8px;">~ 24,7 dias</td>
      <td style="padding: 8px;">~ 24,7 dias</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><b>1bi</b></td>
      <td style="padding: 8px;">188.519294 s</td>
      <td style="padding: 8px;">~ 6,7 anos</td>
      <td style="padding: 8px;">~ 6,7 anos</td>
    </tr>
  </tbody>
</table>

> *Nota: Todas as estimativas com "~" foram previsões calculadas, e não, testadas. Testes paralelos mostraram que o algoritmo demora mais de 213 segundos para tentar ordenar um vetor ordenado crescente de apenas 1 milhão de posições, algo que ultrapassa todas as outras métricas com algoritmos ordenando 100 milhões, ou seja, o pior caso do quicksort é extremamente custoso, computacionalmente falando.*

Em dados desordenados, o Quicksort Original é excelente, processando 1 bilhão de números em cerca de 3 minutos. No entanto, quando testado com vetores Crescentes ou Decrescentes, a falha estrutural se expõe, ao escolher o último elemento de um vetor ordenado, o pivô é sempre o maior (ou menor) de todos. Isso gera uma divisão inútil onde um lado fica vazio e o outro fica gigante, forçando a CPU a executar trilhões de operações redundantes, provando a necessidade de implementar variações que tratam esse pior caso (Mediana de 3, Pivô Aleatório, etc.).
