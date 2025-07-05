#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


struct edge {
    int u, v, w;
    friend bool operator < (const edge &a, const edge &b) {
        return a.w < b.w;
    }
};
vector<int> fa;
vector<edge> e;
int ans = 0, cnt = 0, n, m;
int find(int u) { return u == fa[u] ? fa[u] : fa[u] = find(fa[u]); }
bool kruskal() {
    sort(e.begin() + 1, e.end());
    for(int i = 1; i <= m; i++) {
        int x = find(e[i].u), y = find(e[i].v);
        if(x != y) fa[x] = y, ans += e[i].w, cnt++;
    }
    return cnt == n - 1;
}
void solve() { 
    cin >> n >> m;
    e.resize(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
    }
    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    if(!kruskal()) cout << "orz\n";
    else cout << ans << "\n"; 
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
