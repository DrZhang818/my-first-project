#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve1() {  
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    queue<int> q;
    q.push(1);
    vector<int> col(n + 1, -1);
    vector<int> vis(n + 1);
    col[1] = 1;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(int v : adj[u]) {
            if(col[v] == -1) {
                col[v] = (col[u] + 1) % 3;
                q.push(v);
            } 
        }
    }
    for(int i = 1; i <= n; i++) {
        if(col[i] == 0) {
            cout << 'r';
        } else if(col[i] == 1) {
            cout << 'g';
        } else {
            cout << 'b';
        }
    }
    cout << "\n";
}

void solve2() {
    int q;
    cin >> q;
    while(q--) {
        int d;
        cin >> d;
        array<int,3> cnt {};
        vector<int> col(d + 1);
        for(int i = 1; i <= d; i++) {
            char c;
            cin >> c;
            if(c == 'r') cnt[0]++, col[i] = 0;
            else if(c == 'g') cnt[1]++, col[i] = 1;
            else cnt[2]++, col[i] = 2;
        }
        if(cnt[0] == d || cnt[1] == d || cnt[2] == d) {
            cout << 1 << "\n";
            continue;
        }
        int t = -1;
        if(cnt[0] && cnt[1]) {
            t = 1;
        } else if(cnt[0] && cnt[2]) {
            t = 0;
        } else {
            t = 2;
        }
        for(int i = 1; i <= d; i++) {
            if(col[i] == t) {
                cout << i << "\n";
                break;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> s;
    if(s[0] == 'f') {
        int t;
        cin >> t;
        while(t--) {
            solve1();
        }
    } else {
        int t;
        cin >> t;
        while(t--) {
            solve2();
        }
    }
    return 0;
}
