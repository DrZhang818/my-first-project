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

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<PII> e(m);
    vector<vector<PII>> adj(n);

    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        if(i < n - 1) {
            adj[u].emplace_back(v, i);
            adj[v].emplace_back(u, i);
        }
        e[i] = {u, v};
    }

    vector<int> msk(m);

    for(int i = n - 1; i < m; i++) {
        auto [u, v] = e[i];

        auto dfs = [&](auto&& self, int x, int fa, int s) -> bool {
            if(x == v) {
                msk[i] = s;
                return true;
            }
            for(auto [y, j] : adj[x]) {
                if(y != fa && self(self, y, x, s | (1 << j))) {
                    return true;
                }
            }
            return false;
        };

        dfs(dfs, u, -1, 0);
    }

    vector<int> f(1 << n - 1);
    for(int i = n - 1; i < m; i++) {
        f[msk[i]]++;
    }
    for(int i = 0; i < n - 1; i++) {
        for(int s = 0; s < 1 << n - 1; s++) {
            s |= 1 << i;
            f[s] += f[s ^ (1 << i)];
        }
    }

    const int N = (1 << n - 1) - 1;

    vector<Z> cnt(N + 1);
    vector<Z> sum(N + 1);
    cnt[N] = 1;

    for(int s = N; s >= 0; s--) {
        if(cnt[s] == 0) continue;

        int b = n - 1 - __builtin_popcount(s);
        int cur = b + f[N] - f[s];

        for(int i = 0; i < n - 1; i++) {
            if(~s >> i & 1) continue;

            int ns = s ^ (1 << i);
            int k = f[s] - f[ns];

            Z C = cnt[s] * comb.fac(cur + k) * comb.invfac(cur);
            Z S = sum[s] * comb.fac(cur + k + 1) * comb.invfac(cur + 1);
            S += C * (b + 1);

            cnt[ns] += C;
            sum[ns] += S;
        }
    }

    cout << sum[0] << "\n";
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
