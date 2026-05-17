#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int A[], int p, int r) {
    int x = A[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i = i + 1;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[r]);
    return i + 1;
}

int partition_mediana(int A[], int p, int r) {
    int mid = p + (r - p) / 2;

    if (A[p] > A[mid]) swap(&A[p], &A[mid]);
    if (A[p] > A[r])   swap(&A[p], &A[r]);
    if (A[mid] > A[r]) swap(&A[mid], &A[r]);
    
    swap(&A[mid], &A[r]);

    return partition(A, p, r);
}

void quicksort(int A[], int p, int r) {
    if (p < r) {

        int q = partition_mediana(A, p, r);
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, r);
    }
}

int main(int argc, char *argv[]) {
    clock_t inicio_tempo = clock();

    if (argc != 3) {
        printf("Uso correto: %s <arquivo_entrada> <arquivo_saida>\n", argv[0]);
        return 1;
    }

    char *nome_arquivo_entrada = argv[1];
    char *nome_arquivo_saida = argv[2];

    FILE *f_entrada = fopen(nome_arquivo_entrada, "r");
    if (f_entrada == NULL) {
        printf("Erro: nao foi possivel abrir o arquivo de entrada '%s'.\n", nome_arquivo_entrada);
        return 1;
    }

    int capacidade = 100000; 
    int n = 0;               
    int *vetor = (int *)malloc(capacidade * sizeof(int));
    
    if (vetor == NULL) {
        printf("Erro ao alocar memoria inicial\n");
        fclose(f_entrada);
        return 1;
    }

    printf("Lendo os dados de %s...\n", nome_arquivo_entrada);
    
    int numero_temp;
    while (fscanf(f_entrada, "%d", &numero_temp) == 1) {
        if (n >= capacidade) {
            capacidade *= 2;
            int *temp = (int *)realloc(vetor, capacidade * sizeof(int));
            if (temp == NULL) {
                printf("Erro: faltou memoria RAM para continuar lendo o arquivo.\n");
                free(vetor);
                fclose(f_entrada);
                return 1;
            }
            vetor = temp;
        }
        
        vetor[n] = numero_temp;
        n++;
    }

    fclose(f_entrada);
    
    printf("Foram encontrados %d numeros no arquivo.\n", n);
    
    if (n > 0) {
        printf("Ordenando com Quicksort (Mediana de 3)...\n");
        quicksort(vetor, 0, n - 1);

        FILE *f_saida = fopen(nome_arquivo_saida, "w");
        if (f_saida == NULL) {
            printf("Erro: nao foi possivel criar o arquivo de saida '%s'.\n", nome_arquivo_saida);
            free(vetor);
            return 1;
        }

        printf("Salvando resultados em %s...\n", nome_arquivo_saida);
        for (int i = 0; i < n; i++) {
            fprintf(f_saida, "%d\n", vetor[i]);
        }

        fclose(f_saida);
        printf("Vetor ordenado com sucesso!\n");
    } else {
        printf("Nenhum numero valido foi encontrado no arquivo de entrada.\n");
    }

    free(vetor);

    clock_t fim_tempo = clock();
    double tempo_gasto = (double)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC;

    printf("\n========================================\n");
    printf("Tempo total de execucao: %f segundos\n", tempo_gasto);
    printf("========================================\n");

    return 0;
}