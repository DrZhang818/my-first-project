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

constexpr Z inv2 = Z(2).inv();
constexpr Z inv6 = Z(6).inv();

vector<int> minp, primes;
vector<Z> sp1, sp2;
void init(int n) {
    minp.resize(n + 1);
    sp1.resize(n + 1);
    sp2.resize(n + 1);
    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
            int j = primes.size();
            sp1[j] = sp1[j - 1] + i;
            sp2[j] = sp2[j - 1] + 1LL * i * i;
        }
        for(auto p : primes) {
            if(i * p > n) break;
            minp[i * p] = p;
            if(minp[i] == p) break;
        }
    }
}

void solve() {  
    ll n;
    cin >> n;
    int sq = sqrt(n);
    init(sq);

    vector<ll> w;
    vector<int> id1(sq + 1), id2(sq + 1);
    for(ll L = 1, R; L <= n; L = R + 1) {
        R = n / (n / L);
        ll v = n / L;
        w.push_back(v);
        if(v <= sq) {
            id1[v] = int(w.size()) - 1;
        } else {
            id2[n / v] = int(w.size()) - 1;
        }
    }

    auto get = [&](ll x) {
        return x <= sq ? id1[x] : id2[n / x];
    };

    vector<Z> g1(w.size()), g2(w.size());
    for(int i = 0; i < w.size(); i++) {
        Z x = w[i];
        g1[i] = x * (x + 1) * inv2 - 1;
        g2[i] = x * (x + 1) * (2 * x + 1) * inv6 - 1;
    }

    for(int j = 0; j < primes.size(); j++) {
        ll p = primes[j];
        ll p2 = p * p;
        for(int i = 0; i < w.size(); i++) {
            if(w[i] < p2) break;
            int k = get(w[i] / p);
            g1[i] -= p * (g1[k] - sp1[j]);
            g2[i] -= p2 * (g2[k] - sp2[j]);
        }
    }

    auto S = [&](this auto&& self, ll x, int j) -> Z {
        if(x <= 1 || j < primes.size() && primes[j] > x) return 0;

        int k = get(x);

        Z ans = g2[k] - g1[k] - (sp2[j] - sp1[j]);

        for(int i = j; i < primes.size(); i++) {
            ll p = primes[i];
            if(p * p > x) break;
            for(ll pe = p; pe * p <= x; pe *= p) {
                Z cur = Z(pe) * (pe - 1);
                ans += cur * self(x / pe, i + 1);
                Z np = Z(pe) * p;
                ans += np * (np - 1);
            }
        }

        return ans;
    };

    cout << S(n, 0) + 1 << "\n";
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
