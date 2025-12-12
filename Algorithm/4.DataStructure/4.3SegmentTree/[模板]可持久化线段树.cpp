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
            nodes[u].info = v;

            //需要累加时这样写
            //nodes[u].info = nodes[u].info + v;
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