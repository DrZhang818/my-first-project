#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int query(int l, int r) {
    cout << "? " << l << " " << r << endl;
    int res;
    cin >> res;
    return res;
}

void answer(int x) {
    cout << "! " << x << endl;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> R(n + 1);
    while(q--) {
        int l, r;
        cin >> l >> r;
        R[l] = max(R[l], r);
    }
    vector<array<int,2>> Q;
    for(int l = 1; l <= n; l++) {
        int r = R[l];
        if(r == 0) {
            continue;
        }
        if(Q.empty() || r > Q.back()[1]) {
            Q.push_back({l, r});
        }
    }
    int lo = -1, hi = Q.size();
    while(lo + 1 < hi) {
        int mid = lo + hi >> 1;
        auto [l, r] = Q[mid];
        if(query(l, n) < query(1, r)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    int ans = 0;
    if(hi < Q.size()) {
        auto [l, r] = Q[hi];
        ans = max(ans, query(l, r));
    }
    if(hi > 0) {
        auto [l, r] = Q[hi - 1];
        ans = max(ans, query(l, r));
    }
    answer(ans);
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
