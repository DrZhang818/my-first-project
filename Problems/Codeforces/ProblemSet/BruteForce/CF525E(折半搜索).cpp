#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

ll fac[20];
void solve() {
    int n, k;
    ll tar;
    cin >> n >> k >> tar;
    ll ans = 0;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    auto get = [&](vector<int> &a) -> map<ll,vector<ll>> {
        map<ll,vector<ll>> cnt;
        auto f = [&](this auto &&self, int i, int j, ll s) -> void {
            if(s > tar) return;
            if(i < 0) {
                if(cnt.find(s) == cnt.end()) {
                    cnt[s].resize(k + 1, 0);
                }
                cnt[s][j]++;
                return;
            }
            self(i - 1, j, s);
            int v = a[i];
            self(i - 1, j, s + v);
            if(j < k && v <= 19) {
                self(i - 1, j + 1, s + fac[v]);
            }
        };
        f(a.size() - 1, 0, 0);
        return cnt;
    };
    vector<int> L(a.begin(), a.begin() + n / 2);
    auto cnt = get(L);
    vector<int> R(a.begin() + n / 2, a.end());
    for(auto &[x, b] : get(R)) {
        auto it = cnt.find(tar - x);
        if(it != cnt.end()) {
            auto &c = it->second;
            ll s = 0;
            for(int i = k; i >= 0; i--) {
                s += c[k - i];
                ans += b[i] * s;
            }   
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    fac[0] = 1;
    for(int i = 1; i <= 19; i++) {
        fac[i] = fac[i - 1] * i;
    }
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
