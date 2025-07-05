#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<vector<ll>> dis(n + 1, vector<ll>(n + 1));
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> dis[i][j];
            ans += dis[i][j];
        }
    }
    vector<vector<bool>> vis(n + 1, vector<bool>(n + 1, false));
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(k == i || k == j) continue;
                if(dis[i][k] + dis[k][j] < dis[i][j]) {
                    cout << -1 << "\n";
                    return;
                }
                else if(!vis[i][j] && dis[i][k] + dis[k][j] == dis[i][j]) {
                    ans -= dis[i][j];
                    vis[i][j] = true;
                }
            }
        }
    }
    cout << ans / 2 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
