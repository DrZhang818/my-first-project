#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

struct info {
    int l, r, id;
    friend bool operator < (const info &a, const info &b) {
        return a.r < b.r;
    }
};

void solve() {
    int n;
    cin >> n;
    int ans = 0;
    vector<vector<int>> adj(n + 1);
    vector<info> a(n + 1);
    vector<int> posR;
    for(int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        int l = inf, r = -inf;
        for(int j = 0; j < k; j++) {
            int x;
            cin >> x;
            adj[i].push_back(x);
            l = min(l, x);
            r = max(r, x);
        }
        a[i] = {l, r, i};
        posR.push_back(r);
        if(k == 1) {
            ans += 1;
        } else {
            ans += 2;
        }
    }
    sort(posR.begin(), posR.end());
    sort(a.begin() + 1, a.end());
    auto b = a;
    sort(b.begin() + 1, b.end(), 
        [&](auto x, auto y) {
            return x.l < y.l;
        });
    int Lid = 1;
    int mnR = inf, mxL = 0, R = 0;
    for(auto [l, r, id] : a) {
        if(l <= R) {
            continue;
        }
        if(l == r) {
            R = r;
            continue;
        }
        while(Lid <= n && b[Lid].l < r) {
            Lid++;
        }
        int mnR = *upper_bound(posR.begin(), posR.end(), l);
        mxL = b[Lid - 1].l;
        bool ok = false;
        for(int x : adj[id]) {
            if(mxL <= x && x <= mnR) {
                ok = true;
                break;
            }
        }
        if(ok) {
            ans--;
            R = r;
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
