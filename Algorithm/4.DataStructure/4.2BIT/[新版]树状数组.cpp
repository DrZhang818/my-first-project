inline int lowbit(int o) { return o & -o; }
struct FenwickTree {
    int n;
    vector<ll> tr;
    FenwickTree(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        tr.assign(n, {});
    }
    void add(int o, ll x) {
        for(; o < n; o += lowbit(o)) {
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
    ll rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
    int select(ll k) {
        int x = 0;
        ll cur = 0;
        for(int i = 1 << __lg(n); i; i >>= 1) {
            if(x + i < n && cur + tr[x + i] < k) {
                x += i;
                cur += tr[x];
            }
        }
        return x + 1;
    }
};