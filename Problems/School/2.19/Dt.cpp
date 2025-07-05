#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<ll> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    vector<vector<int>> adj1(n + 1), adj2(m + 1);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj1[u].push_back(v);
        adj1[v].push_back(u);
    }
    for(int i = 0; i < m - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj2[u].push_back(v);
        adj2[v].push_back(u);
    }
    if(a[1] != b[1]) {
        cout << 0 << "\n";
        return;
    }
    map<ll,int> mp;
    mp[a[1]] = 2;
    queue<ll> q1, q2;
    q1.push(1), q2.push(1);
    int ans = 0;
    vector<int> vis1(n + 1), vis2(m + 1);
    vis1[1] = vis2[1] = 1;
    while(!q1.empty() && !q2.empty()) {
        int len1 = q1.size(), len2 = q2.size();
        while(len1--) {
            int u = q1.front();
            q1.pop();
            if(mp[a[u]] == 2) {
                q1.push(u);
            } else {
                mp[a[u]] = 0;
            }
        }
        while(len2--) {
            int u = q2.front();
            q2.pop();
            if(mp[b[u]] == 2) {
                q2.push(u);
            } else {
                mp[b[u]] = 0;
            }
        }
        if(q1.empty() || q2.empty()) break;
        len1 = q1.size(), len2 = q2.size();
        while(len1--) {
            int u = q1.front();
            q1.pop();
            mp[a[u]] -= 1;
            for(int v : adj1[u]) {
                if(vis1[v]) continue;
                q1.push(v);
                vis1[v] = 1;
                mp[a[v]] += 1;
            }
        }
        while(len2--) {
            int u = q2.front();
            q2.pop();
            mp[b[u]] -= 1;
            for(int v : adj2[u]) {
                if(vis2[v]) continue;
                q2.push(v);
                vis2[v] = 1;
                mp[b[v]] += 1;
            }
        }
        ans += 1;
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
    
