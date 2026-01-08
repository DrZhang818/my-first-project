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

bool bfs(Node *adj, int n, int x, int y) {
    bool *vis = (bool *)calloc(n + 1, sizeof(bool));
    int *q = (int *)malloc((n + 1) * sizeof(int));
    int head = 0, tail = 0;
    vis[x] = true;
    q[tail++] = x;
    while(head < tail) {
        int u = q[head++];
        for(Edge *e = adj[u].head; e != NULL; e = e->nxt) {
            int v = e->to;
            if(v == y) {
                return true;
            }
            if(!vis[v]) {
                vis[v] = true;
                q[tail++] = v;
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

    if(bfs(adj, n, x, y)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}