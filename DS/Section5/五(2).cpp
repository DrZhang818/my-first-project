#include <stdio.h>

#define MAXSIZE 101

typedef struct {
    int i, j, v;
} Triple;

typedef struct {
    Triple data[MAXSIZE];
    int mu, nu, tu;
} TSMatrix;

void FastTransmat(TSMatrix M, TSMatrix *N) {
    N->mu = M.nu;
    N->nu = M.mu;
    N->tu = M.tu;
    if (M.tu == 0) return;

    int num[MAXSIZE] = {0};
    int cpot[MAXSIZE] = {0};

    for(int t = 1; t <= M.tu; t++) {
        num[M.data[t].j]++;
    }

    cpot[1] = 1;
    for(int col = 2; col <= M.nu; col++) {
        cpot[col] = cpot[col - 1] + num[col - 1];
    }

    for(int p = 1; p <= M.tu; p++) {
        int col = M.data[p].j;
        int q = cpot[col];
        N->data[q].i = M.data[p].j;
        N->data[q].j = M.data[p].i;
        N->data[q].v = M.data[p].v;
        cpot[col]++;
    }
}

void print(TSMatrix M) {
    for(int p = 1; p <= M.tu; p++) {
        printf("%d %d %d\n", M.data[p].i, M.data[p].j, M.data[p].v);
    }
}

int main() {
    TSMatrix M = {
        .data = {
            {0, 0, 0},
            {1, 2, 12},
            {1, 3, 9},
            {3, 1, -3},
            {3, 6, 14},
            {4, 3, 24},
            {5, 2, 18},
            {6, 5, 15}
        },
        .mu = 6, .nu = 6, .tu = 7
    };

    TSMatrix N;
    FastTransmat(M, &N);
    print(N);

    return 0;
}