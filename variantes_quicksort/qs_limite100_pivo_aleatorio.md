# Quicksort Híbrido com Limite de 100 Extremos + Pivô Aleatório (`qs_limite100_pivo_aleatorio.c`)

Este algoritmo implementa uma blindagem de segurança agressiva contra o pior caso do Quicksort (complexidade O($n^2$)). A estratégia consiste em mapear e isolar os maiores e menores elementos de um subvetor, criando uma "zona segura" no meio dos dados. O pivô final é então escolhido através de um **sorteio aleatório** exclusivo dentro dessa zona permitida.

O propósito desta implementação é garantir que o pivô selecionado para o particionamento nunca seja um elemento de extremo valor (os 100 maiores ou os 100 menores). Ao garantir que o pivô seja aleatório, mas obrigatoriamente intermediário, o algoritmo força divisões estruturalmente saudáveis e elimina matematicamente a vulnerabilidade do pior caso, mesmo em vetores inteiramente ordenados.

## Como o algoritmo funciona

A cada chamada recursiva, o algoritmo segue um rigoroso processo de filtragem e sorteio:

### 1. Verificação de escala (Tamanho do Subvetor)
Antes de iniciar a busca por extremos, o programa avalia o tamanho do subvetor atual ($n\_elem \le 200$). 
Se o subvetor possuir 200 elementos ou menos, é impossível isolar os 100 maiores e os 100 menores e ainda ter opções de pivô. Nesses casos, a varredura pesada é desativada e o algoritmo recorre a um **Pivô Aleatório Simples** (`rand() % n_elem`), garantindo velocidade na resolução de pequenos blocos.

### 2. O mapeamento dos 200 extremos
Para partições maiores que 200 elementos, o algoritmo realiza uma busca linear completa pelo subvetor. Durante essa varredura, ele atualiza constantemente dois históricos de tamanho fixo na memória:
* `idx_menores[100]`: Armazena os índices das 100 menores chaves numéricas encontradas até o momento.
* `idx_maiores[100]`: Armazena os índices das 100 maiores chaves numéricas encontradas até o momento.

Sempre que um novo valor "quebra" o limite dessas listas, ele é inserido ordenadamente, garantindo que, ao final do laço, as "pontas" absolutas do vetor estejam perfeitamente mapeadas.

### 3. A roleta da zona segura (Sorteio com Validação)
Com os extremos isolados, o programa inicia um laço de repetição (`do-while`) para definir o pivô:
1. A função `rand()` sorteia um índice qualquer pertencente ao subvetor atual.
2. O algoritmo faz uma checagem rápida para ver se esse índice sorteado pertence à "lista negra" (ou seja, se ele é um dos 100 maiores ou 100 menores).
3. Se o índice pertencer aos extremos, o sorteio é rejeitado e a roleta gira novamente.
4. Se o índice estiver limpo (na zona segura), o laço é encerrado, e esse índice é oficializado como o pivô da rodada.

O elemento escolhido troca de posição com o último elemento (`A[r]`), e a função tradicional de `partition` assume o trabalho de separação.

## Análise de performance

Abaixo estão os tempos de execução (em segundos) do algoritmo Quicksort Híbrido (Limite 100 + Aleatório) para os diferentes cenários e tamanhos de vetores calculados:

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
      <td style="padding: 8px;">3.091447</td>
      <td style="padding: 8px;">3.068592</td>
      <td style="padding: 8px;">5.839460</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><b>100mi</b></td>
      <td style="padding: 8px;">31.613507</td>
      <td style="padding: 8px;">104.312112</td>
      <td style="padding: 8px;">31.716685</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><b>1bi</b></td>
      <td style="padding: 8px;">324.920485</td>
      <td style="padding: 8px;">1104.275539</td>
      <td style="padding: 8px;">783.835544</td>
    </tr>
  </tbody>
</table>
