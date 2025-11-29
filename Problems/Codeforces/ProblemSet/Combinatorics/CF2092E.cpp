#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    array<int, 2> cnt {};
    for(int i = 1; i <= k; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        if((x == 1) ^ (x == n) ^ (y == 1) ^ (y == m)) {
            cnt[c]++;
        }
    }
    int ans = 0;
    if(cnt[0] + cnt[1] != 2LL * (n + m - 4)) {
        ans = fast_pow(2, (1LL * n * m - k - 1) % (MOD - 1));
    } else if(cnt[0] % 2 == 0) {
        ans = fast_pow(2, (1LL * n * m - k) % (MOD - 1));
    }
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
