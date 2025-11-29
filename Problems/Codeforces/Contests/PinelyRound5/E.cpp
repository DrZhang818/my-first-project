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

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    s = "#" + s;
    vector<array<int,2>> f(n + 1, {1, 1});
    for(int i = n; i >= 1; i--) {
        if(s[i] == '0') {
            f[i][1] = 0;
        }
        if(s[i] == '1') {
            f[i][0] = 0;
        }
        if(i + k - 1 <= n) {
            f[i][0] &= f[i + k - 1][0];
            f[i][1] &= f[i + k - 1][1];
        }
    }
    vector<array<int,2>> fix(n + 2);
    for(int i = n, c0 = 0, c1 = 0, bad = 0; i >= 1; i--) {
        int R = i + k - 2;
        if(R <= n) {
            bad -= (!f[R][0] && !f[R][1]);
            c0 -= (f[R][0] && !f[R][1]);
            c1 -= (!f[R][0] && f[R][1]);
        }
        bad += (!f[i][0] && !f[i][1]);
        c0 += (f[i][0] && !f[i][1]);
        c1 += (!f[i][0] && f[i][1]);
        if(bad > 0) {
            fix[i][0] = fix[i][1] = -1;
        } else {
            fix[i][0] = c0;
            fix[i][1] = c1;
        }
    }

    Z ans = 0;
    auto cal = [&](int x) -> void { 
        if(s[1] != '0' + x && s[1] != '?') {
            return;
        }
        bool ok = true;
        for(int i = 2; i <= n - k + 1; i++) {
            if(f[i][x ^ 1]) {
                if(fix[i + 1][x] != -1 && fix[i + 1][x] <= k / 2) {
                    int S = k - 2 - fix[i + 1][0] - fix[i + 1][1];
                    assert(S >= 0);
                    ans += comb.binom(S, k / 2 - fix[i + 1][x]);
                }
            }
            if(s[i] == '0' + (x ^ 1)) {
                ok = false;
                break;
            }
        }
        if(ok) {
            int S = k - 1, need = k / 2;
            for(int i = n - k + 2; i <= n; i++) {
                if(s[i] != '?') {
                    S--;
                }
                if(s[i] == '0' + x) {
                    need--;
                }
            }
            need = max(0, need);
            for(int i = need; i <= S; i++) {
                ans += comb.binom(S, i);
            }
        }
    };  
    cal(0);
    cal(1);
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
