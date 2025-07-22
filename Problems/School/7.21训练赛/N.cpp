#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int l, r;
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<info> a(m);
    for(int i = 0; i < m; i++) {
        cin >> a[i].l >> a[i].r;
    }
    int q;
    cin >> q;
    vector<int> Q(q + 1);
    for(int i = 1; i <= q; i++) {
        cin >> Q[i];
    }
    auto ck = [&](int x) -> bool {
        vector<int> pre(n + 1, -1);
        for(int i = 1; i <= x; i++) {
            pre[Q[i]] = 1;
        }
        for(int i = 1; i <= n; i++) {
            pre[i] += pre[i - 1];
        }
        for(auto [l, r] : a) {
            if(pre[r] - pre[l - 1] > 0) {
                return true;
            }
        }
        return false;
    };
    int l = 0, r = q + 1; 
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << (r == q + 1 ? -1 : r) << "\n";
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
