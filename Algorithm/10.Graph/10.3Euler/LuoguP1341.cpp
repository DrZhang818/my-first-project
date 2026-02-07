#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 52;

struct Info {
    int v, id;
    friend bool operator<(const Info& a, const Info& b) {
        return a.v < b.v;
    }
};

void solve() {  
    int n;
    cin >> n;

    vector<vector<Info>> adj(N);

    vector<int> deg(N);

    for(int i = 1; i <= n; i++) {
        char x, y;
        cin >> x >> y;
        int u = x <= 'Z' ? x - 'A' : x - 'a' + 26;
        int v = y <= 'Z' ? y - 'A' : y - 'a' + 26;
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
        deg[u]++;
        deg[v]++;
    }

    int S = -1, T = -1;
    bool ok = true;
    for(int i = 0; i < N; i++) {
        if(deg[i] & 1) {
            if(S == -1) {
                S = i;
            } else if(T == -1) {
                T = i;
            } else {
                ok = false;
                break;
            }
        } 
    }

    if(!ok) {
        cout << "No Solution\n";
        return;
    }

    if(S == -1) {
        S = 0;
        for(int i = 0; i < N; i++) {
            if(deg[i] > 0) {
                S = i;
                break;
            }
        }
    }

    for(int i = 0; i < N; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    vector<char> ans;
    vector<int> cur(N);
    vector<bool> vis(n + 1);

    auto dfs = [&](this auto&& self, int u) -> void {
        while(cur[u] < adj[u].size()) {
            auto [v, id] = adj[u][cur[u]++];
            if(!vis[id]) {
                vis[id] = true;
                self(v);
            }
        }
        char c = (u < 26 ? char('A' + u) : char('a' + u - 26));
        ans.push_back(c);
    }; 

    dfs(S);

    if(ans.size() != n + 1) {
        cout << "No Solution\n";
        return;
    }

    reverse(ans.begin(), ans.end());

    for(int i = 0; i <= n; i++) {
        cout << ans[i];
    }
    cout << "\n";

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
