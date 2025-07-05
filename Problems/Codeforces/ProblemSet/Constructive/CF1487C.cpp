#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1, vector<int>(n + 1));
    int tot = n * (n - 1) / 2;
    int cnt = tot / n;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < cnt; j++) {
            int u = i, v = (i + j) % n + 1;
            adj[u][v] = 1;
            adj[v][u] = -1;
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            cout << adj[i][j] << " ";
        }
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
