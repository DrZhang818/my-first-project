#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr i64 inf = 1E18;

using T = pair<i64, int>;

struct State {
    T a[4];
    State() {
        for(int i = 0; i < 4; i++) {
            a[i] = {-inf, -1 - i};
        }
    }
};

State merge(const State& x, const State& y) {
    State res;
    T tmp[8];
    for(int i = 0; i < 4; i++) {
        tmp[i] = x.a[i];
        tmp[i + 4] = y.a[i];
    }
    sort(tmp, tmp + 8, greater());

    int sz = 0;
    for(int i = 0; i < 8 && sz < 4; i++) {
        bool ok = true;
        for(int j = 0; j < sz; j++) {
            if(res.a[j].second == tmp[i].second) {
                ok = false;
                break;
            }
        }
        if(ok) {
            res.a[sz++] = tmp[i];
        }
    }

    return res;
}

State newState(int type, i64 val) {
    State res;
    res.a[0] = {val, type};
    return res;
}

struct SegmentTree {
    int n;
    vector<State> tree;
    SegmentTree(int n) : n(n), tree(n << 1) {}

    void build() {
        for(int i = n - 1; i > 0; i--) {
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    void update(int o, State v) {
        for(tree[o += n] = v; o > 1; o >>= 1) {
            tree[o >> 1] = merge(tree[o], tree[o ^ 1]);
        }
    }

    State rangeQuery(int l, int r) {
        State resL, resR;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) resL = merge(resL, tree[l++]);
            if(r & 1) resR = merge(tree[--r], resR);
        }
        return merge(resL, resR);
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> K(n);
    vector<i64> A(n);
    vector<vector<int>> pos(n);

    for(int i = 0; i < n; i++) {
        cin >> K[i] >> A[i];
        --K[i];
        pos[K[i]].push_back(i);
    }

    vector<State> pre(n + 1), suf(n + 1);

    for(int i = 0; i < n; i++)      pre[i + 1] = merge(pre[i],      newState(K[i], A[i]));
    for(int i = n - 1; i >= 0; i--) suf[i]     = merge(suf[i + 1],  newState(K[i], A[i]));

    vector<i64> default_val(n);
    vector<vector<pair<int,i64>>> patches(n);

    for(int i = 0; i < n; i++) {
        vector<T> cands;
        for(int j = 0; j < 4; j++) {
            if(pre[i].a[j].second != K[i]) cands.push_back(pre[i].a[j]);
        }

        default_val[i] = A[i] + cands[0].first + cands[1].first;

        if(cands[0].second >= 0) {
            patches[cands[0].second].push_back({i, A[i] + cands[1].first + cands[2].first});
        }
        if(cands[1].second >= 0) {
            patches[cands[1].second].push_back({i, A[i] + cands[0].first + cands[2].first});
        }
    }

    SegmentTree seg(n);
    for(int i = 0; i < n; i++) {
        seg.tree[n + i] = newState(K[i], default_val[i]);
    }
    seg.build();

    i64 ans = -1;

    for(int x = 0; x < n; x++) {
        for(auto [idx, val] : patches[x]) {
            seg.update(idx, newState(K[idx], val));
        }
        for(int i4 : pos[x]) {
            State best_i3 = seg.rangeQuery(0, i4);
            for(auto [pre_val, y] : best_i3.a) {
                if(y == x || pre_val < 0) continue;
                i64 sum = pre_val + A[i4];
                int cnt = 0;
                for(int j = 0; j < 4; j++) {
                    auto [suf_val, z] = suf[i4 + 1].a[j];
                    if(z != x && z != y) {
                        sum += suf_val;
                        if(++cnt == 2) break;
                    }
                }
                ans = max(ans, sum);
            }
        }
        for(auto [idx, val] : patches[x]) {
            seg.update(idx, newState(K[idx], default_val[idx]));
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
