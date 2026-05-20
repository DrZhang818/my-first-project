#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

int query(const vector<int>& a) {
    cout << "? 1 " << a.size();
    for(int x : a) {
        cout << " " << x;
    }
    cout << endl;
    int res;
    cin >> res;
    return res;
}

void modify(int u) {
    cout << "? 2 " << u << endl;
}

void answer(const vector<int>& a) {
    cout << "!";
    for(int i = 1; i < a.size(); i++) {
        cout << " " << a[i];
    }
    cout << endl;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> sz(n + 1);
    vector<bool> cands(n + 1, true);

    auto getSize = [&](this auto&& self, int u, int fa) -> void {
        sz[u] = cands[u] ? 1 : 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            sz[u] += sz[v];
        }
    };

    auto getRoot = [&](this auto&& self, int u, int fa, int tot) -> int {
        for(int v : adj[u]) {
            if(v == fa || sz[v] <= tot / 2) continue;
            return self(v, u, tot);
        }
        return u;
    };

    vector<int> S(n);
    iota(S.begin(), S.end(), 1);

    while(S.size() > 1) {
        getSize(1, 0);
        int rt = getRoot(1, 0, S.size());
        getSize(rt, 0);

        vector<int> nS;
        auto add = [&](this auto&& self, int u, int fa) -> void {
            if(cands[u]) {
                nS.push_back(u);
            }
            for(int v : adj[u]) {
                if(v == fa) continue;
                self(v, u);
            }
        };

        sort(adj[rt].begin(), adj[rt].end(), 
            [&](int i, int j) {
                return sz[i] > sz[j];
            });
        int c1 = 0, c2 = 0;
        for(int v : adj[rt]) {
            if(c1 <= c2) {
                add(v, rt);
                c1 += sz[v];
            } else {
                c2 += sz[v];
            }
        }

        int x = query(nS);
        modify(rt);
        int y = query(nS);

        vector<bool> nCands(n + 1);
        for(int u : nS) { 
            nCands[u] = true;
        }

        if(abs(x - y) == 2 * nS.size()) {
            vector<int> tmp;
            for(int u : S) {
                if(!nCands[u]) {
                    tmp.push_back(u);
                } 
                nCands[u] = !nCands[u];
            }
            nS = move(tmp);
        } 
        S = move(nS);
        cands = move(nCands);
    }

    int rt = S[0];

    vector<int> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        ans[i] = query({i});
    }

    auto work = [&](this auto&& self, int u, int fa) -> void {
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
        }
        ans[u] -= ans[fa];
    };
    work(rt, 0);

    answer(ans);
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
