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

constexpr Z inv4 = Z(4).inv();
constexpr Z inv8 = Z(8).inv();
constexpr Z inv16 = Z(16).inv();

using Matrix = vector<vector<Z>>;

Matrix operator * (const Matrix &a, const Matrix &b) {
    int n = a.size();
    vector c(n, vector<Z>(n));
    for(int i = 0; i < n; i++) {
        for(int k = 0; k < n; k++) {
            if(a[i][k] == 0) continue;
            for(int j = 0; j < n; j++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
};

Matrix fast_pow(Matrix a, ll b) {
    int n = a.size();
    Matrix res(n, vector<Z>(n));
    for(int i = 0; i < n; i++) {
        res[i][i] = 1;
    }
    while(b) {
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

void solve() {  
    int n;
    ll m;
    cin >> n >> m;
    vector<Z> vec(3 * n + 2);
    vec[3 * n] = 1;
    vec[2 * n - 1] = vec[3 * n - 1] = inv4;
    for(int i = n - 2; i >= 0; i--) {
        vec[i] = vec[n + i] = (3 * vec[i + 1] + vec[2 * n + i + 1]) * inv8 + 3 * vec[n + i + 1] * inv16;
        if(i == n - 2) {
            vec[i] += inv16;
            vec[n + i] += inv16;
        }
    }

    for(int i = 0; i < n; i++) {
        vec[3 * n + 1] += vec[i] * 9 * inv16 + (vec[n + i] + vec[2 * n + i]) * 3 * inv16;
    }
    vec[3 * n + 1] += inv16;

    Matrix mat(3 * n + 2, vector<Z>(3 * n + 2));
    mat[3 * n - 1][3 * n] = inv16;
    mat[3 * n + 1][3 * n + 1] = 1;
    for(int i = n - 1; i >= 0; i--) {
        mat[i][i] = 3 * inv16;
        mat[i][n + i] = inv16;
        mat[2 * n + i][i] = 3 * inv8;
        mat[2 * n + i][n + i] = inv8;
        mat[2 * n + i][2 * n + i] = 3 * inv16;
        if(i < n - 1) {
            for(int j = 0; j <= 3 * n; j++) {
                Z v = 3 * mat[i + 1][j] * inv8 + mat[2 * n + i + 1][j] * inv8 + mat[n + i + 1][j] * 3 * inv16;
                mat[i][j] += v;
                mat[n + i][j] += v;
            }
        }
        for(int j = 0; j <= 3 * n; j++) {
            mat[3 * n + 1][j] += mat[i][j] * 9 * inv16 + (mat[n + i][j] + mat[2 * n + i][j]) * 3 * inv16;
        }
    }

    mat = fast_pow(mat, m - 1);

    Z ans = 0;
    for(int j = 0; j <= 3 * n + 1; j++) {
        ans += mat[3 * n + 1][j] * vec[j];
    }

    ans *= power(Z(4), 1LL * (n + 1) * (m + 1));
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
