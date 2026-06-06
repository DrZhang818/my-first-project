#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;

struct Edge {
    long long v, w, next;

    Edge(long long x = 0, long long y = 0, long long z = 0) {
        v = x;
        w = y;
        next = z;
    }
} E[1000006];
long long head[510], cnt = 1, S, T;
long long cur[510];

void addEdge(long long u, long long v, long long w) {
    E[++cnt] = Edge(v, w, head[u]);
    head[u] = cnt;
}

long long n, m, c, d;
char s[252][252];
long long vis[510], epoch;
long long dep[510];

queue<int> q;

bool bfs() {
    q.push(S);
    vis[S] = ++epoch;
    while(!q.empty()) {
        long long u = q.front();
        cur[u] = head[u];
        q.pop();
        for(long long i = head[u];i;i = E[i].next) {
            if(E[i].w && vis[E[i].v] != epoch) {
                q.push(E[i].v);
                dep[E[i].v] = dep[u] + 1;
                vis[E[i].v] = epoch;
            }
        }
    }
    return vis[T] == epoch;
}

long long dfs(long long u, long long f) {
    if(u == T) return f;
    long long s = 0;
    for(long long &i = cur[u];i;i = E[i].next) {
        if(E[i].w && dep[E[i].v] == dep[u] + 1) {
            long long tmp = dfs(E[i].v, min(E[i].w, f - s));
            s += tmp;
            E[i].w -= tmp;
            E[i ^ 1].w += tmp;
        }
        if(s == f) break;
    }
    return s;
}

long long Dinic() {
    long long res = 0;
    while(bfs()) {
        res += dfs(S, n * m);
    }
    // printf("%lld|", res);
    return res;
}

int main() {
    scanf("%lld%lld%lld%lld", &n, &m, &c, &d);
    S = n + m + 1;
    T = n + m + 2;
    for(long long i = 1;i <= n;i++) {
        addEdge(S, i, 0);
        addEdge(i, S, 0);
    }
    for(long long i = 1;i <= m;i++) {
        addEdge(n + i, T, 0);
        addEdge(T, n + i, 0);
    }
    long long z = 0;
    for(long long i = 1;i <= n;i++) {
        scanf("%s", s[i] + 1);
        for(long long j = m, lst = m + 1;j >= 1;j--) {
            if(s[i][j] == '.') {
                addEdge(i, n + j, 1);
                addEdge(n + j, i, 0);
                ++z;
            }
        }
    }
    long long ans = d * z;
    for(long long k = 1;k <= max(n, m);k++) {
        // printf("%lld!:", k);
        for(long long i = 1;i <= n;i++) {
            ++E[i * 2].w;
        }
        for(long long i = 1;i <= m;i++) {
            ++E[n * 2 + i * 2].w;
        }
        auto delta = Dinic();
        if(delta == 0) break;
        z -= delta;
        ans = min(ans, c * k + d * z);
    }
    printf("%lld\n", ans);
    return 0;
}
