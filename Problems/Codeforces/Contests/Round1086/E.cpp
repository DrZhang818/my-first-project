#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;


template<class T>
constexpr T power(T a, i64 b) {
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
    constexpr MInt(i64 x) : x{norm(x % getMod())} {}
    
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
        i64 v;
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


void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    if(a[1] == -1) a[1] = 0;
    for(int i = n; i >= 1; i--) {
        if(a[i] == -1) continue;
        if(a[i] >= i) {
            cout << 0 << "\n";
            return;
        }
        int j = a[i] + 1;
        if(a[j] == -1) a[j] = a[i];
        if(a[j] != a[i]) {
            cout << 0 << "\n";
            return;
        }
    }

    vector<int> suf(n + 1, -1);
    for(int i = n; i >= 0; i--) {
        if(a[i] != -1 && suf[a[i]] == -1) {
            suf[a[i]] = i;
        }
    }

    for(int i = 0; i <= n; i++) {
        if(suf[i] == -1) continue;
        for(int j = i + 1; j <= suf[i]; j++) {
            if(a[j] != -1 && a[j] < i) {
                cout << 0 << "\n";
                return;
            }
        }
    }

    auto dfs = [&](this auto&& self, int l, int r) -> Z {
        int len = r - l;
        vector<Z> dp(len, 0);
        dp[0] = 1;
        Z ways = 1;

        int k = l + 1;
        while(k <= r) {
            if(a[k] == -1) {
                for(int i = len - 2; i >= 0; i--) {
                    dp[i + 1] = dp[i];
                }
                dp[0] = 0;
                for(int i = len - 2; i >= 0; i--) {
                    dp[i] += dp[i + 1];
                }
                k++;
            } else if(a[k] == l) {
                Z sum = 0;
                for(int i = 0; i < len; i++) {
                    sum += dp[i];
                    dp[i] = 0;
                }
                dp[0] = sum;
                k++;
            } else {
                int R = suf[k - 1];
                ways *= self(k - 1, R);
                for(int i = len - 2; i >= 0; i--) {
                    dp[i + 1] = dp[i];
                }
                dp[0] = 0;
                k = R + 1;
            }
        }

        Z sum = 0;
        for(int i = 0; i < len; i++) {
            sum += dp[i]; 
        }
        return sum * ways;
    };

    cout << dfs(0, n) << "\n";
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
