mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct FHQ {
    struct Node {
        int l = 0, r = 0, v = 0, sz = 0;
        unsigned int p = 0;
    };
    
    vector<Node> tr;
    int root = 0;

    FHQ(int n = 0) {
        tr.reserve(n + 1);
        tr.push_back({0, 0, 0, 0, 0});
    }

    int newNode(int v) {
        tr.push_back({0, 0, v, 1, (unsigned int)rng()});
        return tr.size() - 1;
    }

    void pull(int u) {
        tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + 1;
    }

    void split(int u, int v, int &x, int &y) {
        if(!u) {
            x = y = 0;
            return;
        }
        if(tr[u].v <= v) {
            x = u;
            split(tr[u].r, v, tr[u].r, y);
        } else {
            y = u;
            split(tr[u].l, v, x, tr[u].l);
        }
        pull(u);
    }

    int merge(int u, int v) {
        if(!u || !v) return u | v;
        if(tr[u].p > tr[v].p) {
            tr[u].r = merge(tr[u].r, v);
            pull(u);
            return u;
        } else {
            tr[v].l = merge(u, tr[v].l);
            pull(v);
            return v;
        }
    }

    void add(int v) {
        int x, y;
        split(root, v, x, y);
        root = merge(merge(x, newNode(v)), y);
    }

    void remove(int v) {
        int x, y, z;
        split(root, v, x, z);
        split(x, v - 1, x, y);
        if(y) {
            y = merge(tr[y].l, tr[y].r);
        }
        root = merge(merge(x, y), z);
    }

    int rank(int v) {
        int x, y;
        split(root, v - 1, x, y);
        int res = tr[x].sz + 1;
        root = merge(x, y);
        return res;
    }

    int kth(int k) {
        int u = root;
        while(u) {
            if(tr[tr[u].l].sz + 1 == k) return tr[u].v;
            if(tr[tr[u].l].sz >= k) {
                u = tr[u].l;
            } else {
                k -= tr[tr[u].l].sz + 1;
                u = tr[u].r;
            }
        }
        return -1;
    }

    int prev(int v) {
        int x, y;
        split(root, v - 1, x, y);
        int u = x;
        if(!u) return -inf;
        while(tr[u].r) u = tr[u].r;
        int res = tr[u].v;
        root = merge(x, y);
        return res;
    }

    int next(int v) {
        int x, y;
        split(root, v, x, y);
        int u = y;
        if(!u) return inf;
        while(tr[u].l) u = tr[u].l;
        int res = tr[u].v;
        root = merge(x, y);
        return res;
    }
};