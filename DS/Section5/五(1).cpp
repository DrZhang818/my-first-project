#include <stdio.h>

#define MAXSIZE 100

typedef struct {
    int i, j;   
    int v;      
} Triple;

typedef struct {
    Triple data[MAXSIZE + 1]; 
    int mu, nu, tu;           
} TSMatrix;

void Transmat(TSMatrix M, TSMatrix *N) {
    N->mu = M.nu; 
    N->nu = M.mu; 
    N->tu = M.tu;

    if(M.tu == 0) return;

    int q = 1; 
    for(int col = 1; col <= M.nu; col++) {
        for(int p = 1; p <= M.tu; p++) {
            if (M.data[p].j == col) {
                N->data[q].i = M.data[p].j;
                N->data[q].j = M.data[p].i;
                N->data[q].v = M.data[p].v;
                q++;
            }
        }
    }
}

void printMatrix(TSMatrix M) {
    printf("Rows: %d, Cols: %d, Non-zero: %d\n", M.mu, M.nu, M.tu);
    for(int p = 1; p <= M.tu; p++) {
        printf("(%d, %d, %d)\n", M.data[p].i, M.data[p].j, M.data[p].v);
    }
}

int main() {
    TSMatrix M = {
        .data = {
            {0, 0, 0},    
            {1, 2, 10},   
            {1, 3, 20},   
            {3, 1, 30}    
        },
        .mu = 3, 
        .nu = 4, 
        .tu = 3
    };

    TSMatrix N;
    Transmat(M, &N);

    printMatrix(M);

    printMatrix(N);

    return 0;
}