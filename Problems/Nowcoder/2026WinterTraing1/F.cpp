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

vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u);
    fa[u] = v;
}

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<int> loL(n + 1, -1), loR(n + 1, -1), hiL(n + 1, -1), hiR(n + 1, -1);
    for(int i = 1; i <= m; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        if(loL[x] == -1) {
            loL[x] = hiL[x] = l;
            loR[x] = hiR[x] = r;
        } else {
            if(l > loR[x] || r < loL[x]) {
                cout << 0 << "\n";
                return;
            }
            loL[x] = max(loL[x], l);
            loR[x] = min(loR[x], r);
            hiL[x] = min(hiL[x], l);
            hiR[x] = max(hiR[x], r);
        }
    }

    fa.resize(n + 2);
    iota(fa.begin(), fa.end(), 0);

    vector<int> cnt(n + 1), f(n + 1);
    int rem = n;

    for(int x = 1; x <= n; x++) {
        if(loL[x] == -1) {
            continue;
        }

        for(int i = loL[x]; i <= loR[x]; i++) {
            i = find(i);
            if(i <= loR[x]) {
                cnt[x]++;
                merge(i, i + 1);
            }
        }

        f[x] = cnt[x];

        for(int i = hiL[x]; i <= hiR[x]; i++) {
            i = find(i);
            if(i <= hiR[x]) {
                f[x]++;
                merge(i, i + 1);
            }
        }

        rem -= f[x];
    }

    Z ans = 1;

    for(int x = n; x >= 1; x--) {
        if(loL[x] == -1) {
            ans *= rem;
            rem--;
        } else {
            ans *= cnt[x];
            rem += f[x] - 1;
        }   
    }

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
