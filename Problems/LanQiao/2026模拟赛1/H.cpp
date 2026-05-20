#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

struct Info {
    int mn = inf;
};

Info operator+(const Info& a, const Info& b) {
    return {min(a.mn, b.mn)};
}

struct LazysegmentTree {
    int n;
    vector<Info> info;
    LazysegmentTree(int n) : n(n), info(4 << __lg(n)) {}

    void pull(int o) { info[o] = info[o << 1] + info[o << 1 | 1]; }

    void modify(int o, int l, int r, int x, const Info& v) {
        if(l == r) { info[o] = v; return; }
        int m = l + r >> 1;
        if(x <= m) modify(o << 1, l, m, x, v);
        else modify(o << 1 | 1, m + 1, r, x, v);
        pull(o);
    }
    void modify(int x, const Info& v) { modify(1, 0, n - 1, x, v); }

    Info rangeQuery(int o, int l, int r, int x, int y) {
        if(l > y || r < x) return Info();
        if(x <= l && r <= y) return info[o];
        int m = l + r >> 1;
        return rangeQuery(o << 1, l, m, x, y) + rangeQuery(o << 1 | 1, m + 1, r, x, y);
    }
    Info rangeQuery(int l, int r) { return rangeQuery(1, 0, n - 1, l, r); }

    template <typename F>
    int findLast(int o, int l, int r, int x, int y, F&& pred) {
        if(l > y || r < x) return -1;
        if(x <= l && r <= y && !pred(info[o])) return -1;
        if(l == r) return l;
        int m = l + r >> 1;
        int res = findLast(o << 1 | 1, m + 1, r, x, y, pred);
        if(res == -1) res = findLast(o << 1, l, m, x, y, pred);
        return res;
    }
    template <typename F>
    int findLast(int l, int r, F&& pred) { return findLast(1, 0, n - 1, l, r, pred); }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    auto val = a;
    sort(val.begin() + 1, val.end());
    val.erase(unique(val.begin() + 1, val.end()), val.end());

    vector<int> id(n + 1);
    vector<vector<int>> pos(n + 1);
    vector<int> cur(n + 1);
    for(int i = 1; i <= n; i++) {
        a[i] = lower_bound(val.begin() + 1, val.end(), a[i]) - val.begin();
        pos[a[i]].push_back(i);
    }

    LazysegmentTree seg(n + 1);

    for(int i = 1; i <= n; i++) {
        if(!pos[i].empty()) {
            seg.modify(i, { pos[i][0] });
        }
    }

    auto upd = [&](int p, int i) {
        while(cur[p] < pos[p].size() && pos[p][cur[p]] <= i) {
            cur[p]++;
        }
        if(cur[p] == pos[p].size()) {
            seg.modify(p, {inf});
        } else {
            seg.modify(p, {pos[p][cur[p]]});
        }
    };

    vector<int> ans(n + 1, -1);
    for(int i = 1; i <= n; i++) {
        int p = seg.findLast(1, n, [&](const auto& info) {
            return info.mn - i <= k;
        });
        if(p != -1) {
            k -= pos[p][cur[p]] - i;
            ans[i] = val[p];
            cur[p]++;
            seg.modify(p, {inf});
        }

        if(a[i] != p) {
            upd(a[i], i);
        }

        if(ans[i - 1] != -1) {
            int las = lower_bound(val.begin() + 1, val.end(), ans[i - 1]) - val.begin();
            upd(las, i);
        }
    }

    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}