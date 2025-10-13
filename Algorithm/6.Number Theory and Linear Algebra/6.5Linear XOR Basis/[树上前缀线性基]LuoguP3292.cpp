#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class XorBasis {
    vector<ll> b;

    int num;
    ll _or;
    
    bool canBeZero;
    vector<ll> basis;

    vector<int> rightMost;
    int rightMostZero;
public:
    XorBasis(vector<ll> &a) {
        b.resize(64);
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
        b.resize(64);
        rightMost.resize(b.size(), 0);
        rightMostZero = -1;
        num = 0;
        _or = 0;
        canBeZero = false;
    }
    bool insert(ll v) {
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
    bool insertRightMost(int idx, ll v) {
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
    bool decompose(ll v) {
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
    ll maxXor() {
        ll res = 0;
        for(int i = b.size() - 1; i >= 0; i--) {
            res = max(res, res ^ b[i]);
        }
        return res;
    }
    ll maxXorWithVal(ll v) {
        ll res = v;
        for(int i = b.size() - 1; i >= 0; i--) {
            res = max(res, res ^ b[i]);
        }
        return res;
    }
    ll maxXorWithLowerIndex(int lowerIndex) {
        ll res = 0;
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(res >> i & 1) && rightMost[i] >= lowerIndex) {
                res = max(res, res ^ b[i]);
            }
        }
        return res;
    }
    ll minXor() {
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
        vector<ll> tmp = b;
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
    ll kthXor(ll k) {
        initOnce();
        if(canBeZero) {
            k--;
        }
        if(k >= (1LL << basis.size())) {
            return -1;
        }
        ll _xor = 0;
        for(int i = 0; i < basis.size(); i++) {
            if(k >> i & 1) {
                _xor ^= basis[i];
            }
        }
        return _xor;
    }
    XorBasis get(int lowerIndex) {
        XorBasis res;
        for(int i = b.size() - 1; i >= 0; i--) {
            if(rightMost[i] >= lowerIndex) {
                res.insert(b[i]);
            }
        }
        return res;
    }
    void merge(const XorBasis& other) {
        for(int i = other.b.size() - 1; i >= 0; i--) {
            ll v = other.b[i];
            if(v > 0) {
                insert(v);
            }
        }
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }   
    vector<vector<int>> adj(n + 1); 
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> dep(n + 1), son(n + 1), p(n + 1), sz(n + 1, 1);
    auto dfs1 = [&](this auto &&self, int u, int fa) -> void {
        dep[u] = dep[fa] + 1;
        p[u] = fa;
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            sz[u] += sz[v];
            if(son[u] == 0 || sz[son[u]] < sz[v]) {
                son[u] = v;
            }
        }
    };
    dfs1(1, 0);
    vector<int> top(n + 1);
    auto dfs2 = [&](this auto &&self, int u, int t) -> void {
        top[u] = t;
        if(son[u] == 0) {
            return;
        }
        self(son[u], t);
        for(int v : adj[u]) {
            if(v == p[u] || v == son[u]) continue;
            self(v, v);
        }
    };
    dfs2(1, 1);
    auto LCA = [&](int u, int v) -> int {
        while(top[u] != top[v]) {
            if(dep[top[u]] < dep[top[v]]) {
                swap(u, v);
            }
            u = p[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    };
    vector<XorBasis> b(n + 1);
    auto work = [&](this auto &&self, int u) -> void {
        b[u].insertRightMost(dep[u], a[u]);
        for(int v : adj[u]) {
            if(v == p[u]) continue;
            b[v] = b[u];
            self(v);
        }
    };
    work(1);
    while(q--) {
        int u, v;
        cin >> u >> v;
        int d = dep[LCA(u, v)];
        XorBasis cur = b[u].get(d);
        cur.merge(b[v].get(d));
        cout << cur.maxXor() << "\n";
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
