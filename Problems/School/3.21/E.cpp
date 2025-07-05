#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr int inf = 1000000000;
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<ll> dp(1 << n, inf);
    dp[0] = 0;
    vector<int> a(m + 1), b(m + 1);
    for(int i = 1; i <= m; i++) {
        int len;
        cin >> b[i] >> len;
        for(int j = 0; j < len; j++) {
            int v;
            cin >> v;
            a[i] |= (1 << v - 1);
        }
    }
    for(int i = 1; i <= m; i++) {
        for(int s = 0; s < 1 << n; s++) {
            dp[s | a[i]] = min(dp[s | a[i]], dp[s] + b[i]);
        }
    }
    if(dp[(1 << n) - 1] == inf) {
        cout << -1 << "\n";
    } else {
        cout << dp[(1 << n) - 1] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
