#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int k, p;
};
ll fast_pow(int a, int b) {
    ll res = 1;
    while(b) {
        if(b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}
void solve() {
    int n, m;
    cin >> n >> m;
    vector<info> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].k >> a[i].p;
    }
    auto get = [&](vector<info> &a) -> map<ll,int> {
        map<ll,int> mp;
        auto f = [&](this auto &&self, int i, ll s) -> void {
            if(i < 0) {
                mp[s]++;
                return;
            }
            for(int j = 1; j <= m; j++) {
                self(i - 1, s + a[i].k * fast_pow(j, a[i].p));
            }
        };
        f(a.size() - 1, 0);
        return mp;
    };
    vector<info> L(a.begin(), a.begin() + n / 2);
    auto cnt = get(L);
    vector<info> R(a.begin() + n / 2, a.end());
    ll ans = 0;
    for(auto [x, c] : get(R)) {
        if(cnt.find(-x) != cnt.end()) {
            ans += c * cnt[-x];
        }
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
