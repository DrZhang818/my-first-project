#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr int inf = 1000000000;
struct info {
    ll x, h;
};
void solve() { 
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].h;
    }
    a[0].x = a[0].h = -inf;
    vector<int> dp(3);
    for(int i = 1; i <= n; i++) {
        auto ndp = dp;
        if(a[i - 1].x + a[i - 1].h < a[i].x - a[i].h) {
            ndp[0] = max(ndp[0], dp[1] + 1);
        }
        if(a[i - 1].x < a[i].x - a[i].h) {
            ndp[0] = max({ndp[0], dp[0] + 1, dp[2] + 1});
        }
        if(a[i - 1].x + a[i - 1].h < a[i].x) {
            ndp[1] = max(ndp[1], dp[1] + 1);
            ndp[2] = max(ndp[2], dp[1]);
        }
        if(a[i - 1].x < a[i].x) {
            ndp[1] = max({ndp[1], dp[0] + 1, dp[2] + 1});
            ndp[2] = max(ndp[2], dp[0]);
        }
        dp = ndp;
    }
    cout << dp[1] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
