#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Edge {
    int to;
    struct Edge *nxt;
} Edge;

typedef struct Node {
    Edge *head;
} Node;

bool vis[100005];

bool dfs(Node *adj, int u, int tar) {
    if(u == tar) return true;
    vis[u] = true;

    for(Edge *e = adj[u].head; e != NULL; e = e->nxt) {
        int v = e->to;
        if(!vis[v]) {
            if(dfs(adj, v, tar)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Node *adj = (Node *)calloc(n + 1, sizeof(Node));
    for(int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        Edge *e = (Edge *)malloc(sizeof(Edge));
        e->to = v;
        e->nxt = adj[u].head;
        adj[u].head = e;
    }

    int x, y;
    scanf("%d %d", &x, &y);

    if(dfs(adj, x, y)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}