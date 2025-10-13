#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class MaxAssignment {
public:
    int solve(int n, int m, vector<vector<int>> &adj, vector<int> &val) {
        assert(adj.size() == n);
        assert(val.size() == n);
        vector<int> yx(m, -1);
        vector<bool> vis(n, false);
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        sort(p.begin(), p.end(),
            [&](auto x, auto y) {
                return val[x] < val[y];
            });
        auto find = [&](this auto &&self, int x) -> bool {
            vis[x] = true;
            for(int y : adj[x]) {
                if(yx[y] == -1 || !vis[yx[y]] && self(yx[y])) {
                    yx[y] = x;
                    return true;
                }
            }
            return false;
        };
        int ans = 0;
        for(auto i : p) {
            if(find(i)) {
                vis.assign(n, false);
                ans += val[i];
            }
        }
        return ans;
    }
};

void solve() {
    int n;
    cin >> n;

    map<int,int> id;
    vector<vector<int>> adj;
    vector<int> val;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        vector<array<int,2>> ps;
        for(int j = 2; j * j <= x; j++) {
            if(x % j == 0) {
                int t = 0;
                while(x % j == 0) {
                    t++;
                    x /= j;
                }
                ps.push_back({j, t});
            }
        }
        if(x > 1) {
            ps.push_back({x, 1});
        }
        vector<array<int,2>> ds;
        auto dfs = [&](auto &&self, int idx, int d, int t) -> void {
            if(idx == ps.size()) {
                ds.push_back({t, d});
                return ;
            }
            auto [p, e] = ps[idx];
            for(int j = 0; j <= e; j++) {
                if(j) {
                    d *= p;
                    t++;
                }
                self(self, idx + 1, d, t);
            }    
        };  
        dfs(dfs, 0, 1, 0);
        sort(ds.begin(), ds.end());
        ans += ds.back()[0];
        for(auto [t, d] : ds) {
            if(!id.contains(d)) {
                id[d] = adj.size();
                adj.push_back({});
                val.push_back(t);
            }
            adj[id[d]].push_back(i);
        }
    }
    
    int m = val.size();
    ans -= MaxAssignment().solve(m, n, adj, val);
    cout << ans << "\n";

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
