#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int N;
    char nome_arquivo[256];
    FILE *arquivo;
    int opcao;

    printf("Digite a quantidade de numeros (N) a serem gerados: ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Quantidade invalida. O programa sera encerrado.\n");
        return 1;
    }

    printf("Digite o nome ou caminho do arquivo (ex: arquivos_numeros/vetor.txt): ");

    if (scanf("%255s", nome_arquivo) != 1) {
        printf("Nome de arquivo invalido. O programa sera encerrado.\n");
        return 1;
    }

    printf("\nEscolha como gerar os %d numeros:\n", N);
    printf("1 - Ordenado Crescente\n");
    printf("2 - Ordenado Decrescente\n");
    printf("3 - Desordenado (Aleatorio)\n");
    printf("Digite a opcao (1, 2 ou 3): ");
    
    if (scanf("%d", &opcao) != 1 || (opcao < 1 || opcao > 3)) {
        printf("Opcao invalida. O programa sera encerrado.\n");
        return 1;
    }

    arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("\nErro ao criar o arquivo '%s'.\n", nome_arquivo);
        printf("Dica: Se voce digitou uma pasta no nome (ex: pasta/arquivo.txt), certifique-se de que a pasta existe!\n");
        return 1;
    }

    srand(time(NULL));
    printf("\nGerando arquivo '%s', aguarde...\n", nome_arquivo);

    for (int i = 0; i < N; i++) {
        int numero;

        if (opcao == 1) {
            numero = i;
        } else if (opcao == 2) {
            numero = N - i;
        } else {
            numero = rand() % 1000000001; 
        }

        fprintf(arquivo, "%d\n", numero);
    }

    fclose(arquivo);
    printf("Sucesso! Arquivo gerado.\n");
    return 0;
}