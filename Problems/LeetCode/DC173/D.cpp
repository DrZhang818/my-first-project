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


class Solution {
public:
    int numberOfRoutes(vector<string>& grid, int d) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> a(n + 1, vector<int>(m + 1));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                a[i][j] = grid[i - 1][j - 1] == '.' ? 1 : 0;
            }
        }
        vector<Z> dp(m + 1);
        for(int j = 1; j <= m; j++) {
            if(a[n][j] == 1) {
                dp[j] = 1;
            }
        }
        for(int i = n - 1; i >= 1; i--) {
            vector<Z> pre(m + 1);
            for(int j = 1; j <= m; j++) {
                pre[j] = pre[j - 1] + dp[j];
            }
            auto ndp = dp;
            for(int j = 1; j <= m; j++) {
                if(a[i + 1][j] == 1) {
                    ndp[j] = pre[min(m, j + d)] - pre[max(0, j - d - 1)];
                }
            }
            swap(dp, ndp);
            for(int j = 1; j <= m; j++) {
                pre[j] = pre[j - 1] + dp[j];
            }
            ndp = vector<Z>(m + 1, 0);
            for(int j = 1; j <= m; j++) {
                if(a[i][j] == 1) {
                    ndp[j] = pre[min(m, j + d - 1)] - pre[max(0, j - d)];
                }
            }
            swap(dp, ndp);
        }
        {
            vector<Z> pre(m + 1);
            for(int j = 1; j <= m; j++) {
                pre[j] = pre[j - 1] + dp[j];
            }
            auto ndp = dp;
            for(int j = 1; j <= m; j++) {
                if(a[1][j] == 1) {
                    ndp[j] = pre[min(m, j + d)] - pre[max(0, j - d - 1)];
                }
            }
            swap(dp, ndp);
        }
        Z ans = 0;
        for(int j = 1; j <= m; j++) {
            ans += dp[j];
        }
        int res = ans.x;
        return res;
    }
};