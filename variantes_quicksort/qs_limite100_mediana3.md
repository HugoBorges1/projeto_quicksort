# Quicksort Híbrido com Limite de 100 Extremos + Mediana de 3 (`qs_limite100_mediana3.c`)

Esta variação representa uma técnica aplicada ao Quicksort para evitar a todo custo seu pior caso. O algoritmo combina uma estratégia rigorosa de **isolamento dos valores extremos** com a técnica de **Mediana de 3** para criar uma proteção absoluta contra o pior caso computacional ($O(N^2)$).

Para anular o pior caso de forma definitiva em subvetores massivos, este algoritmo estabelece uma "zona proibida" composta pelos **100 maiores** e pelos **100 menores** elementos do subvetor sob análise. O pivô final é extraído exclusivamente da zona de segurança intermediária restante.

## Como o algoritmo funciona

O fluxo lógico de execução divide-se em quatro fases principais a cada chamada recursiva:

### 1. Verificação de escala de elementos
Antes de aplicar a lógica pesada de filtragem, o algoritmo analisa a dimensão do problema atual ($n\_elem = r - p + 1$):
* **Menos ou igual a 200 elementos ($2 \times k$):** é matematicamente impossível isolar 100 elementos de cada lado e ainda restar candidatos. Nesses cenários pequenos, o algoritmo desativa automaticamente a varredura linear e utiliza a **Mediana de 3 Clássica** para garantir uma resolução rápida e sem custos extras de processamento.
* **Mais de 200 elementos:** a lógica híbrida de proteção entra em ação.

### 2. Mapeamento linear dos 100 extremos
O algoritmo percorre todo o subvetor de `p` até `r`. À medida que varre os elementos, ele mantém dois históricos ordenados atualizados em tempo real dentro da memória cache (usando vetores estáticos de tamanho fixo para evitar alocação dinâmica lenta):
* `idx_menores[100]`: armazena os índices das 100 menores chaves numéricas encontradas até o momento.
* `idx_maiores[100]`: armazena os índices das 100 maiores chaves numéricas encontradas até o momento.

Sempre que uma nova chave supera o limite de corte dessas listas, ela é inserida na sua posição correta via *Insertion Sort* interno, empurrando o elemento menos extremo para fora do histórico.

### 3. Sorteio controlado na zona segura
Com as tabelas de exclusão preenchidas, o programa inicia um sorteio aleatório usando a função `rand()`. O algoritmo sorteia um índice e faz uma busca linear nas listas proibidas:
* Se o índice sorteado for o dono de um dos 100 menores ou 100 maiores valores, o sorteio é sumariamente **rejeitado**.
* O processo repete-se em loop até que **3 índices seguros e distintos** sejam validados.

### 4. Refinamento por mediana de 3
Para garantir a melhor divisão possível do espaço de busca, o algoritmo coleta os valores contidos nesses 3 índices seguros e calcula a **mediana entre eles**. O índice vencedor é eleito o pivô definitivo, trocado de lugar com a última posição (`A[r]`) e entregue à função `partition`.

## Análise de performance

Abaixo estão os tempos de execução (em segundos) do algoritmo Quicksort com os 200 extremos e mediana de 3 para os diferentes cenários e tamanhos de vetores calculados:

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
      <td style="padding: 8px;">3.010620</td>
      <td style="padding: 8px;">8.808110</td>
      <td style="padding: 8px;">5.270731</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><b>100mi</b></td>
      <td style="padding: 8px;">31.165486</td>
      <td style="padding: 8px;">107.806807</td>
      <td style="padding: 8px;">31.123076</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><b>1bi</b></td>
      <td style="padding: 8px;">320.545594</td>
      <td style="padding: 8px;">1284.086133</td>
      <td style="padding: 8px;">716.131236</td>
    </tr>
  </tbody>
</table>