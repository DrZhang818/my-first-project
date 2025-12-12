#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100
#define M 2000
#define inf 1000000000

int adj[N][N];

void prim(int n) {
    int min;
    int adjvex[N];
    int mnCost[N];
    mnCost[1] = 0;
    adjvex[1] = 0;

    for(int i = 2; i <= n; i++) {
        mnCost[i] = adj[1][i];
        adjvex[i] = 1;
    }

    for(int i = 1; i < n; i++) {
        min = inf;
        int k = 0;
        for(int j = 1; j <= n; j++) {
            if(mnCost[j] != 0 && mnCost[j] < min) {
                min = mnCost[j];
                k = j;
            }
        }
        printf("(%d,%d): %d\n", adjvex[k], k, adj[adjvex[k]][k]);
        mnCost[k] = 0;        
        for(int j = 1; j <= n; j++) {
            if(mnCost[j] != 0 && adj[k][j] < mnCost[j]) {
                mnCost[j] = adj[k][j];
                adjvex[j] = k;
            }
        }
    }
}

int main() {

    int n, m;
    scanf("%d %d", &n, &m);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            adj[i][j] = inf;
        }
    }

    for(int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        adj[u][v] = adj[v][u] = w;
    }

    prim(n);

    return 0;
}