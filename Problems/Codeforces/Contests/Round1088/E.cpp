#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    
    vector<int> dp(n + 1, inf);
    vector<i64> val(n + 1);

    for(int u = n; u >= 1; u--) {
        cin >> val[u];
        int k;
        cin >> k;
        vector<int> son(k);
        for(int i = 0; i < k; i++) {
            cin >> son[i];
        }

        i64 l = 1;
        bool ok = false;
        dp[u] = 0;
        for(int v : son) {
            dp[u] += dp[v];
            i64 g = gcd(val[v], val[u]);
            if(g != 1) {
                ok = true;
            }
            l = l / gcd(l, g) * g;
        }
        if(!ok) {
            dp[u] += 1;
        } else {
            val[u] = l;
        }
        cout << dp[u] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    int t = 1;  
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
