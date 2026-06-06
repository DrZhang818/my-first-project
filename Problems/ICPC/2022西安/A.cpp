#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename Policy>
struct FHQ {
    using Val = typename Policy::Val;
    using Info = typename Policy::Info;

    struct Node {
        int l = 0, r = 0, fa = 0;
        int sz = 1;
        unsigned int pri = 0;

        Val val{};
        Info info{};
    };

    vector<Node> tr;

    FHQ(int n = 0) {
        tr.reserve(n + 1);
        tr.push_back(Node{});
        tr[0].sz = 0;
        tr[0].info = Policy::identity();
    }

    int newNode(const Val& v) {
        tr.push_back(Node{});
        int u = int(tr.size()) - 1;

        tr[u].l = tr[u].r = tr[u].fa = 0;
        tr[u].sz = 1;
        tr[u].pri = rng();
        tr[u].val = v;
        tr[u].info = Policy::make(v);

        return u;
    }

    int size(int u) const {
        return u ? tr[u].sz : 0;
    }

    Info info(int u) const {
        return u ? tr[u].info : Policy::identity();
    }

    void setFa(int u, int fa) {
        if(u) tr[u].fa = fa;
    }

    void pull(int u) {
        if(!u) return; 
        tr[u].sz = size(tr[u].l) + size(tr[u].r) + 1;
        tr[u].info = Policy::merge(
            Policy::merge(info(tr[u].l), Policy::make(tr[u].val)),
            info(tr[u].r)
        );

        setFa(tr[u].l, u);
        setFa(tr[u].r, u);
    }

    void pullPath(int u) {
        for(int x = u; x; x = tr[x].fa) {
            pull(x);
        }
    }

    pair<int,int> split(int u, int k) {
        if(!u) return {0, 0};

        if(size(tr[u].l) >= k) {
            auto [x, y] = split(tr[u].l, k);
            tr[u].l = y;
            pull(u);

            setFa(x, 0);
            setFa(u, 0);
            return {x, u};
        } else {
            auto [x, y] = split(tr[u].r, k - size(tr[u].l) - 1);
            tr[u].r = x;
            pull(u);

            setFa(u, 0);
            setFa(y, 0);
            return {u, y};
        }
    }

    int merge(int u, int v) {
        if(!u || !v) {
            int rt = u | v;
            setFa(rt, 0);
            return rt;
        }

        if(tr[u].pri > tr[v].pri) {
            tr[u].r = merge(tr[u].r, v);
            pull(u);
            setFa(u, 0);
            return u;
        } else {
            tr[v].l = merge(u, tr[v].l);
            pull(v);
            setFa(v, 0);
            return v;
        }
    }

    int getRoot(int u) const {
        while(tr[u].fa) {
            u = tr[u].fa;
        }
        return u;
    }

    int getRank(int u) {
        int res = size(tr[u].l) + 1;

        while(tr[u].fa) {
            int f = tr[u].fa;
            if(tr[f].r == u) {
                res += size(tr[f].l) + 1;
            }
            u = f;
        }

        return res;
    }

    pair<int,int> splitAfterNode(int u) {
        int rt = getRoot(u);
        int rk = getRank(u);
        return split(rt, rk);
    }

    void setValue(int u, const Val& v) {
        tr[u].val = v;
        pullPath(u);
    }
};

struct Policy {
    struct Val {
        int col = 0;
        int L = 0;
        int R = 0;
    };
    struct Info {
        int last = 0;
    };

    static Info identity() { 
        return {0}; 
    }
    static Info make(const Val& v) {
        return {v.col};
    }
    static Info merge(const Info& lhs, const Info& rhs) {
        if(rhs.last == 0) return lhs;
        return rhs;
    }
};  

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    FHQ<Policy> fhq(n + 2 * q + 5);
    vector<map<int,int>> seg(n + 1);

    auto addSeg = [&](int col, int L, int R) {
        int u = fhq.newNode({col, L, R});
        seg[col][L] = u;
        return u;
    };

    auto findSeg = [&](int col, int pos) {
        auto it = seg[col].upper_bound(pos);
        --it;
        return it->second;
    };

    auto cut = [&](int x, int pos) -> pair<int,int> {
        auto [col, L, R] = fhq.tr[x].val;

        fhq.setValue(x, {col, L, pos});
        int y = addSeg(col, pos, R);

        auto [a, b] = fhq.splitAfterNode(x);

        return {a, fhq.merge(y, b)};
    };

    vector<int> bel(n + 1);

    for(int i = 1; i <= n; i++) {
        bel[i] = addSeg(i, 1, m + 2);
    }

    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int a, pos;
            cin >> a >> pos;

            int x = findSeg(a, pos);
            int y = findSeg(a + 1, pos);

            auto [x0, x1] = cut(x, pos);
            auto [y0, y1] = cut(y, pos);

            fhq.merge(x0, y1);
            fhq.merge(y0, x1);
        } else {
            int a;
            cin >> a;

            int rt = fhq.getRoot(bel[a]);
            cout << fhq.tr[rt].info.last << "\n";
        }
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