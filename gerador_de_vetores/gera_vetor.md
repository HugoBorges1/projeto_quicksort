# Gerador de vetores (`gera_vetor.c`)

O **gerador de vetores** é um algoritmo utilizado para criar arquivos `.txt` contendo valores determinados pelo usuário, servindo como um gerador de dados para testar as variadas implementações do quicksort apresentadas nesse experimento. É capaz de gerar arquivos com N quantidade de valores (até 1 bilhão), ordenados de forma crescente, decrescente ou aleatória.

## Como o algoritmo funciona

O programa opera em três etapas simples:

### 1. Entrada do Usuário
Ao ser executado, o programa interage com o usuário via terminal para coletar três informações cruciais:
* **Quantidade (N):** o número total de elementos que o vetor terá (ex: 10000000 para 10 milhões).
* **Caminho do Arquivo:** onde o arquivo será salvo e qual será o seu nome (ex: `vetores_teste/vetor_10mi.txt`).
* **Tipo de Distribuição:** a forma como os números estarão organizados (Crescente, Decrescente ou Aleatório).

### 2. A lógica de distribuição 
Dependendo da opção escolhida, o laço de repetição (`for`) adota uma matemática diferente para gerar os números:

* **Opção 1 (Crescente):** `numero = i;`
  Gera uma sequência perfeita de `0` até `N-1`. 

* **Opção 2 (Decrescente):** `numero = N - i;`
  Gera uma sequência invertida (do maior para o menor).
  
* **Opção 3 (Desordenado/Aleatório):** `numero = rand() % 1000000001;`
  Gera números aleatórios entre 0 e 1 Bilhão. (O algoritmo usa `srand(time(NULL))` para garantir que a semente de aleatoriedade seja diferente a cada segundo).

### 3. Escrita em arquivo
O programa grava os números no disco utilizando a quebra de linha (`\n`) como separador:
```c
fprintf(arquivo, "%d\n", numero);