#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
    }
    
    vector<int> vis(n + 1);
    set<int> st;
    st.insert(adj[1].begin(), adj[1].end());
    vis[1] = true;
    st.erase(1);
    int num = 1;

    for(int i = 1; i <= n; i++) {
        while(!st.empty() && *st.begin() <= i) {
            int u = *st.begin();
            st.erase(u);
            if(!vis[u]) {
                vis[u] = true;
                num++;
                st.insert(adj[u].begin(), adj[u].end());
            }
        }
        if(num < i) {
            cout << -1 << "\n";
            continue;
        }
        cout << st.size() << "\n";
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
