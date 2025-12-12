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

using T = pair<Z,Z>;

int k, p;
int low[20], high[20];
T dp[20][1 << 10];
Z power10[21];


T dfs(int pos, int s, bool limit_low, bool limit_high) {
    if(pos == 0) {
        return {0, 1};
    }
    if(!limit_low && !limit_high && dp[pos][s].first != -1) {
        return dp[pos][s];
    }
    int lo = limit_low ? low[pos] : 0;
    int hi = limit_high ? high[pos] : 9;
    Z sum = 0, cnt = 0;
    for(int i = lo; i <= hi; i++) {
        int ns = s;
        if(!limit_low || i > 0 || pos <= p) {
            ns |= 1 << i;
        }
        if(__builtin_popcount(ns) > k) {
            continue;
        }
        auto [cur, c] = dfs(pos - 1, ns, limit_low && i == lo, limit_high && i == hi);
        sum += cur + power10[pos - 1] * Z(i) * c;
        cnt += c;
    }
    T res = {sum, cnt};
    if(!limit_low && !limit_high) {
        dp[pos][s] = res;
    }
    return res;
}

Z cal(ll l, ll r) {
    int cnt_lo = 0, cnt_hi = 0;
    while(l) {
        low[++cnt_lo] = l % 10; 
        l /= 10;
    }
    while(r) {
        high[++cnt_hi] = r % 10;
        r /= 10;
    }
    p = cnt_hi;
    while(low[p] == 0) p--;
    return dfs(cnt_hi, 0, true, true).first;
}

void solve() {
    ll l, r;
    cin >> l >> r >> k;
    cout << cal(l, r) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 0; i <= 19; i++) {
        for(int s = 0; s < 1 << 10; s++) {
            dp[i][s].first = -1;
        }
    }

    power10[0] = 1;
    for(int i = 1; i <= 20; i++) {
        power10[i] = power10[i - 1] * 10;
    }

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
