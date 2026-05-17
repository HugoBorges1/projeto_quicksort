# Quicksort: Clássico / Original (`qs_original.c`)

Esta é a implementação tradicional do algoritmo Quicksort, escrita exatamente como descrita em grande parte da literatura acadêmica clássica (como o famoso livro *Introduction to Algorithms* de Thomas H. Cormen). Ele serve como o nosso "ponto de partida" e grupo de controle neste laboratório.

## 🎯 Objetivo
O objetivo deste algoritmo é demonstrar a eficiência brutal do particionamento lógico em cenários comuns, mas também expor, na prática, o famoso "Calcanhar de Aquiles" do Quicksort: a sua vulnerabilidade a dados pré-ordenados, que aciona o trágico pior caso de complexidade $O(N^2)$.

## ⚙️ Como o Algoritmo Funciona

A lógica do Quicksort Clássico baseia-se na simplicidade. Sem sorteios complexos ou cálculos de medianas, a cada chamada recursiva, o algoritmo segue os seguintes passos na função `partition`:

### 1. A Escolha Cega do Pivô
O algoritmo confia cegamente que o **último elemento** do subvetor será um bom divisor de águas. Ele atribui diretamente o valor de `A[r]` à variável pivô `x`:
```c
int x = A[r];
2. O Particionamento (Separação)
O programa percorre o subvetor com um laço de repetição (for). Toda vez que encontra um número menor ou igual ao pivô, ele o "joga" para o lado esquerdo através de uma troca de posições (swap). Ao final do laço, os números menores estão à esquerda, os maiores à direita, e o pivô é colocado exatamente no centro (a sua posição final e definitiva).

3. A Divisão e Conquista (Recursão)
Com o pivô no lugar, o algoritmo "quebra" o vetor em dois subvetores menores (um à esquerda do pivô e outro à direita) e chama a si mesmo repetidas vezes até que todos os números estejam ordenados.

📈 Análise de Performance e Benchmark (O Problema do Pior Caso)
A escolha do último elemento como pivô é extremamente rápida e funciona maravilhosamente bem se os dados estiverem misturados (aleatórios). No entanto, ela esconde uma armadilha fatal se o vetor já estiver ordenado.

Em nossos testes de estresse, os resultados revelaram as duas faces deste algoritmo:

Vetor Desordenado (Aleatório) - 1 Bilhão de elementos: ~188 segundos.

Vetor Ordenado / Decrescente - 1 Milhão de elementos: > 213 segundos (Estouro).

Conclusão dos Tempos: Em dados caóticos, o Quicksort Original é uma máquina formidável, processando 1 bilhão de números em cerca de 3 minutos. No entanto, quando testado com vetores Crescentes ou Decrescentes, a falha estrutural foi exposta: ao escolher o último elemento de um vetor ordenado, o pivô é sempre o maior (ou menor) de todos. Isso gera uma divisão inútil onde um lado fica vazio e o outro fica gigante, forçando a CPU a executar trilhões de operações redundantes. O teste falhou massivamente já na marca de 1 milhão de elementos, provando a necessidade de criarmos as variações (Mediana de 3, Pivô Aleatório, etc.).

🚀 Compilação e Execução
Para garantir o máximo de desempenho na leitura do arquivo dinâmico e na recursão, utilize a flag de otimização de nível 3 (-O3).

Compilação via Terminal
Usando o Clang:

Bash
clang qs_original.c -o qs_original -Wall -O3
Usando o GCC:

Bash
gcc qs_original.c -o qs_original -Wall -O3
Execução Passando Parâmetros
O programa foi projetado para receber dois argumentos obrigatórios via terminal: o arquivo fonte (.txt) para leitura e o arquivo de destino onde os números ordenados serão gravados.

Exemplo prático:

Bash
./qs_original arquivos_numeros/vetor_aleatorio_10mi.txt vetores_ordenados/saida_original_10mi.txt
⚠️ Alerta de Laboratório: Evite testar o executável qs_original com vetores Crescentes ou Decrescentes maiores que 10 milhões de elementos. A falha do O(N²) causará um esgotamento da pilha de chamadas (Stack Overflow) e o seu sistema operacional poderá matar o processo (Segmentation Fault), ou o seu computador travará operando a 100% de CPU por dias ininterruptos!