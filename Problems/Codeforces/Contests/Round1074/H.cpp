#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

template<class Info>
struct PersistentSegmentTree {
    struct Node {
        int l = 0, r = 0;
        Info info;
    };
    int n;
    vector<Node> nodes;

    PersistentSegmentTree() : n(0) {}
    PersistentSegmentTree(int n_, int q = 0) {
        init(n_, q);
    }

    void init(int n_, int q = 0) {
        n = n_;
        nodes.clear();
        nodes.reserve(4 * n + (q > 0 ? q * (__lg(n) + 2) : 0));
        nodes.push_back({0, 0, Info()});
    }

    //下标从1开始
    template<class T>
    int build(const vector<T>& init_) {
        auto dfs = [&](auto &&self, int l, int r) -> int {
            int u = newNode();
            if(l == r) {
                if(l < (int)init_.size()) nodes[u].info = init_[l];
                return u;
            }
            int mid = l + r >> 1;
            nodes[u].l = self(self, l, mid);
            nodes[u].r = self(self, mid + 1, r);
            pull(u);
            return u;
        };
        return dfs(dfs, 1, n);
    }
    int build() {
        auto dfs = [&](auto &&self, int l, int r) -> int {
            int u = newNode();
            if(l == r) return u;
            int mid = l + r >> 1;
            nodes[u].l = self(self, l, mid);
            nodes[u].r = self(self, mid + 1, r);
            pull(u);
            return u;
        };
        return dfs(dfs, 1, n);
    }
    int newNode() {
        nodes.push_back({0, 0, Info()});
        return nodes.size() - 1;
    }
    int copyNode(int src) {
        Node tmp = nodes[src];
        nodes.push_back(tmp);
        return nodes.size() - 1;
    }
    void pull(int u) {
        if(u) nodes[u].info = nodes[nodes[u].l].info + nodes[nodes[u].r].info;
    }
    int modify(int prev, int l, int r, int x, const Info& v) {
        int u = copyNode(prev);
        if(l == r) {
            // nodes[u].info = v;

            //需要累加时这样写
            nodes[u].info = nodes[u].info + v;
            return u;
        }
        int mid = l + r >> 1;
        if(x <= mid) {
            nodes[u].l = modify(nodes[prev].l, l, mid, x, v);
        } else {
            nodes[u].r = modify(nodes[prev].r, mid + 1, r, x, v);
        }
        pull(u);
        return u;
    }
    int modify(int prev, int x, const Info& v) {
        return modify(prev, 1, n, x, v);
    }
    Info query(int u, int l, int r, int x, int y) {
        if(!u) return Info();
        if(x <= l && r <= y) {
            return nodes[u].info;
        }
        int mid = l + r >> 1;
        if(y <= mid) {
            return query(nodes[u].l, l, mid, x, y);
        }
        if(x > mid) {
            return query(nodes[u].r, mid + 1, r, x, y);
        }
        return query(nodes[u].l, l, mid, x, y) + query(nodes[u].r, mid + 1, r, x, y);
    }
    Info query(int u, int x, int y) {
        if(y < x) {
            return Info();
        }
        return query(u, 1, n, x, y);
    }
    template<class F>
    int findFirst(int u, int l, int r, int x, int y, F&& pred) {
        if(l > y || r < x || u == 0 || !pred(nodes[u].info)) {
            return -1;
        }
        if(l == r) {
            return l;
        }
        int mid = l + r >> 1;
        int res = findFirst(nodes[u].l, l, mid, x, y, pred);
        if(res == -1) {
            res = findFirst(nodes[u].r, mid + 1, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int u, int x, int y, F&& pred) {
        return findFirst(u, 1, n, x, y, pred);
    }
};

struct Info {
    int cnt = 0;
};

Info operator+(const Info& a, const Info& b) {
    return {a.cnt + b.cnt};
}

void solve() {  
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    vector<ll> f(n + 1);
    for(int i = 0; i < n; i++) {
        f[i] = pre[i] - a[i + 1];
    }

    vector<ll> val(2 * n + 1);
    for(int i = 1; i <= n; i++) {
        val[i] = -a[i];
        val[i + n] = f[i - 1];
    }

    val.push_back(0);
    sort(val.begin() + 1, val.end());
    val.erase(unique(val.begin() + 1, val.end()), val.end());
    int m = val.size() - 1;

    PersistentSegmentTree<Info> seg(m, n);
    vector<int> root(n + 1);
    for(int i = 1; i <= n; i++) {
        auto pos = lower_bound(val.begin() + 1, val.end(), f[i - 1]) - val.begin();
        root[i] = seg.modify(root[i - 1], pos, {1});
    }    

    auto cal = [&](int l, int r, int pos) -> int {
        return seg.query(root[r + 1], 1, pos - 1).cnt - seg.query(root[l], 1, pos - 1).cnt;
    };

    auto p0 = lower_bound(val.begin() + 1, val.end(), 0) - val.begin();

    for(int x = 1; x <= n; x++) {
        int ans = 0;
        int lo = x - 1, hi = n + 1;
        while(lo + 1 < hi) {
            int m = lo + hi >> 1;
            if(pre[m] >= 2 * a[x]) {
                hi = m;
            } else {
                lo = m;
            }
        }
        int p = hi;
        lo = x - 1, hi = p;
        while(lo + 1 < hi) {
            int m = lo + hi >> 1;
            if(cal(m, n - 1, p0) <= k) { 
                hi = m;
            } else {
                lo = m;
            }
        }
        ans += p - hi;
        lo = p - 1, hi = n + 1;
        while(lo + 1 < hi) {
            int m = lo + hi >> 1;
            if(cal(m, n - 1, p0) <= k - 1) {
                hi = m;
            } else {
                lo = m;
            }
        }
        ans += n - hi + 1;

        int nk = k - cal(x, n - 1, p0);
        auto v = lower_bound(val.begin() + 1, val.end(), -a[x]) - val.begin();
        lo = 0, hi = x;
        while(lo + 1 < hi) {
            int m = lo + hi >> 1;
            if(pre[m - 1] >= a[x]) {
                hi = m;
            } else {
                lo = m;
            }
        }
        p = hi;
        lo = 0, hi = p;
        while(lo + 1 < hi) {
            int m = lo + hi >> 1;
            if(cal(m - 1, x - 2, v) <= nk) {
                hi = m;
            } else {
                lo = m;
            }
        }
        ans += p - hi;
        lo = p - 1, hi = x;
        while(lo + 1 < hi) {
            int m = lo + hi >> 1;
            if(cal(m - 1, x - 2, v) <= nk - 1) {
                hi = m;
            } else {
                lo = m;
            }
        }
        ans += x - hi;
        cout << ans << " \n"[x == n];
    }   
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
