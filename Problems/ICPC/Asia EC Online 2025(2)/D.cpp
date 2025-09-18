#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;
const int N = 200000;
const int inv2 = (MOD + 1) / 2;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

int mi_2[N + 1], mi_3[N + 1];

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end(), greater<int>());
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int cur = 1LL * a[i] * (mi_3[n - i] + 1) % MOD * inv2 % MOD * mi_2[i - 1] % MOD;
        add(ans, cur);        
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    mi_2[0] = mi_3[0] = 1;
    for(int i = 1; i <= N; i++) {
        mi_2[i] = 2LL * mi_2[i - 1] % MOD;
        mi_3[i] = 3LL * mi_3[i - 1] % MOD;
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
