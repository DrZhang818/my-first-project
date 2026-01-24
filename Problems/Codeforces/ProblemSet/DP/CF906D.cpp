#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int get(int x) {
    int res = x;
    for(int i = 2; i * i <= x; i++) {
        if(x % i) continue;
        int p = i;
        res = res / i * (i - 1);
        while(x % p == 0) x /= p;
    }
    if(x > 1) res = res / x * (x - 1);
    return res;
}

int tag_pow(ll a, ll b, int MOD) {
    ll res = 1;
    bool tag = false;
    if(a >= MOD) {
        a %= MOD;
        tag = true;
    }
    while(b) {
        if(b & 1) {
            res *= a;
            if(res >= MOD) {
                res %= MOD;
                tag = true;
            }
        }
        a *= a;
        if(a >= MOD) {
            a %= MOD;
            tag = true;
        }
        b >>= 1;
    }
    return res + (tag ? MOD : 0);
}

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<int> phi;
    for(int i = m; i > 1;) {
        phi.push_back(get(i));
        i = phi.back();
    }
    reverse(phi.begin(), phi.end());

    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }    

    auto dfs = [&](this auto&& self, int l, int r, int m) -> int {
        if(m == 1) {
            return 1;
        }
        if(l == r) {
            return a[l] >= m ? a[l] + m : a[l];
        }
        auto it = lower_bound(phi.begin(), phi.end(), m);
        it--;
        int p = *it;
        return tag_pow(a[l], self(l + 1, r, p), m);
    };

    int q;
    cin >> q;
    while(q--) {
        int l, r;
        cin >> l >> r;
        cout << dfs(l, r, m) % m << "\n";
    }
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
