#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class XorBasis {
    vector<int> b;

    int num;
    ll _or;
    
    bool canBeZero;
    vector<ll> basis;

    vector<int> rightMost;
    int rightMostZero;
public:
    XorBasis(vector<int> &a) {
        b.resize(32);
        rightMost.resize(b.size(), 0);
        rightMostZero = -1;
        num = 0;
        _or = 0;
        canBeZero = false;

        for(ll v : a) {
            insert(v);
        }
    };
    XorBasis() {
        b.resize(32);
        rightMost.resize(b.size(), 0);
        rightMostZero = -1;
        num = 0;
        _or = 0;
        canBeZero = false;
    }
    bool insert(int v) {
        _or |= v;
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                b[i] = v;
                num++;
                return true;
            }
            v ^= b[i];
        }
        canBeZero = true;
        return false;
    }
    bool insertRightMost(int idx, int v) {
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                b[i] = v;
                rightMost[i] = idx;
                num++;
                return true;
            }
            if(idx > rightMost[i]) {
                swap(idx, rightMost[i]);
                swap(v, b[i]);
            }
            v ^= b[i];
        }
        canBeZero = true;
        rightMostZero = max(rightMostZero, idx);
        return false;
    }
    bool decompose(int v) {
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                return false;
            }
            v ^= b[i];
        }
        return true;
    }
    int maxXor() {
        int res = 0;
        for(int i = b.size() - 1; i >= 0; i--) {
            res = max(res, res ^ b[i]);
        }
        return res;
    }
    int maxXorWithVal(int v) {
        int res = v;
        for(int i = b.size() - 1; i >= 0; i--) {
            res = max(res, res ^ b[i]);
        }
        return res;
    }
    int maxXorWithLowerIndex(int lowerIndex) {
        int res = 0;
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(res >> i & 1) && rightMost[i] >= lowerIndex) {
                res = max(res, res ^ b[i]);
            }
        }
        return res;
    }
    int minXor() {
        if(canBeZero) {
            return 0;
        }
        for(int i = 0; i < b.size(); i++) {
            if(b[i] > 0) {
                return b[i];
            }
        }
        return -1; //基为空
    }
    void initOnce() {
        if(!basis.empty()) {
            return;
        }
        vector<int> tmp = b;
        for(int i = 0; i < tmp.size(); i++) {
            if(tmp[i] == 0) {
                continue;
            }
            for(int j = i - 1; j >= 0; j--) {
                if(tmp[i] >> j & 1) {
                    tmp[i] ^= tmp[j];
                }
            }
            basis.push_back(tmp[i]);
        }
    }
    int kthXor(int k) {
        initOnce();
        if(canBeZero) {
            k--;
        }
        if(k >= (1LL << basis.size())) {
            return -1;
        }
        int _xor = 0;
        for(int i = 0; i < basis.size(); i++) {
            if(k >> i & 1) {
                _xor ^= basis[i];
            }
        }
        return _xor;
    }
    void merge(const XorBasis& other) {
        for(int i = other.b.size() - 1; i >= 0; i--) {
            int v = other.b[i];
            if(v > 0) {
                insert(v);
            }
        }
    }
};

inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; }

class SegmentTree {
private:
    int n;
    vector<XorBasis> tr;
public:
    SegmentTree(int x) : n(x), tr(x << 2) {}
    void add(int k, int o, int l, int r, int x) {
        tr[o].insert(x);
        if(l == r) {
            return;
        }
        int mid = l + r >> 1;
        if(k <= mid) add(k, ls(o), l, mid, x);
        else add(k, rs(o), mid + 1, r, x);
    } 
    XorBasis get(int L, int R, int o, int l, int r) {
        if(L <= l && r <= R) {
            return tr[o];
        }
        XorBasis b;
        int mid = l + r >> 1;
        if(L <= mid) b.merge(get(L, R, ls(o), l, mid));
        if(R > mid) b.merge(get(L, R, rs(o), mid + 1, r));
        return b;
    }
    void add(int k, int x) {
        add(k, 1, 1, n, x);
    }
    int query(int L, int R) {
        XorBasis b = get(L, R, 1, 1, n);
        return b.maxXor();
    }
};

void solve() {
    int n, q;
    cin >> q >> n;

    SegmentTree tr(n + 1);

    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int k, x;
            cin >> k >> x;
            tr.add(k, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << tr.query(l, r) << "\n";
        }
    }
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
