#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 500000;

vector<vector<int>> fac(N + 1);
vector<int> mu(N + 1);

int init = []() {
    mu[1] = 1;

    for(int i = 1; i <= N; i++) {
        fac[i].push_back(i);
        for(int j = 2 * i; j <= N; j += i) {
            fac[j].push_back(i);
            mu[j] -= mu[i];
        }
    }

    return 1;
}();

void solve() {  
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }    

    vector<ll> cnt(N + 1);
    vector<int> tag(n + 1);

    ll ans = 0;
    while(q--) {
        int x;
        cin >> x;
        int add = (tag[x] == 0 ? 1 : -1);
        tag[x] ^= 1;
        const auto& cur = fac[a[x]];
        for(auto d : cur) {
            ans -= 1LL * mu[d] * cnt[d] * (cnt[d] - 1) / 2;
            cnt[d] += add;
            ans += 1LL * mu[d] * cnt[d] * (cnt[d] - 1) / 2;
        }
        cout << ans << "\n";
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
