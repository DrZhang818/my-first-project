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
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
 
template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(ll x) : x{norm(x % getMod())} {}
    
    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
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
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        ll v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
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
int MInt<0>::Mod = 1;
 
template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();
 
constexpr int P = 1000000007;
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

void fwht(vector<Z>& a, auto merge) {
    int n = a.size();
    for(int i = 1; i < n; i <<= 1) {
        for(int j = 0; j < n; j += i << 1) {
            for(int k = 0; k < i; k++) {
                merge(a[j + k], a[j + i + k]);
            }
        }
    }
}

void solve() {  
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> b(k + 1);
    for(int i = 1; i <= k; i++) {
        cin >> b[i];
    }

    vector<int> xb;
    for(int i = 1; i <= k; i++) {
        int cur = b[i];
        for(int e : xb) {
            cur = min(cur, cur ^ e);
        }
        if(cur) {
            xb.push_back(cur);
            sort(xb.begin(), xb.end(), greater());
        }
    }

    int d = xb.size();

    const Z inv2d = Z(1 << d).inv();

    auto getRem = [&](int x) {
        for(int e : xb) {
            x = min(x, x ^ e);
        }
        return x;
    };

    auto getMask = [&](int x) {
        int res = 0;
        for(int i = 0; i < d; i++) {
            int e = xb[i];
            if((x ^ e) < x) {
                x = x ^ e;
                res |= 1 << i;
            }
        }
        return res;
    };

    vector<int> p(n + 1), q(n + 1);
    for(int i = 1; i <= n; i++) {
        p[i] = getMask(a[i]);
        q[i] = getRem(a[i]);
    }

    vector<int> tar;
    for(int i = 1; i <= k; i++) {
        tar.push_back(getMask(b[i]));
    }

    vector<Z> w(1 << d);
    for(int s : tar) {
        w[s] = 1;
    }

    auto f = [](auto& x, auto& y) { 
        auto u = x, v = y;
        x = u + v;
        y = u - v;
    };

    fwht(w, f);

    vector<int> subq(n + 1);
    vector<vector<Z>> dp(n + 1, vector<Z>(1 << d));

    auto dfs = [&](this auto&& self, int u, int fa) -> void {
        subq[u] = q[u];
        for(int s = 0; s < 1 << d; s++) {
            if(__builtin_popcount(p[u] & s) & 1) {
                dp[u][s] = -1;
            } else {
                dp[u][s] = 1;
            }
        }

        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);

            if(subq[v] == 0) {
                Z sum = 0;
                for(int s = 0; s < 1 << d; s++) {
                    sum += dp[v][s] * w[s];
                }
                sum *= inv2d;
                for(int s = 0; s < 1 << d; s++) {
                    dp[u][s] *= dp[v][s] + sum;
                }
            } else {
                for(int s = 0; s < 1 << d; s++) {
                    dp[u][s] *= dp[v][s];
                }
            }

            subq[u] ^= subq[v];
        }
    };

    dfs(1, 0);

    if(subq[1]) {
        cout << 0 << "\n";
        return;
    }

    Z ans = 0;
    for(int s = 0; s < 1 << d; s++) {
        ans += dp[1][s] * w[s];
    }
    ans *= inv2d;

    cout << ans << "\n";
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
