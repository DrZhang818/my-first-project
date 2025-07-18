#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

//https://ac.nowcoder.com/acm/problem/297618
/*
    DP 
    

*/
vector<array<int,100>> pre;
ll fast_pow(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
const int inv100 = fast_pow(100, MOD - 2);
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void init(int n) {
    pre.resize(n + 1); 
    for(int i = 1; i <= 100; i++) {
        int p = 1LL * i * inv100 % MOD;
        int invp = fast_pow(p, MOD - 2);
        pre[1][i] = invp;
        for(int j = 2; j <= n; j++) {
            pre[j][i] = 1LL * invp * (1LL * (1 - p + MOD) % MOD * pre[j - 1][i] % MOD + 1) % MOD;
        }
    }
    for(int j = 1; j <= 100; j++) {
        for(int i = 1; i <= n; i++) {
            add(pre[i][j], pre[i - 1][j]);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    init(n);
    vector<int> a(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    int ans = 0;
    for(int i = 1; i <= 2 * n; i++) {
        add(ans, pre[(i + 1) / 2][a[i]]);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
