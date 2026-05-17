#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void exchange(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int A[], int p, int r) {
    int n_elem = r - p + 1;

    if (n_elem > 2) {
        int idx_menor = p;
        int idx_maior = p;

        for (int j = p + 1; j <= r; j++) {
            if (A[j] < A[idx_menor]) {
                idx_menor = j;
            } else if (A[j] > A[idx_maior]) {
                idx_maior = j;
            }
        }

        int pivo_idx;
        do {
            pivo_idx = p + (rand() % n_elem);
        } while (pivo_idx == idx_menor || pivo_idx == idx_maior);

        exchange(&A[pivo_idx], &A[r]);
    }

    int x = A[r];               
    int i = p - 1;              

    for (int j = p; j <= r - 1; j++) {
        if (A[j] <= x) {
            i = i + 1;          
            exchange(&A[i], &A[j]);
        }
    }
    exchange(&A[i + 1], &A[r]); 
    
    return i + 1;               
}

void quicksort(int A[], int p, int r) {
    if (p < r) {

        int q = partition(A, p, r); 
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, r);

    }
}

int main() {

    srand(time(NULL));

    int vetor[10] = {42, 7, 19, 88, 3, 55, 12, 91, 34, 21};
    int n = 10;

    printf("Vetor Original:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n\n");

    quicksort(vetor, 0, n - 1);

    printf("Vetor Ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}