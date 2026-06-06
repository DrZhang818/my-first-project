#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

constexpr int P = 1000000007;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    i64 m;
    cin >> n >> m;

    vector<int> pre(n + 1);
    pre[0] = 1;

    for (int i = 1; i <= n; i++) {
        pre[i] = 1LL * pre[i - 1] * ((m - i + 1) % P) % P;
    }

    i64 ans = 0;
    i64 suf = 1;

    for (int i = n; i >= 1; i--) {
        ans = (ans + 1LL * i * pre[i - 1] % P * suf) % P;
        suf = suf * ((m - i + 1) % P) % P;
    }

    cout << ans << "\n";

    return 0;
}