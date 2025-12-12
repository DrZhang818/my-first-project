#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100
#define M 2000

struct Edge {
    int to;
    int next;
} e[M];

int head[N], edge_cnt, vis[N];

void init() {
    memset(head, -1, sizeof(head));
    edge_cnt = 0;
}

void addEdge(int u, int v) {
    e[edge_cnt].to = v;
    e[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

void dfs(int u) {
    printf("%d ", u);
    vis[u] = 1;
    for(int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        if(!vis[v]) {
            dfs(v);
        }
    }
}

void print_dfs(int n) {
    memset(vis, 0, sizeof vis);
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            dfs(i);
        }
    }
    printf("\n");
}

void print_bfs(int n) {
    memset(vis, 0, sizeof vis);
    int que[N];
    int front = 0, rear = 0;
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            vis[i] = 1;
            printf("%d ", i);
            que[rear++] = i;
            while(front != rear) {
                int u = que[front++];
                for(int j = head[u]; ~j; j = e[j].next) {
                    int v = e[j].to;
                    if(!vis[v]) {
                        vis[v] = 1;
                        printf("%d ", v);
                        que[rear++] = v;
                    }
                }
            }
        }
    }
    printf("\n");
}

int main() {
    init();

    int n, m;
    scanf("%d %d", &n, &m);

    for(int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    print_dfs(n);
    print_bfs(n);

    return 0;
}