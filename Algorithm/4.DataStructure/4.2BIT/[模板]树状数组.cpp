class FenwickTree {
private:
    vector<int> tree;
    int n;
public:
    FenwickTree(int x) {
        tree.resize(x + 1);
        n = x;
    }
    void add(int i, int x) {
        while(i <= n) {
            tree[i] += x;
            i += i & -i;
        }
    }
    int query(int i) {
        int res = 0;
        while(i > 0) {
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }
    int range_query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
