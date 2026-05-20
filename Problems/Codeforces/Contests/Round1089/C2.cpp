#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9 + 7;
constexpr int N = 300;

vector<int> minp, primes;

auto init = []() {
    minp.resize(N + 1);
    for(int i = 2; i <= N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        if(primes.size() >= 21) break;
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(minp[i] == p) break;
        }
    }
    primes.insert(primes.begin(), 1);
    return 1;
}();

const int m = primes.size();

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    vector<bool> vis(n + 1);

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int l = i == 1 ? 1 : gcd(a[i], a[i - 1]);
        int r = i == n ? 1 : gcd(a[i], a[i + 1]);
        int tar = lcm(l, r);
        if(tar > b[i]) {
            vis[i] = true;
            continue;
        }
        if(tar < a[i]) {
            ans++;
            a[i] = tar;
            vis[i] = true;
        }
    }

    vector<int> dp(m, -inf);
    dp[0] = ans;
    for(int i = 1; i <= n; i++) {
        int mx = *max_element(dp.begin(), dp.end());
        if(vis[i]) {
            dp[0] = mx;
            fill(dp.begin() + 1, dp.end(), -inf);
            continue;
        }
        vector<int> ndp(m, -inf);
        ndp[0] = mx;
        for(int k = 1; k < m; k++) {
            if(1LL * a[i] * primes[k] > b[i]) break;
            if(i < n && gcd(1LL * a[i] * primes[k], a[i + 1]) != gcd(a[i], a[i + 1])) {
                continue;
            }
            if(i > 1 && gcd(1LL * a[i] * primes[k], a[i - 1]) != gcd(a[i], a[i - 1])) {
                continue;
            }
            for(int j = 0; j < m; j++) {
                if(j == k) continue;
                ndp[k] = max(ndp[k], dp[j] + 1);
            }
        }
        dp = move(ndp);
    }

    ans = *max_element(dp.begin(), dp.end());
    cout << ans << "\n";
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
