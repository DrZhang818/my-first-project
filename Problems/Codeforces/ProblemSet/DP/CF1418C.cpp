#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr int inf = 1000000000;
void solve() { 
    int n; 
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector dp(3, vector<vector<int>>(2, vector<int>(2, inf)));
    dp[0][0][0] = a[1]; dp[1][0][1] = a[1] + a[2]; dp[1][1][0] = a[1];
    for(int i = 3; i <= n; i++) {
        auto &c = dp[(i - 1) % 3], &p = dp[(i - 2) % 3], &pp = dp[i % 3];
        c[0][0] = min(p[1][0], p[1][1]) + a[i];
        c[0][1] = min(pp[1][0], pp[1][1]) + a[i] + a[i - 1];
        c[1][0] = min(p[0][0], p[0][1]);
        c[1][1] = min(pp[0][0], pp[0][1]);
    }
    auto &c = dp[(n - 1) % 3];
    cout << min({c[0][0], c[0][1], c[1][0], c[1][1]}) << "\n";
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
    
