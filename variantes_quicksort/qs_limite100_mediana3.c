#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int escolher_pivo_hibrido(int A[], int p, int r) {
    int n_elem = r - p + 1;
    int k = 100;

    if (n_elem <= k * 2) {
        int mid = p + (r - p) / 2;
        int i1 = p, i2 = mid, i3 = r;
        
        if (A[i1] > A[i2]) swap(&i1, &i2);
        if (A[i1] > A[i3]) swap(&i1, &i3);
        if (A[i2] > A[i3]) swap(&i2, &i3);
        
        return i2;
    }

    int idx_menores[100];
    int idx_maiores[100];
    int qtd_menores = 0;
    int qtd_maiores = 0;

    for (int j = p; j <= r; j++) {

        if (qtd_menores < k) {
            int pos = qtd_menores - 1;
            while(pos >= 0 && A[j] < A[idx_menores[pos]]) {
                idx_menores[pos + 1] = idx_menores[pos];
                pos--;
            }
            idx_menores[pos + 1] = j;
            qtd_menores++;
        } else if (A[j] < A[idx_menores[k - 1]]) { 
            int pos = k - 2;
            while(pos >= 0 && A[j] < A[idx_menores[pos]]) {
                idx_menores[pos + 1] = idx_menores[pos];
                pos--;
            }
            idx_menores[pos + 1] = j;
        }

        if (qtd_maiores < k) {
            int pos = qtd_maiores - 1;
            while(pos >= 0 && A[j] > A[idx_maiores[pos]]) {
                idx_maiores[pos + 1] = idx_maiores[pos];
                pos--;
            }
            idx_maiores[pos + 1] = j;
            qtd_maiores++;
        } else if (A[j] > A[idx_maiores[k - 1]]) { 
            int pos = k - 2;
            while(pos >= 0 && A[j] > A[idx_maiores[pos]]) {
                idx_maiores[pos + 1] = idx_maiores[pos];
                pos--;
            }
            idx_maiores[pos + 1] = j;
        }
    }

    int indices_seguros[3];
    for (int c = 0; c < 3; c++) {
        int pivo_idx;
        int eh_extremo;
        do {
            pivo_idx = p + (rand() % n_elem);
            eh_extremo = 0;
            for (int m = 0; m < k; m++) {
                if (idx_menores[m] == pivo_idx || idx_maiores[m] == pivo_idx) {
                    eh_extremo = 1;
                    break; 
                }
            }
        } while (eh_extremo); 
        
        indices_seguros[c] = pivo_idx;
    }

    int i1 = indices_seguros[0];
    int i2 = indices_seguros[1];
    int i3 = indices_seguros[2];

    if (A[i1] > A[i2]) swap(&i1, &i2);
    if (A[i1] > A[i3]) swap(&i1, &i3);
    if (A[i2] > A[i3]) swap(&i2, &i3);

    return i2;
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

int partition_custom(int A[], int p, int r) {
    int pivo_idx = escolher_pivo_hibrido(A, p, r);
    swap(&A[pivo_idx], &A[r]);
    return partition(A, p, r);
}

void quicksort(int A[], int p, int r) {
    if (p < r) {
        int q = partition_custom(A, p, r);
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, r);
    }
}

int main(int argc, char *argv[]) {
    clock_t inicio_tempo = clock();

    srand(time(NULL));

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
        printf("Ordenando com Quicksort (100 Extremos + Mediana de 3)...\n");
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