#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> adj(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n - 1; i++) {
        for(int j = i + 1; j <= n; j++) {
            cin >> adj[i][j];
        }   
    }
    vector<int> sz(n + 1), nxt(n + 1);
    int mx = 0;
    for(int i = n; i >= 1; i--) {
        sz[i] = a[i];
        for(int j = 1; j <= n; j++) {
            if(adj[i][j] && sz[j] + a[i] > sz[i]) {
                sz[i] = sz[j] + a[i];
                nxt[i] = j;
            }
        }
        mx = max(mx, sz[i]);
    }
    int idx = 0;
    while(sz[idx] != mx) idx++;
    int ans = 0;
    while(idx) {
        cout << idx << " ";
        ans += a[idx];
        idx = nxt[idx];
    }
    cout << "\n" << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
