#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> pos(n);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    vector<int> b(n + 1, -1);
    vector<int> L(n), R(n);
    auto dfs = [&](this auto &&self, int l, int r, int x) -> void {
        if(x >= n) return;
        int p = pos[x];
        if(l < p && p < r) {
            L[x] = l;
            R[x] = r;
            self(l, r, x + 1);
        } else {
            b[p] = x;
            L[x] = p;
            R[x] = p;
            self(min(l, p), max(r, p), x + 1);
        }
    };
    dfs(inf, -inf, 0);
    int ans = 1;
    for(int i = 0; i < n; i++) {
        int l = L[i], r = R[i];
        if(l != r) {
            ans = 1LL * ans * (r - l + 1 - i) % MOD;
        }
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
