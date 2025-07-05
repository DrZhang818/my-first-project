#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.luogu.com.cn/problem/AT_abc139_e
void solve() { 
    int n;
    cin >> n;
    vector<vector<int>> idx(n + 1, vector<int>(n + 1));
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            idx[i][j] = idx[j][i] = ++cnt;
        }
    }
    vector<vector<int>> adj(n * (n - 1) / 2 + 1);
    vector<int> deg(n * (n - 1) / 2 + 1);
    int pre = -1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < n; j++) {
            int x;
            cin >> x;
            if(j > 1) {
                int u = idx[i][pre];
                int v = idx[i][x];
                adj[u].push_back(v);
                deg[v]++;
            }
            pre = x;
        }
    }
    queue<int> q;
    vector<int> vis(cnt + 1);
    for(int i = 1; i <= cnt; i++) {
        if(deg[i] == 0) {
            q.push(i);
            vis[i] = 1;
        }
    }
    int ans = 0;
    while(!q.empty()) {
        int len = q.size();
        for(int i = 0; i < len; i++) {
            int u = q.front();
            q.pop();
            vis[u] = 1;
            for(int v : adj[u]) {
                if(--deg[v] == 0) {
                    q.push(v);
                }
            }
        }
        ans += 1;
    }
    for(int i = 1; i <= cnt; i++) {
        if(!vis[i]) {
            cout << -1 << "\n";
            return;
        }
    }
    cout << ans << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
