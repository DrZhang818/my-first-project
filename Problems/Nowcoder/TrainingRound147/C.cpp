#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int MOD;

int fast_pow(int a, ll b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

void solve() {  
    ll A, B;
    cin >> A >> B >> MOD;
    vector<int> cnt(MOD);
    for(int y = 0; y < MOD; y++) {
        cnt[fast_pow(y, B)]++;
    }
    ll ans = 0;
    for(int x = 0; x < MOD; x++) {
        ans += cnt[fast_pow(x, A)];
    }
    cout << ans << "\n";
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
