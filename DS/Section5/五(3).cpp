#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define MAXRC 20
#define OK 1
#define ERROR 0

typedef struct {
    int i, j, e;
} Triple;

typedef struct {
    Triple data[MAXSIZE + 1];
    int rpos[MAXRC + 1];
    int mu, nu, tu;
} RLSMatrix;

int MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix *Q) {
    if(M.nu != N.mu) return ERROR;
    Q->mu = M.mu;
    Q->nu = N.nu;
    Q->tu = 0;
    if(M.tu * N.tu != 0) {
        for(int arow = 1; arow <= M.mu; ++arow) {
            int ctemp[MAXRC + 1] = {0};
            Q->rpos[arow] = Q->tu + 1;
            int tp;
            if(arow < M.mu) tp = M.rpos[arow + 1];
            else tp = M.tu + 1;
            for(int p = M.rpos[arow]; p < tp; ++p) {
                int brow = M.data[p].j;
                int t;
                if(brow < N.mu) t = N.rpos[brow + 1];
                else t = N.tu + 1;
                for(int q = N.rpos[brow]; q < t; ++q) {
                    int ccol = N.data[q].j;
                    ctemp[ccol] += M.data[p].e * N.data[q].e;
                }
            }
            for(int ccol = 1; ccol <= Q->nu; ++ccol) {
                if(ctemp[ccol]) {
                    if(++Q->tu > MAXSIZE) return ERROR;
                    Q->data[Q->tu] = (Triple){arow, ccol, ctemp[ccol]};
                }
            }
        }
    }
    return OK;
}

void print(RLSMatrix M) {
    for(int p = 1; p <= M.tu; p++) {
        printf("%d %d %d\n", M.data[p].i, M.data[p].j, M.data[p].e);
    }
}

int main() {
    RLSMatrix M = {
        .data = {{0,0,0}, {1,1,3}, {1,2,2}, {2,1,1}},
        .rpos = {0, 1, 3},
        .mu = 2, .nu = 2, .tu = 3
    };
    RLSMatrix N = {
        .data = {{0,0,0}, {1,1,1}, {1,2,1}, {2,2,1}},
        .rpos = {0, 1, 3},
        .mu = 2, .nu = 2, .tu = 3
    };
    RLSMatrix Q;
    if(MultSMatrix(M, N, &Q)) {
        print(Q);
    }
    return 0;
}