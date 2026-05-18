# Análise Comparativa de Desempenho: Variantes do Quicksort

Este repositório foi desenvolvido com o objetivo de avaliar empiricamente o comportamento de diferentes estratégias de escolha de pivô para o algoritmo de ordenação **Quicksort**. O foco do experimento é observar como otimizações de pior caso mitigam a degradação assintótica para O($n^2$) e mensurar o impacto do custo computacional extra (*overhead*) que essas proteções impõem ao caso médio.

---

## Ambiente de Testes

Para garantir a reprodução e a fidelidade dos benchmarks, todos os testes foram submetidos a condições semelhantes de execução:

1. **Cenário de simulação real (I/O em disco):** para simular uma aplicação do mundo real, todas as 5 variantes principais realizam a leitura de um arquivo de texto de entrada (`.txt`) contendo chaves desordenadas ou ordenadas, realizam a ordenação em memória e gravam o resultado final em um novo arquivo de texto de saída (`.txt`). 
2. **Nível de otimização do compilador:** todos os arquivos de código-fonte foram compilados de forma limpa, **sem otimizações do compilador (`-O0`)**, garantindo que as nuances e instruções brutas de cada lógica algorítmica fossem integralmente preservadas na CPU.
3. **Especificações de hardware:**
   - **Processador:** frequência de operação oscilando dinamicamente entre **4.5 GHz e 4.8 GHz**.
   - **Memória Cache:** **32 MB de cache** de terceiro nível (L3).
   - **Estado do Sistema:** os testes foram executados com o sistema em completo estado de ociosidade, garantindo que nenhum processo paralelo interferisse nos tempos de CPU medidos (testes realizados no WSL). 
---

## Metodologia e conjuntos de dados

Os vetores de teste foram criados utilizando o algoritmo [gera_vetor](./gerador_de_vetores/gerav_vetor.md). Para submeter as variantes a testes de estresse significativos, o benchmark foi estruturado em três dimensões:

* **3 Tamanhos de vetores massivos:** 10 Milhões (`10mi`), 100 Milhões (`100mi`) e 1 Bilhão (`1bi`) de elementos.
* **3 Cenários de distribuição de dados:**
  - **Vetores desordenados:** elementos distribuídos aleatoriamente.
  - **Vetores ordenados crescente:** dados já ordenados de forma ascendente (pior caso teórico para pivôs fixos).
  - **Vetores ordenados decrescente:** dados ordenados de modo invertido.

## Algoritmos e Variantes Avaliadas

O repositório está subdividido em abordagens de manipulação de arquivo e uma variação especial puramente em memória:

1. **`qs_original.c`:** quicksort clássico com escolha cega do pivô na última posição (`A[r]`). 
    - Detalhes: [quicksort classico.](./variantes_quicksort/qs_original.md) 
2. **`qs_mediana3.c`:** implementação com escolha de pivô baseada na mediana entre o início, meio e fim do subvetor.
    - Detalhes: [quicksort mediana de 3.](./variantes_quicksort/qs_mediana3.md) 
3. **`qs_pivo_aleatorio.c`:** abordagem probabilística que sorteia um índice aleatório via `rand()` e o utiliza como pivô.
    - Detalhes: [quicksort pivo aleatorio.](./variantes_quicksort/q_pivo_aleatorio.md) 
4. **`qs_limite100_mediana3.c`:** variante híbrida que faz uma varredura linear para mapear e banir os 100 maiores e 100 menores elementos de serem pivôs, aplicando mediana de 3 sobre o espaço seguro restante.
    - Detalhes: [quicksort limite de 100 mediana de 3.](./variantes_quicksort/qs_limite100_mediana3.md) 
5. **`qs_limite100_pivo_aleatorio.c`:** abordagem híbrida similar à anterior, mas que realiza um sorteio probabilístico validado dentro da zona de segurança (excluindo os 100 maiores e menores).
    - Detalhes: [quicksort limite de 100 pivo aleatorio.](./variantes_quicksort/qs_limite100_pivo_aleatorio.md) 

### Implementação Especial: `qs_simplificado`
diferente das demais variantes, o **`qs_simplificado`** é uma implementação desenvolvida especificamente para demonstração. Ele **não realiza a leitura ou escrita em arquivos de texto externos**. A sua lógica central consiste apenas em procurar o maior e o menor valor do arranjo e estabelecer uma proteção direta, que ele não permite que esses dois extremos absolutos sejam eleitos como pivô, além de selecionar aleatoriamente um pivô.

## Resultados dos benchmarks

Abaixo estão dispostas as tabelas de benchmarks de tempo (em segundos) extraídas para cada um dos cenários.

### 1. Cenário: Vetores Desordenados (Aleatórios)
<table border="1" style="border-collapse: collapse; text-align: center; width: 100%;">
  <thead>
    <tr style="background-color: #2c3e50; color: white;">
      <th style="padding: 10px;">Tamanho</th>
      <th style="padding: 10px;">qs_original</th>
      <th style="padding: 10px;">qs_mediana3</th>
      <th style="padding: 10px;">qs_pivo_aleatorio</th>
      <th style="padding: 10px;">qs_limite100_mediana3</th>
      <th style="padding: 10px;">qs_limite100_pivo_aleatorio</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="padding: 8px;"><b>10mi</b></td>
      <td style="padding: 8px;">1.817523</td>
      <td style="padding: 8px;">1.796448</td>
      <td style="padding: 8px;">1.821947</td>
      <td style="padding: 8px;">3.010620</td>
      <td style="padding: 8px;">3.091447</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><b>100mi</b></td>
      <td style="padding: 8px;">18.948404</td>
      <td style="padding: 8px;">19.405822</td>
      <td style="padding: 8px;">19.018934</td>
      <td style="padding: 8px;">31.165486</td>
      <td style="padding: 8px;">31.613507</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><b>1bi</b></td>
      <td style="padding: 8px;">188.519294</td>
      <td style="padding: 8px;">190.535368</td>
      <td style="padding: 8px;">195.234093</td>
      <td style="padding: 8px;">320.545594</td>
      <td style="padding: 8px;">324.920485</td>
    </tr>
  </tbody>
</table>

### 2. Cenário: Vetores Ordenados Crescente
<table border="1" style="border-collapse: collapse; text-align: center; width: 100%;">
  <thead>
    <tr style="background-color: #2c3e50; color: white;">
      <th style="padding: 10px;">Tamanho</th>
      <th style="padding: 10px;">qs_original</th>
      <th style="padding: 10px;">qs_mediana3</th>
      <th style="padding: 10px;">qs_pivo_aleatorio</th>
      <th style="padding: 10px;">qs_limite100_mediana3</th>
      <th style="padding: 10px;">qs_limite100_pivo_aleatorio</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="padding: 8px;"><b>10mi</b></td>
      <td style="padding: 8px; color: red;">~ 5,9 horas</td>
      <td style="padding: 8px;">1.216785</td>
      <td style="padding: 8px;">1.327225</td>
      <td style="padding: 8px;">8.808110</td>
      <td style="padding: 8px;">3.068592</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><b>100mi</b></td>
      <td style="padding: 8px; color: red;">~ 24,7 dias</td>
      <td style="padding: 8px;">12.898493</td>
      <td style="padding: 8px;">13.650596</td>
      <td style="padding: 8px;">107.806807</td>
      <td style="padding: 8px;">104.312112</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><b>1bi</b></td>
      <td style="padding: 8px; color: red;">~ 6,7 anos</td>
      <td style="padding: 8px;">125.660830</td>
      <td style="padding: 8px;">139.787241</td>
      <td style="padding: 8px;">1284.086133</td>
      <td style="padding: 8px;">1104.275539</td>
    </tr>
  </tbody>
</table>

### 3. Cenário: Vetores Ordenados Decrescente
<table border="1" style="border-collapse: collapse; text-align: center; width: 100%;">
  <thead>
    <tr style="background-color: #2c3e50; color: white;">
      <th style="padding: 10px;">Tamanho</th>
      <th style="padding: 10px;">qs_original</th>
      <th style="padding: 10px;">qs_mediana3</th>
      <th style="padding: 10px;">qs_pivo_aleatorio</th>
      <th style="padding: 10px;">qs_limite100_mediana3</th>
      <th style="padding: 10px;">qs_limite100_pivo_aleatorio</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="padding: 8px;"><b>10mi</b></td>
      <td style="padding: 8px; color: red;">~ 5,9 horas</td>
      <td style="padding: 8px;">1.315829</td>
      <td style="padding: 8px;">1.322947</td>
      <td style="padding: 8px;">5.270731</td>
      <td style="padding: 8px;">5.839460</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><b>100mi</b></td>
      <td style="padding: 8px; color: red;">~ 24,7 dias</td>
      <td style="padding: 8px;">19.085570</td>
      <td style="padding: 8px;">19.054682</td>
      <td style="padding: 8px;">31.123076</td>
      <td style="padding: 8px;">31.716685</td>
    </tr>
    <tr>
      <td style="padding: 8px;"><b>1bi</b></td>
      <td style="padding: 8px; color: red;">~ 6,7 anos</td>
      <td style="padding: 8px;">128.134831</td>
      <td style="padding: 8px;">141.315888</td>
      <td style="padding: 8px;">716.131236</td>
      <td style="padding: 8px;">783.835544</td>
    </tr>
  </tbody>
</table>

> *Nota: todas as estimativas com "~" foram previsões calculadas, e não, testadas. Testes paralelos mostraram que o algoritmo demora mais de 213 segundos para tentar ordenar um vetor ordenado crescente de apenas 1 milhão de posições, algo que ultrapassa todas as outras métricas com algoritmos ordenando 100 milhões, ou seja, o pior caso do quicksort é extremamente custoso, computacionalmente falando.*

## Principais Conclusões do Experimento

1. **O Colapso do Quicksort Clássico (`qs_original`):** conforme previsto pela teoria, a escolha do último elemento como pivô gera partições degeneradas em vetores pré-ordenados. Sem qualquer otimização sintética do compilador para mascarar o problema, a profundidade excessiva da pilha recursiva resulta num colapso absoluto.
2. **O Equilíbrio da Mediana de 3:** revelou-se a melhor estratégia de uso prático, pois ordenou rapidamente o caso médio e lidou bem com cenários de vetores ordenados.
3. **O Custo Oculto da Blindagem de Limites:** embora as variantes com isolamento de `100 extremos` sejam blindagens matematicamente absolutas e infalíveis contra a complexidade O($n^2$), elas cobram um pedágio computacional (*overhead*) extremamente alto em cenários médios devido às movimentações contínuas de memória para mapear os piores índices.
