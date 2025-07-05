#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int nn, kk;
    cin >> nn >> kk;
    vector<vector<vector<ll>>> memo(nn + 1, vector<vector<ll>>(kk + 1, vector<ll>(nn + 1, -1)));
    auto dfs = [&](auto&& dfs, int n, int k, int mn)->ll{
        if(k == 0){
            return n == 0 ? 1 : 0;
        }
        if(n < 0) return 0;
        ll &res = memo[n][k][mn];
        if(res != -1) return res;
        res = 0;
        for(int p = mn; p <= n; p++){
            res += dfs(dfs, n - p, k - 1, p);
        }        
        return res;
    };
    ll res = dfs(dfs, nn, kk, 1);        
    cout << res << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}