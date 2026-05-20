#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

struct DSU {
    vector<int> fa;
    DSU(int n) : fa(n) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int o) {
        while(o != fa[o]) {
            o = fa[o] = fa[fa[o]];
        }
        return o;
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) return false;
        fa[x] = y;
        return true;
    }
};

int query(int l, int r) {
    cout << "? " << l << " " << r << endl;
    int res;
    cin >> res;
    return res;
}

int answer(const string& s) {
    cout << "! " << s << endl;
    int res;
    cin >> res;
    assert(res != -1);
    return res;
}

void solve() {
    int n;
    cin >> n;

    DSU dsu(n + 1);
    vector<vector<pair<int,int>>> adj(n + 1);

    for(int len = n >> 1 << 1; len >= 2; len -= 2) {
        for(int i = 0; i + len <= n; i++) {
            if(dsu.merge(i, i + len)) {
                int f = query(i + 1, i + len);
                int w = (len / f) & 1;
                adj[i].emplace_back(i + len, w);
                adj[i + len].emplace_back(i, w);
            }
        }
    }

    vector<int> P(n + 1, -1);
    auto dfs = [&](this auto&& self, int u) -> void {
        for(auto [v, w] : adj[u]) {
            if(P[v] == -1) {
                P[v] = P[u] ^ w;
                self(v);
            }
        }
    };

    for(int i : {0, 1}) {
        P[i] = 0;
        dfs(i);
    }

    string s(n, '0');
    for(int i = 1; i <= n; i++) {
        s[i - 1] = (P[i] ^ P[i - 1]) ? '1' : '0';
    }

    int res = answer(s);
    if(res == 1) return;

    for(int i = 0; i < n; i++) {
        s[i] ^= 1;
    }
    answer(s);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
