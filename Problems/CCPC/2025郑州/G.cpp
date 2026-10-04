#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr i64 inf = i64(1E18) + 9;

void solve() {
    i64 a, b, c;
    cin >> a >> b >> c;

    if(a % b == c % b && a <= c) {
        cout << "YES\n";
        return;
    }

    i64 k = __lg(b);
    i64 U = 1LL << k + 1;
    i64 msk = U - 1;

    vector<vector<i64>> dp(b, vector<i64>(U, inf));

    priority_queue<i64, vector<i64>, greater<i64>> pq;
    pq.push(a);
    dp[a % b][a & msk] = a;

    auto add = [&](i64 x) {
        i64 rem = x % b;
        i64 state = x & msk;
        if(x < dp[rem][state]) {
            dp[rem][state] = x;
            pq.push(x);
        }
    };

    while(!pq.empty()) {
        i64 x = pq.top();
        pq.pop();

        i64 rem = x % b;
        i64 state = x & msk;

        if(dp[rem][state] < x) continue;

        add(x + b);
        add(x ^ b);
    }

    i64 mn = *min_element(dp[c % b].begin(), dp[c % b].end());
    if(mn <= c) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}