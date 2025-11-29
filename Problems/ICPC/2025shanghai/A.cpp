#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int query(int u, int k) {
    cout << "? " << u << " " << k << endl;
    int res;
    cin >> res;
    return res;
}

void answer(int u) {
    cout << "! " << u << endl;
}

void solve() {
    int n;
    cin >> n;
    
    vector<int> fa(n + 1);
    vector<vector<int>> adj(n + 1);
    for(int i = 2; i <= n; i++) {
        cin >> fa[i];
        adj[fa[i]].push_back(i);
    }
    
    int l = -1, r = 0;
    vector<int> dep(n + 1);
    [&](this auto &&self, int u) -> void {
        for(int v : adj[u]) {
            dep[v] = dep[u] + 1;
            r = max(r, dep[v] + 1);
            self(v);
        }
    }(1);

    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(query(1, mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }

    int dis = r;
    vector<int> ver;
    for(int i = 1; i <= n; i++) {
        if(dep[i] == dis) {
            ver.push_back(i);
        }
    }

    vector<int> cnt(n + 1);
    auto work = [&](this auto &&self, int u) -> void {
        for(int v : adj[u]) {
            self(v);
            cnt[u] += cnt[v];
        }
    };

    vector<int> vis(n + 1);
    auto dfs = [&](this auto &&self, int u) -> void {
        if(dep[u] == dis) {
            vis[u] = true;
        }
        for(int v : adj[u]) {
            self(v);
        }
    };

    while(ver.size() > 1) {
        fill(cnt.begin() + 1, cnt.end(), 0);
        fill(vis.begin() + 1, vis.end(), 0);
        for(int o : ver) {
            cnt[o]++;
        }
        work(1);
        int m = ver.size();
        int u = 1;
        while(cnt[u] > m / 2 && adj[u].size() > 0) {
            int nxt = -1, mx = -1;
            for(int v : adj[u]) {
                if(cnt[v] > mx) {
                    mx = cnt[v];
                    nxt = v;
                }
            }
            u = nxt;
        }
        dfs(u);
        int d = dis - dep[u];
        vector<int> nver;
        int s = query(u, d);
        for(int o : ver) {
            if(vis[o] == s) {
                nver.push_back(o);
            }
        }
        ver = move(nver);
    }

    answer(ver[0]);
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
