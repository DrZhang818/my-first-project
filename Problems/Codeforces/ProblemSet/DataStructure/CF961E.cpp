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
    PersistentSegmentTree(int n_, int expected_updates = 0) {
        init(n_, expected_updates);
    }

    void init(int n_, int expected_updates = 0) {
        n = n_;
        nodes.clear();
        nodes.reserve(4 * n + (expected_updates > 0 ? expected_updates * (__lg(n) + 2) : 0));
    }

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
        nodes[u].info = nodes[nodes[u].l].info + nodes[nodes[u].r].info;
    }
    int modify(int prev, int l, int r, int x, const Info& v) {
        int u = copyNode(prev);
        if(l == r) {
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
    Info query(int u, int l, int r, int x, int y) {
        if(l > y || r < x || u == 0) {
            return Info();
        }
        if(x <= l && r <= y) {
            return nodes[u].info;
        }
        int mid = l + r >> 1;
        return query(nodes[u].l, l, mid, x, y) + query(nodes[u].r, mid + 1, r, x, y);
    }
    Info query(int u, int x, int y) {
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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> val(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        val[i] = a[i];
    }

    PersistentSegmentTree<Info> seg(n, n);
    vector<int> roots(n + 1);
    roots[0] = seg.build();

    ll ans = 0;
    for(int x = 1; x <= n; x++) {
        int y = min(a[x], x - 1);
        ans += y - seg.query(roots[y], 1, n, 1, x - 1).cnt;
        roots[x] = seg.modify(roots[x - 1], 1, n, min(a[x], n), {1});
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
