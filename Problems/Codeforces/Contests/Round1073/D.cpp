#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

template<class T> 
constexpr T power(T a, ll b) {
    T res = 1;
    while(b) {
        if(b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

template<int P> 
struct MInt {
    int x;
    constexpr MInt() : x() {}
    constexpr MInt(ll x) : x(norm(x % getMod())) {}

    static int Mod;
    constexpr static int getMod() {
        if(P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if(x < 0) {
            x += getMod();
        }
        if(x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr istream &operator>>(istream &is, MInt &a) {
        ll v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr ostream &operator<<(ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
int MInt<0>::Mod = 998244353;

template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = 998244353;
using Z = MInt<P>;

struct Comb {
    int n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;
    
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }
    
    void init(int m) {
        m = std::min(m, Z::getMod() - 1);
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }
    
    Z fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    Z invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    Z inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    Z binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;

vector<int> p, sz;
int find(int o) { return o == p[o] ? p[o] : p[o] = find(p[o]); }
void merge(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return;
    p[v] = u;
    sz[u] += sz[v];
}

void solve() {  
    int n, m;
    cin >> n >> m;
    vector adj(n + 1, vector<int>{});
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if(u == n || v == n) {
            if(v == n) swap(u, v);
            adj[u].push_back(v);
        } else {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }    
    p.assign(n + 1, 0);
    iota(p.begin(), p.end(), 0);
    sz.assign(n + 1, 1);


    vector<int> vis(n + 1);
    auto dfs = [&](this auto &&self, int u, int fa) -> void {
        vis[u] = true;
        for(int v : adj[u]) {
            if(v == fa) continue;
            merge(u, v);
            self(v, u);
        }
    }; 

    for(int i = 1; i < n; i++) {
        if(!vis[i]) {
            dfs(i, 0);
        }
    }

    vector<int> tag(n + 1);
    int root_siz = 1;
    for(int v : adj[n]) {
        tag[find(v)] = 1;
        root_siz += sz[find(v)];
    }

    int k = n - m;
    Z prod = power(Z(n), P - 1 + k - 3);
    for(int i = 1; i < n; i++) {
        if(find(i) == i && !tag[i]) {
            prod *= sz[i];
        }
    }

    vector<Z> ans(n + 1);
    if(tag[find(n - 1)]) {
        for(int v : adj[n]) {
            if(find(v) == find(n - 1)) {
                ans[v] = prod * root_siz * n;
                break;
            }
        }
    } else {
        for(int v : adj[n]) {
            ans[v] = prod * sz[find(v)] * n;
        }
        for(int i = 1; i < n; i++) {
            if(tag[find(i)]) continue;
            if(find(i) == find(n - 1)) {
                ans[i] = prod * comb.inv(sz[find(i)]) * (root_siz + sz[find(i)]);
            } else {
                ans[i] = prod;
            }
        }
    }

    for(int i = 1; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
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
