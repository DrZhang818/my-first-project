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

constexpr Z inv2 = (P + 1) / 2;

void fwht(vector<Z>& a, auto combine) {
    int n = a.size();
    for(int i = 1; i < n; i <<= 1) {
        for(int j = 0; j < n; j += i << 1) {
            for(int k = 0; k < i; k++) {
                combine(a[j + k], a[j + i + k]);
            }
        }
    }
}

void work(int n, vector<Z> a, vector<Z> b, int type) {
    int N = 1 << n;
    if(type == 0) {
        auto f = [](Z& x, Z& y) { y += x; };
        auto g = [](Z& x, Z& y) { y -= x; };
        
        fwht(a, f); 
        fwht(b, f);
        
        for(int i = 0; i < N; i++) {
            a[i] *= b[i];
        }

        fwht(a, g);
    } else if(type == 1) {
        auto f = [](Z& x, Z& y) { x += y; };
        auto g = [](Z& x, Z& y) { x -= y; };

        fwht(a, f);
        fwht(b, f);

        for(int i = 0; i < N; i++) {
            a[i] *= b[i];
        }

        fwht(a, g);
    } else {
        auto f = [](Z& x, Z& y) {
            Z u = x, v = y;
            x = u + v;
            y = u - v;
        };
        auto g = [](Z& x, Z& y) {
            Z u = x, v = y;
            x = (u + v) * inv2;
            y = (u - v) * inv2;
        };

        fwht(a, f);
        fwht(b, f);

        for(int i = 0; i < N; i++) {
            a[i] *= b[i];
        }

        fwht(a, g);
    }

    for(int i = 0; i < N; i++) {
        cout << a[i] << " \n"[i == N - 1];
    }
}

void solve() {  
    int n;
    cin >> n;

    const int N = 1 << n;

    vector<Z> a(N), b(N);

    for(int i = 0; i < N; i++) {
        cin >> a[i];
    }    
    for(int i = 0; i < N; i++) {
        cin >> b[i];
    }

    work(n, a, b, 0);
    work(n, a, b, 1);
    work(n, a, b, 2);
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
