#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


void solve() { 
    int n, k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> memo(n + 1, -1);
    auto dfs = [&](this auto &&dfs, int pos) -> ll {
        if(n - pos < k) return 0;
        ll &res = memo[pos];
        if(res != -1) return res;
        res = dfs(pos + 1);
        ll sum = 0;
        for(int j = pos; j + (j - pos + 1) * k <= n; j++) {
            sum += a[j];
            res = max(res, dfs(j + 1 + (j - pos + 1) * k) + sum);
        }
        return res;
    };
    ll ans = dfs(1);
    cout << ans << "\n";
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
    
