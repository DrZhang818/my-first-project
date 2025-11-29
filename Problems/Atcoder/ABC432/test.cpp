#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

constexpr int P = 998244353;
using ll = long long;
int norm(int x) {
    if(x < 0) {
        x += P;
    }
    if(x >= P) {
        x -= P;
    }
    return x;   
}
template<class T>
T power(T a, ll b) {
    T res = 1;
    while(b) {
        if(b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}
struct Z {
    int x;
    Z(int x = 0) : x(norm(x % P)) {}
    Z(ll x) : x(norm(x % P)) {}
    int val() const {
        return x;   
    }
    Z operator-() const {
        return Z(norm(P - x));
    }  
    Z inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = ll(x) * rhs.x % P;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend istream &operator>>(istream &is, Z &a) {
        ll v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend ostream &operator<<(ostream &os, const Z &a) {
        return os << a.val();
    }
};

struct Comb {
    int n;
    vector<Z> _fac;
    vector<Z> _invfac;
    vector<Z> _inv;
    
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }
    void init(int m) {
        if(m <= n) return ;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        for(int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for(int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }
    Z fac(int m) {
        if(m > n) init(2 * m);
        return _fac[m];
    }
    Z invfac(int m) {
        if(m > n) init(2 * m);
        return _invfac[m];
    }
    Z inv(int m) {
        if(m > n) init(2 * m);
        return _inv[m];
    }
    Z binom(int n, int m) {
        if(n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;

// --- 依赖之前的 Z 类 (模数必须是 998244353) ---
// ... (此处粘贴之前的 Z 类代码) ...

// --- NTT 核心部分 ---
namespace NTT {
    std::vector<int> rev;
    std::vector<Z> roots{0, 1};
    
    void dft(std::vector<Z> &a) {
        int n = a.size();
        if (int(rev.size()) != n) {
            int k = __builtin_ctz(n) - 1;
            rev.resize(n);
            for (int i = 0; i < n; i++)
                rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
        }
        for (int i = 0; i < n; i++)
            if (rev[i] < i) std::swap(a[i], a[rev[i]]);
            
        if (int(roots.size()) < n) {
            int k = __builtin_ctz(roots.size());
            roots.resize(n);
            while ((1 << k) < n) {
                Z e = power(Z(3), (P - 1) >> (k + 1));
                for (int i = 1 << (k - 1); i < (1 << k); i++) {
                    roots[2 * i] = roots[i];
                    roots[2 * i + 1] = roots[i] * e;
                }
                k++;
            }
        }
        for (int k = 1; k < n; k *= 2) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    Z u = a[i + j];
                    Z v = a[i + j + k] * roots[k + j];
                    a[i + j] = u + v;
                    a[i + j + k] = u - v;
                }
            }
        }
    }
    
    void idft(std::vector<Z> &a) {
        int n = a.size();
        std::reverse(a.begin() + 1, a.end());
        dft(a);
        Z inv = Z(n).inv();
        for (int i = 0; i < n; i++) a[i] *= inv;
    }
}

// --- Poly 结构体 (仅保留卷积) ---
struct Poly : public std::vector<Z> {
    using std::vector<Z>::vector; // 使用 vector 的构造函数
    
    // 乘法重载：核心功能
    friend Poly operator*(Poly a, Poly b) {
        if (a.empty() || b.empty()) return Poly();
        int sz = a.size() + b.size() - 1;
        int n = 1;
        while (n < sz) n *= 2;
        a.resize(n);
        b.resize(n);
        NTT::dft(a);
        NTT::dft(b);
        for (int i = 0; i < n; i++) a[i] *= b[i];
        NTT::idft(a);
        a.resize(sz);
        return a;
    }
    
    // 加法重载 (可选，方便写代码)
    Poly& operator+=(const Poly &b) {
        if (this->size() < b.size()) this->resize(b.size());
        for (int i = 0; i < b.size(); i++) (*this)[i] += b[i];
        return *this;
    }
    friend Poly operator+(Poly a, const Poly &b) { return a += b; }
};

constexpr int V = 500005;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> ca(V), cb(V);
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ca[x]++;
    }
    for(int j = 0; j < m; j++) {
        int x;
        cin >> x;
        cb[x]++;
    }
    Poly f(V), g(V);
    for(int i = 0; i < V; i++) {
        f[i] = Z(cb[i]) * comb.invfac(i);
        g[i] = comb.invfac(i);
    }
    f = f * g;
    Z ans = 0;
    for(int i = 0; i < V; i++) {
        ans += Z(ca[i]) * comb.fac(i) * f[i].val();
    }
    cout << ans << "\n";
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
