#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    fa[v] = u;
}
bool same(int u, int v) {
    return find(u) == find(v);
}
void solve() {
    int n, m;
    cin >> n >> m;
    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    vector<int> cnt(n + 1);
    bool ok = true;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        cnt[u]++;
        cnt[v]++;
        if(same(u, v)) {
            ok = false;
            break;
        }
        if(cnt[u] >= 3 || cnt[v] >= 3) {
            ok = false;
            break;
        }
        merge(u, v);
    }
    if(ok) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
