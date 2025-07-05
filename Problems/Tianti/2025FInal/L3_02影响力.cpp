#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }  
    vector<ll> cu(n + m), cv(n + m), preU(n + m), preV(n + m);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cu[i + j - 1]++;
            cv[i - j + m]++;
        }
    }
    for(int i = 1; i < n + m; i++) preU[i] = i * cu[i], preV[i] = i * cv[i];
    for(int i = 1; i < n + m; i++) {
        cu[i] += cu[i - 1];
        cv[i] += cv[i - 1];
        preU[i] += preU[i - 1];
        preV[i] += preV[i - 1];
    }
    vector<vector<ll>> ans(n + 1, vector<ll>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int u = i + j - 1, v = i - j + m;
            ans[i][j] += 2 * u * cu[u] - u * cu[n + m - 1] + 2 * v * cv[v] - v * cv[n + m - 1];
            ans[i][j] -= 2 * preU[u] - preU[n + m - 1] + 2 * preV[v] - preV[n + m - 1];
            ans[i][j] = ans[i][j] * a[i][j] / 2;
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cout << ans[i][j] << " \n"[j == m];
        }
    }    
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}