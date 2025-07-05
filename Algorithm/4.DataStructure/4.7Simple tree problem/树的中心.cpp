#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr int inf = 100000000;
void solve() {
    int n;
    cin >> n;
    vector<vector<PII>> adj(n);
    for(int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<int> d1(n), d2(n);
    auto dfsd = [&](auto &&dfsd, int u, int fa) -> int {
        int t1 = -inf, t2 = -inf;
        for(auto &[v, w] : adj[u]) {
            if(v == fa) continue;
            int temp = dfsd(dfsd, v, u) + w;
            if(temp > t1) {
                t2 = t1;
                t1 = temp;
            } else if(temp > t2){
                t2 = temp;
            }
        }
        t1 = t1 == -inf ? 0 : t1;
        t2 = t2 == -inf ? 0 : t2;
        d1[u] = t1;
        d2[u] = t2;
        return t1;
    };
    vector<int> up(n);
    auto dfsu = [&](auto &&dfsu, int u, int fa) -> void {
        for(auto &[v, w] : adj[u]) {
            if(v == fa) continue;
            up[v] = up[u] + w;
            if(d1[v] + w == d1[u]) {
                up[v] = max(up[v], d2[u] + w);
            } else {
                up[v] = max(up[v], d1[u] + w);
            }
            dfsu(dfsu, v, u);
        }
    };
    dfsd(dfsd, 0, -1);
    dfsu(dfsu, 0, -1);
    int mn = inf, x = -1, y = -1;
    for(int i = 0; i < n; i++) {
        int mx = max(d1[i], up[i]);
        if(mx < mn) {
            mn = mx;
            x = i + 1;
            y = -1;
        } else if(mx == mn){
            y = i + 1;
        }
    }
    if(y != -1) cout << x << "\n" << y << "\n";
    else cout << x << "\n";
} 

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
