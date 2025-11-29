#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = ll(1E18);

template<class Info>
struct FenwickTree {
    int n;
    vector<Info> tr;
    FenwickTree() {}
    FenwickTree(int n) {
        this->n = n;
        tr.assign(n, Info());
    }
    void add(int o, Info x) {
        for(; o < n; o += o & -o) {
            tr[o] = tr[o] + x;
        }
    }
    Info query(int o) {
        Info res;
        for(; o > 0; o -= o & -o) {
            res = res + tr[o];
        }
        return res;
    }
};

struct Info {
    ll val = inf;
};
Info operator + (const Info &l, const Info &r) {
    return {min(l.val, r.val)};
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<array<int,3>> Line(m);
    for(int i = 0; i < m; i++) {
        cin >> Line[i][0] >> Line[i][1] >> Line[i][2];
    }
    sort(Line.begin(), Line.end());
    FenwickTree<Info> fen(n + 1);
    fen.add(n, {0});
    int i = 1;
    for(auto [l, r, c] : Line) {
        i = max(i, l);
        ll w = fen.query(n - i + 1).val;
        fen.add(n - r + 1, {w + c});
    }
    ll ans = fen.query(1).val;
    if(ans == inf) {
        cout << -1 << "\n";
        return;
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
