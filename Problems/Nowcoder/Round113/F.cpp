#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

template<class Info>
struct LazySegmentTree {
    int n;
    vector<Info> info;
    LazySegmentTree() : n(0) {}
    LazySegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    LazySegmentTree(vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(vector(n_, v_));
    }
    template<class T>
    void init(vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        auto build = [&](auto &&self, int o, int l, int r) {
            if(l == r) {
                info[o] = init_[l];
                return;
            }
            int m = l + r >> 1;
            self(self, o << 1, l, m);
            self(self, o << 1 | 1, m + 1, r);
            pull(o);
        };
        build(build, 1, 0, n - 1);
    }
    void pull(int o) {
        info[o] = info[o << 1] + info[o << 1 | 1];
    }
    
    void modify(int o, int l, int r, int x, const Info &v) {
        if(l == r) {
            info[o] = v;
            return ;
        }
        int m = l + r >> 1;
        if(x <= m) {
            modify(o << 1, l, m, x, v);
        } else {
            modify(o << 1 | 1, m + 1, r, x, v);
        }
        pull(o);
    }
    void modify(int x, const Info &v) {
        modify(1, 0, n - 1, x, v);
    }
    Info rangeQuery(int o, int l, int r, int x, int y) {
        if(l > y || r < x) {
            return Info();
        }
        if(x <= l && r <= y) {
            return info[o];
        }
        int m = l + r >> 1;
        return rangeQuery(o << 1, l, m, x, y) + rangeQuery(o << 1 | 1, m + 1, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n - 1, l, r);
    }
};
struct Info {
    ll sum = 0;
    array<int,12> cnt {}, scnt {};
};

vector<int> fac;
Info operator + (const Info &l, const Info &r) {
    Info res;
    res.sum = l.sum + r.sum;
    res.cnt = l.cnt;
    res.scnt = l.scnt;
      for(int i = 0; i < 12; i++) {
        res.cnt[i] += r.cnt[i];
        res.scnt[i] += r.scnt[i];
        res.sum += 1LL * l.cnt[i] * r.scnt[11 - i];
    }
    return res;
}


void solve() {
    int n, q;
    cin >> n >> q;
    std::vector<int> a(n + 1);
    LazySegmentTree<Info> seg(n + 1);

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        Info cur;
        bool ok = true;
        for(int j = 0; j < 12; j++) {
            int d = fac[j];
            if(a[i] % d == 0) {
                if(ok) {
                    cur.cnt[j]++;
                    ok = false;
                }
                cur.scnt[j]++;
            }
        }
        seg.modify(i, cur);
    }
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int x, y;
            cin >> x >> y;
            a[x] = y;
            Info cur;
            bool ok = true;
            for(int i = 0; i < 12; i++) {
                int d = fac[i];
                if(y % d == 0) {
                    if(ok) {
                        cur.cnt[i]++;
                        ok = false;
                    }
                    cur.scnt[i]++;
                }
            }
            seg.modify(x, cur);
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.rangeQuery(l, r).sum << "\n";
        }
    }
    

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 1; i * i <= 495; i++) {
        if(495 % i == 0) {
            fac.push_back(i);
            if(i * i != 495) {
                fac.push_back(495 / i);
            }
        }
    }
    sort(fac.begin(), fac.end(), greater<int>());
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
