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

constexpr int N = 1 << 4;

void fwht(vector<Z>& a, auto combine) {
    int n = a.size();
    for(int i = 1; i < n; i <<= 1) {
        for(int j = 0; j < n; j += i << 1) {
            for(int k = 0; k < i; k++) {
                combine(a[j + k], a[j + i + k]);
            }
        }
    }
}

vector<Z> work(vector<Z> a, vector<Z> b, int type) {
    if(type == 0) {
        auto f = [](Z& x, Z& y) { y += x; };
        auto g = [](Z& x, Z& y) { y -= x; };
        
        fwht(a, f); 
        fwht(b, f);
        
        for(int i = 0; i < a.size(); i++) {
            a[i] *= b[i];
        }

        fwht(a, g);
    } else if(type == 1) {
        auto f = [](Z& x, Z& y) { x += y; };
        auto g = [](Z& x, Z& y) { x -= y; };

        fwht(a, f);
        fwht(b, f);

        for(int i = 0; i < a.size(); i++) {
            a[i] *= b[i];
        }

        fwht(a, g);
    }
    return a;
}

vector<Z> operator+(const vector<Z>& a, const vector<Z>& b) {
    auto c = a;
    for(int i = 0; i < a.size(); i++) {
        c[i] += b[i];
    }
    return c;
}

int to[] = {0b1111111100000000, 0b1111000011110000, 0b1100110011001100, 0b1010101010101010,
            0b0000000011111111, 0b0000111100001111, 0b0011001100110011, 0b0101010101010101};

void solve() {  
    string s;
    cin >> s;

    int n;
    cin >> n;
    vector<int> a(N, -1);
    for(int i = 0; i < n; i++) {
        int msk = 0, f = 0;
        for(int j = 0; j < 4; j++) {
            int x;
            cin >> x;
            msk = msk << 1 | x;
        }
        cin >> f;   
        a[msk] = f;
    }

    auto dfs = [&](this auto&& self, int l, int r) -> vector<Z> {
        vector<Z> res(1 << N);
        if(l == r) {
            if(s[l] == '?') {
                for(int i = 0; i < 8; i++) {
                    res[to[i]] += 1;
                }
            } else {
                if(isupper(s[l])) {
                    res[to[s[l] - 'A']] += 1;
                } else {
                    res[to[s[l] - 'a' + 4]] += 1;
                }
            }
            return res;
        }

        int cur = 0, idx = -1;
        for(int i = l; i <= r; i++) {
            if(s[i] == '(') {
                cur++;
                continue;
            } else if(s[i] == ')') {
                cur--;
                continue;
            }
            if(cur == 0) {
                idx = i;
                break;
            }
        }

        auto L = self(l + 1, idx - 2);
        auto R = self(idx + 2, r - 1);

        if(s[idx] == '|') {
            return work(L, R, 0);
        } else if(s[idx] == '&') {
            return work(L, R, 1);
        } else {
            return work(L, R, 0) + work(L, R, 1);
        }
    }; 

    int m = s.size();
    auto dp = dfs(0, m - 1);

    Z ans = 0;
    for(int s = 0; s < 1 << N; s++) {
        if(dp[s] == 0) continue;
        bool ok = true;
        for(int i = 0; i < N; i++) {
            if(a[i] != -1 && a[i] != (s >> i & 1)) {
                ok = false;
                break;
            }
        }
        if(ok) {
            ans += dp[s];
        }
    }

    cout << ans << "\n";
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
