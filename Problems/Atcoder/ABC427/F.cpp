#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    using T = pair<unordered_map<int,int>, unordered_map<int,int>>;
    auto get = [&](int L, int R) -> T {
        unordered_map<int,int> mp0, mp1;
        int c = 0;
        auto dfs = [&](auto &&self, int i, int x) -> void {
            c++;
            if(i == R + 1) {
                mp0[x]++;
                return;
            }
            if(i == R + 2) {
                mp1[x]++;
                return;
            }
            self(self, i + 1, x);
            self(self, i + 2, x + a[i] >= m ? x + a[i] - m : x + a[i]);
        };
        dfs(dfs, L, 0);
        return make_pair(mp0, mp1);
    };
    int l = 1, r = n;
    int mid = l + r >> 1;
    reverse(a.begin() + mid + 1, a.end());
    auto [L0, L1] = get(1, mid);
    auto [R0, R1] = get(mid + 1, r);
    ll ans = 0;
    for(auto [x, c] : L0) {
        int need = x == 0 ? 0 : m - x;
        if(R0.contains(need)) {
            ans += 1LL * c * R0[need];
        }
        if(R1.contains(need)) {
            ans += 1LL * c * R1[need];
        }
    }
    for(auto [x, c] : R0) {
        int need = x == 0 ? 0 : m - x;
        if(L1.contains(need)) {
            ans += 1LL * c * L1[need];
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
