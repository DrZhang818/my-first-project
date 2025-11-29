#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void chmax(ll &x, ll y) {
    if(x < y) {
        x = y;
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> w(n + 1), v(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> w[i] >> v[i];
    }

    int q;
    cin >> q;
    vector<int> L(q + 1), R(q + 1), C(q + 1);
    vector<ll> ans(q + 1);
    for(int i = 1; i <= q; i++) {
        cin >> L[i] >> R[i] >> C[i];
    }
    int mx = *max_element(C.begin() + 1, C.end());
    vector<int> p(q + 1);
    iota(p.begin(), p.end(), 0);
    auto dfs = [&](auto &&self, int al, int ar, int ql, int qr) -> void {
        int am = al + ar >> 1;
        vector dpl(am - al + 3, vector<ll>(mx + 1));
        vector dpr(ar - am + 1, vector<ll>(mx + 1));
        for(int i = am; i >= al; i--) {
            int id = i - al + 1;
            dpl[id] = dpl[id + 1];
            for(int j = 0; j + w[i] <= mx; j++) {
                chmax(dpl[id][j + w[i]], dpl[id + 1][j] + v[i]);
            }
        }
        for(int i = am + 1; i <= ar; i++) {
            int id = i - am;
            dpr[id] = dpr[id - 1];
            for(int j = 0; j + w[i] <= mx; j++) {
                chmax(dpr[id][j + w[i]], dpr[id - 1][j] + v[i]);
            }
        }
        int tl = ql - 1, tr = qr + 1;
        for(int i = ql; i < tr; i++) {
            if(R[p[i]] < am) {
                swap(p[i], p[++tl]);
                if(i != tl) i--;
            } else if(L[p[i]] > am + 1) {
                swap(p[i], p[--tr]);
                if(i != tr) i--;
                else break;
            }
        }
        for(int i = tl + 1; i < tr; i++) {
            int l = L[p[i]], r = R[p[i]], c = C[p[i]];
            l = l - al + 1;
            r = r - am;
            for(int j = 0; j <= c; j++) {
                chmax(ans[p[i]], dpl[l][j] + dpr[r][c - j]); 
            }
        }
        if(tl >= ql) self(self, al, am, ql, tl);
        if(tr <= qr) self(self, am + 1, ar, tr, qr);
    };
    dfs(dfs, 1, n, 1, q);
    for(int i = 1; i <= q; i++) {
        cout << ans[i] << "\n";
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
