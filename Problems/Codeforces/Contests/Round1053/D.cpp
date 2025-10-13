#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

const int MX = 200000;
ll binpow(ll a, ll b, ll m = MOD){
    ll res = 1;
    a %= m;
    while(b > 0){
        if(b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

inline ll inv(ll a){
    return binpow(a, MOD - 2, MOD);
}

static ll fact[MX + 1], invfact[MX + 1];
void init_factorials(){
    fact[0] = 1;
    for(int i = 1; i <= MX; i++){
        fact[i] = fact[i - 1] * i % MOD;
    }
    invfact[MX] = inv(fact[MX]);
    for(int i = MX - 1; i >= 0; i--){
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;
    }
}

ll nCr(int n, int r){
    if(r > n || r < 0) return 0;
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}

ll nPr(int n, int r){
    if(r > n || r < 0) return 0;
    return fact[n] * invfact[n - r] % MOD;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    if(sum != n) {
        cout << 0 << "\n";
        return;
    }
    vector<int> cnt(n + 2);
    for(int i = 1; i <= n; i++) {
        cnt[1]++;
        cnt[min(i, n - i + 1) + 1]--;
    }
    for(int i = 1; i <= n; i++) {
        cnt[i] += cnt[i - 1];
    }
    ll ans = 1;
    int used = 0;
    for(int i = n; i >= 1; i--) {
        int has = cnt[i] - used;
        if(has < a[i]) {
            cout << 0 << "\n";
            return;
        }
        ans = 1LL * ans * nCr(has, a[i]) % MOD;
        used += a[i];
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init_factorials();

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
