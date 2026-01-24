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

constexpr int P = 1000000007;
using Z = MInt<P>;

Z inv6 = Z(6).inv();

Z sum_id2(Z i) {
    return i * (i + 1) * (2 * i + 1) * inv6;
}

Z sum_id2(int L, int R) {
    return sum_id2(R) - sum_id2(L - 1);
}

Z sum_id(int L, int R) {
    return Z(1LL * (L + R) * (R - L + 1) / 2);
}

constexpr int N = 1000000;
Z f[N + 1];
int minp[N + 1];
vector<int> primes;

void init() {
    f[1] = 1;

    for(int i = 2; i <= N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
            f[i] = -1;
        }
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(minp[i] == p) {
                f[i * p] = 0;
                break;
            } else {
                f[i * p] = -f[i];
            }
        }
    }

    for(int i = 2; i <= N; i++) {
        f[i] *= i;
        f[i] *= i;
        f[i] += f[i - 1];
    }
}

map<int, Z> mp;

Z get(int n) {
    if(n <= N) {
        return f[n];
    }
    auto it = mp.find(n);
    if(it != mp.end()) {
        return it->second;
    }

    Z res = 1;

    for(ll L = 2, R; L <= n; L = R + 1) {
        R = n / (n / L);
        res -= sum_id2(L, R) * get(n / L);
    }

    return mp[n] = res;
}

Z get(int L, int R) {
    return get(R) - get(L - 1);
}

void solve() {  
    int n;
    cin >> n;

    Z ans = 0;

    for(ll L = 1, R; L <= n; L = R + 1) {
        R = n / (n / L);
        Z x = sum_id(1, n / L);
        ans += x * x * get(L, R);
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init();

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
