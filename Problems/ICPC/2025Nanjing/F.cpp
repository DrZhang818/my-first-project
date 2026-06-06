#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

struct DSU {
    int n;
    vector<int> fa;

    DSU(int n) : n(n), fa(n) {
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int o) {
        return o == fa[o] ? fa[o] : fa[o] = find(fa[o]);
    }

    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if(u == v) return false;
        fa[v] = u;
        return true;
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }
};

constexpr int V = 1 << 12;

void solve() {
    int n, q;
    cin >> n >> q;

    vector<DSU> dsu(V, DSU(n + 1));

    i64 sum = 0;

    while(q--) {
        char op;
        cin >> op;
        if(op == '+') {
            int u, v, w;
            cin >> u >> v >> w;
            
            auto dfs = [&](this auto&& self, int msk) -> void {
                if(!dsu[msk].merge(u, v)) return;
                for(int i = 0; i < 12; i++) {
                    if(msk >> i & 1) {
                        self(msk ^ 1 << i);
                    }
                }
            };

            dfs(w);
        } else {
            int u, v;
            cin >> u >> v;

            int cur = 0;
            for(int i = 11; i >= 0; i--) {
                if(dsu[cur | 1 << i].same(u, v)) {
                    cur |= 1 << i;
                }
            }

            if(!dsu[cur].same(u, v)) {
                cur = -1;
            }

            sum += cur;
        }
    }

    cout << sum << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}