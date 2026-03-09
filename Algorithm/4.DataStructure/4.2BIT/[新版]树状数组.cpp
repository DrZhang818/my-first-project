inline int lowbit(int o) { return o & -o; }
template<typename T>
struct FenwickTree {
    int n;
    vector<T> tr;
    FenwickTree(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        tr.assign(n, {});
    }
    void add(int o, T x) {
        for(; o < n; o += lowbit(o)) {
            tr[o] += x;
        }
    }
    T query(int o) {
        T res = 0;
        for(; o > 0; o -= lowbit(o)) {
            res += tr[o];
        }
        return res;
    }
    T rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
    int select(T k) {
        int x = 0;
        T cur = 0;
        for(int i = 1 << __lg(n); i; i >>= 1) {
            if(x + i < n && cur + tr[x + i] < k) {
                x += i;
                cur += tr[x];
            }
        }
        return x + 1;
    }
};