#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    vector<vector<int>> adj(n + 1);

    {
        stack<int> stk;        
        for(int i = 1; i <= n; i++) {
            while(!stk.empty() && a[i] > stk.top()) {
                stk.pop();
            }
            if(!stk.empty()) {
                adj[stk.top()].push_back(a[i]);
            }
            stk.push(a[i]);
        }
    }
    {
        stack<int> stk;
        for(int i = 1; i <= n; i++) {
            while(!stk.empty() && b[i] < stk.top()) {
                stk.pop();
            }
            if(!stk.empty()) {
                adj[stk.top()].push_back(b[i]);
            }
            stk.push(b[i]);
        }
    }

    vector<int> deg(n + 1);
    vector<pair<int,int>> ans;
    for(int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
        for(int j : adj[i]) {
            deg[j]++;
            ans.emplace_back(i, j);
        }
    }

    auto tmp = deg;

    {
        priority_queue<int> pq;
        for(int i = 1; i <= n; i++) {
            if(deg[i] == 0) {
                pq.push(i);
            }
        }
        vector<int> seq(n + 1);

        int i = 1;
        while(!pq.empty()) {
            int u = pq.top();
            seq[i++] = u;
            pq.pop();
            for(int v : adj[u]) {
                if(--deg[v] == 0) {
                    pq.push(v);
                }                
            }
        }
        if(seq != b) {
            cout << "No\n";
            return;
        }
    }

    deg = move(tmp);

    {
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i = 1; i <= n; i++) {
            if(deg[i] == 0) {
                pq.push(i);
            }
        }
        vector<int> seq(n + 1);

        int i = 1;
        while(!pq.empty()) {
            int u = pq.top();
            seq[i++] = u;
            pq.pop();
            for(int v : adj[u]) {
                if(--deg[v] == 0) {
                    pq.push(v);
                }                
            }
        }
        if(seq != a) {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
    cout << ans.size() << "\n";
    for(auto [u, v] : ans) {
        cout << u << " " << v << "\n";
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
