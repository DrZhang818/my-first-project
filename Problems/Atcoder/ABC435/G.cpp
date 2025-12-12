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


void solve() {  
    int n, m;
    cin >> n >> m;
    vector<int> L(m + 1), R(m + 1), C(n + 2);
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        cin >> L[i] >> R[i];
        if(L[i] == R[i]) continue;
        adj[R[i]].push_back(i);
        C[L[i] + 1]++;
        C[R[i] + 1]--;
    }
    for(int i = 1; i <= n; i++) {
        C[i] += C[i - 1];
    }
    vector<Z> S(n + 1), f(n + 1), pre(n + 1);
    S[0] = S[1] = 1;
    pre[0] = pre[1] = 1;
    for(int i = 2, s = 0; i <= n; i++) {
        S[i] = C[i] * S[i - 2] - f[i];
        if(i + 2 <= n) {
            f[i + 2] = S[i];
            auto apply = [&](int u) {
                for(int x : adj[u]) {
                    if(L[x] >= i) continue;
                    int p = L[x];
                    p -= (p ^ i) & 1;
                    Z cur = pre[i - 2] - (p >= 2 ? pre[p - 2] : 0);
                    if(s) {
                        cur = -cur;
                    }
                    f[i + 2] -= cur;
                }
            };
            apply(i);
            apply(i + 1);
        }
        S[i] += S[i - 1];
        pre[i] = pre[i - 2] + S[i] * (s == 0 ? -1 : 1);
        if(i & 1) {
            s ^= 1;
        }
    }
    cout << S[n] << "\n";
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
