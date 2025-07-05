#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//解决有向无环图(DAG)
void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    vector<int> res;
    vector<int> vis(n + 1, 0);
    stack<pair<int, bool>> stk;
    bool hasCycle = false;
    for(int i = 1; i <= n && !hasCycle; i++) {
        if(vis[i] != 0) continue;
        stk.push({i, false});
        while(!stk.empty()) {
            auto [u, state] = stk.top();
            stk.pop();

            if(state) {
                res.push_back(u);
                vis[u] = 2;
                continue;
            }
            if(vis[u] == 1) {
                hasCycle = true;
                break;
            }

            vis[u] = 1;
            stk.push({u, true});    
            for(auto it = adj[u].rbegin(); it != adj[u].rend() && !hasCycle; it++) {
                int v = *it;
                if(vis[v] == 1) {
                    hasCycle = true;
                } else if(vis[v] == 0) {
                    stk.push({v, false});
                }
            }
        }
    }
    if(hasCycle) {
        cout << -1 << "\n";
        return;
    }
    reverse(res.begin(), res.end());
    for(int x : res) {
        cout << x << " ";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

