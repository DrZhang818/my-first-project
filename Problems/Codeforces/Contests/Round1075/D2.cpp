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

void solve() {  
    int n, c;
    cin >> n >> c;
    string s;
    cin >> s;
    s = " " + s;
    if(s[1] == '?') s[1] = '1';
    if(s[n] == '?') s[n] = '1';
    if(s[1] == '0' || s[n] == '0') {
        cout << -1 << "\n";
        return;
    }
    Z ans = 1;
    int prod = 1;
    vector<int> val;
    for(int i = n - 1; i >= 1; i--) {
        if(s[i] == '1') {
            ans *= 2;
            prod = 1LL * prod * 2 % c;
        } else if(s[i] == '0') {
            ans *= i - 1;
            prod = 1LL * prod * (i - 1) % c;
        } else {
            if(i - 1 > 2) {
                val.push_back(i - 1);
            } else {
                ans *= i - 1;
                prod = 1LL * prod * (i - 1) % c;
            }
        }
    }

    if(prod == 0) {
        cout << -1 << "\n";
        return;
    }

    int m = val.size();
    while(m > 0) {
        if(2LL * prod % c) {
            ans *= 2;
            prod = 2LL * prod % c;
            m--;
        } else {
            break;
        }
    }

    reverse(val.begin(), val.end());

    for(int i = 0; i < val.size() && m > 0; i++) {
        if(val[i] & 1) {
            ans *= val[i];
            prod = 1LL * prod * val[i] % c;
            m--;
        }
    }

    if(m || prod == 0) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
    }
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
