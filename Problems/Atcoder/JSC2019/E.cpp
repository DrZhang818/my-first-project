#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class MaxAssignment {
public:
    ll solve(int n, int m, vector<vector<int>> &adj, vector<int> &val) {
        assert(adj.size() == n);
        assert(val.size() == n);
        vector<int> yx(m, -1);
        vector<bool> vis(n, false);
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        sort(p.begin(), p.end(),
            [&](auto x, auto y) {
                return val[x] > val[y];
            });
        auto find = [&](auto &&self, int x) -> bool {
            vis[x] = true;
            for(int y : adj[x]) {
                if(yx[y] == -1 || !vis[yx[y]] && self(self, yx[y])) {
                    yx[y] = x;
                    return true;
                }
            }
            return false;
        };
        ll ans = 0;
        for(auto i : p) {
            if(find(find, i)) {
                vis.assign(n, false);
                ans += val[i];
            }
        }
        return ans;
    }
};

void solve() {
    int n, h, w;
    cin >> n >> h >> w;
    vector<int> val(n);
    vector<vector<int>> adj(n);
    vector<int> id(h + w, -1);
    int idx = 0;
    for(int i = 0; i < n; i++) {
        int r, c;
        cin >> r >> c >> val[i];
        r--;
        c--;
        if(id[r] == -1) {
            id[r] = idx++;
        }
        if(id[h + c] == -1) {
            id[h + c] = idx++;
        }
        adj[i].push_back(id[r]);
        adj[i].push_back(id[h + c]);
    }
    ll ans = MaxAssignment().solve(n, idx, adj, val);
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
