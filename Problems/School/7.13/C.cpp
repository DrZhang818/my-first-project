#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int cnt, w;
};
void solve() {
    int n, k;
    cin >> n >> k;
    k /= 100;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].cnt >> a[i].w;
        a[i].w /= 100;
    }    
    vector dp(k + 1, inf);
    dp[0] = 0;
    for(int i = 1; i <= n; i++) {
        auto ndp = dp;
        for(int j = 0; j <= a[i].cnt; j++) {
            for(int s = k; s >= 1; s--) {
                if(j < a[i].cnt) ndp[s] = min(ndp[s], dp[max(0,s - j * i)] + j);
                else ndp[s] = min(ndp[s], dp[max(0,s - j * i - a[i].w)] + j);
            }
        }
        swap(dp, ndp);
    }

    cout << dp[k] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
