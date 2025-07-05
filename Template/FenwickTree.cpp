inline int lowbit(int o) { return o & -o; }
class FenwickTree {
private:
    int n;
    vector<int> tr;
public:
    FenwickTree(int x) : n(x), tr(x + 1) {}
    void add(int o, int x) {
        for(; o <= n; o += lowbit(o)) {
            tr[o] += x;
        }
    }
    ll query(int o) {
        ll res = 0;
        for(; o > 0; o -= lowbit(o)) {
            res += tr[o];
        }
        return res;
    }
    ll range_query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

