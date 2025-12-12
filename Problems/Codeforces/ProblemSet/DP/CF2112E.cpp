#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 500000;

vector<int> dp(N + 1, inf);
vector<int> fac[N + 1];

void solve() {
    int n;
    cin >> n;
    if(n % 2 == 0) {
        cout << -1 << "\n"; 
        return;
    }
    cout << dp[n] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    dp[1] = 1;
    for(int i = 1; i <= N; i += 2) {
        for(int j = 1; (i + 2) * j <= N; j += 2) {
            dp[(i + 2) * j] = min(dp[(i + 2) * j], dp[i] + dp[j]);
        }
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}