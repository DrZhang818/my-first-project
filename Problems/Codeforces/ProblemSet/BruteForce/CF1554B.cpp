#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = 1E18;

void solve1() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll ans = -inf;
    for(int i = n; i >= 1; i--) {
        for(int j = i - 1; j >= 1; j--) {
            if(1LL * i * j <= ans) {
                break;
            }
            ans = max(ans, 1LL * i * j - 1LL * k * (a[i] | a[j]));            
        }
    }
    cout << ans << "\n";
}

//本题也可以DP

void solve2() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    int _or = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        _or |= a[i];
    }
    const int N = __lg(_or) + 1;
    vector<PII> dp(1 << N, {0, 0});
    for(int i = 1; i <= n; i++) {
        auto [x, y] = dp[a[i]];
        dp[a[i]] = {i, x};
    }
    for(int i = 0; i < N; i++) {
        for(int s = 0; s < 1 << N; s++) {
            if(~s >> i & 1) {
                s |= 1 << i;
            }
            auto [x1, y1] = dp[s];
            auto [x2, y2] = dp[s ^ (1 << i)];
            if(x2 > x1) {
                dp[s].first = x2;
                dp[s].second = max(x1, y2);
            } else {
                dp[s].second = max(y1, x2);
            }
        }
    }
    ll ans = -inf;
    for(int s = 0; s < 1 << N; s++) {
        auto [i, j] = dp[s];
        if(j == 0) continue;
        ans = max(ans, 1LL * i * j - 1LL * k * s);
    }
    cout << ans << "\n";    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve2();
    }
    return 0;
}
