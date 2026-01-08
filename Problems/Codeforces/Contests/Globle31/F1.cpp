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

constexpr int N = 5000;
Z dp[N + 1][N + 1][2][2];
Z pre[N + 2][N + 2];
void init() {
    Z inv4 = Z(4).inv();
    Z inv16 = Z(16).inv();
    for(int i = N; i >= 1; i--) {
        for(int j = N; j >= 1; j--) {
            if(i == N && j == N) {
                dp[i][j][0][1] = dp[i][j][1][0] = inv4;
                dp[i][j][1][1] = 1;
            } else if(i == N) {
                dp[i][j][0][0] = (dp[i][j + 1][0][0] * 3 + dp[i][j + 1][0][1]) * inv16;
                dp[i][j][1][0] = (dp[i][j + 1][1][0] * 3 + dp[i][j + 1][1][1]) * inv16 + (dp[i][j + 1][0][0] * 3 + dp[i][j + 1][0][1]) * 2 * inv16; 
            } else if(j == N) {
                dp[i][j][0][0] = dp[i][j][0][1] = (dp[i + 1][j][0][0] * 3 + dp[i + 1][j][1][0]) * 2 * inv16 + (dp[i + 1][j][0][1] * 3 + dp[i + 1][j][1][1]) * inv16;
            } else {
                dp[i][j][0][0] = dp[i][j][0][1] = (dp[i + 1][j][0][0] * 3 + dp[i + 1][j][1][0]) * 2 * inv16 + (dp[i + 1][j][0][1] * 3 + dp[i + 1][j][1][1]) * inv16;
                dp[i][j][1][0] = (dp[i][j + 1][1][0] * 3 + dp[i][j + 1][1][1]) * inv16 + (dp[i][j + 1][0][0] * 3 + dp[i][j + 1][0][1]) * 2 * inv16;
                dp[i][j][0][0] += (dp[i][j + 1][0][0] * 3 + dp[i][j + 1][0][1]) * inv16;
            }  
        }
    }
    for(int i = N; i >= 1; i--) {
        for(int j = N; j >= 1; j--) {
            pre[i][j] = pre[i + 1][j] + pre[i][j + 1] - pre[i + 1][j + 1] + dp[i][j][0][0] * 9 * inv16 + (dp[i][j][0][1] + dp[i][j][1][0]) * 3 * inv16 + dp[i][j][1][1] * inv16;
        }
    }
}

void solve() {  
    int n, m;
    cin >> n >> m;
    cout << power(Z(4), (n + 1) * (m + 1)) * pre[N - n + 1][N - m + 1] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init();    

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
