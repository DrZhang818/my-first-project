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

void addEdge(Node *adj, int u, int v) {
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->to = v;
    e->nxt = adj[u].head;
    adj[u].head = e;
}

bool vis[100005];
bool dfs(Node *adj, int x, int y, int k) {
    if(x == y) {
        return k == 0;
    }
    if(k == 0) {
        return false;
    }
    vis[x] = true;
    for(Edge *e = adj[x].head; e != NULL; e = e->nxt) {
        int v = e->to;
        if(!vis[v]) {
            if(dfs(adj, v, y, k - 1)) {
                return true;
            }
        }
    }
    vis[x] = false;
    return false;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Node *adj = (Node *)calloc(n + 1, sizeof(Node));
    for(int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(adj, u, v);
        addEdge(adj, v, u);
    }

    int x, y, k;
    scanf("%d %d %d", &x, &y, &k);

    if(dfs(adj, x, y, k)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}