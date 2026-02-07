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

Z solve(vector<int> a) { 
    int n = a.size() - 1;
    vector<int> cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        cnt[a[i]]++;
    }
    int len = cnt[1];
    for(int i = 2; i <= n; i++) {
        if(cnt[i] > len) {
            return 0;
        }
    }
    int idx = -1;
    if(a[1] == 1 && a[n] == 1) {
        idx = n;
        while(idx - 1 >= 1 && a[idx - 1] == 1) {
            idx--;
        }
    } else {
        idx = find(a.begin() + 1, a.end(), 1) - a.begin();
    }
    rotate(a.begin() + 1, a.begin() + idx, a.end());
    
    vector<int> f(n + 1), g(n + 1);

    map<int,int> mp;
    for(int i = 1, j = 1; i <= n; i++) {
        while(j <= n && j - i + 1 <= len) {
            mp[a[j]]++;
            j++;
        }
        auto [v, c] = *mp.rbegin();
        if(c == cnt[v]) {
            f[v]++;
        }
        g[v]++;
        if(--mp[a[i]] == 0) {
            mp.erase(a[i]);
        }
    }

    Z ans = 1, rem = 0;
    for(int i = 1; i <= n; i++) {
        if(cnt[i] > 0 && f[i] == 0) {
            return 0;
        }

        if(cnt[i] > 0) {
            ans *= f[i];
            rem += g[i] - 1;
        } else {
            ans *= rem;
            rem -= 1;
        }
    }
    return ans;
}

Z solve_brute(vector<int> a) {  
    int n = a.size() - 1;
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    vector<int> stop(n + 1, 1);
    stop[0] = 0;
    auto ck = [&](vector<int> p) -> bool {
        while(p != a && p != stop) {
            vector<int> np(n + 1);
            for(int i = 2; i <= n; i++) {
                np[i] = min(p[i - 1], p[i]);
            }
            np[1] = min(p[1], p[n]);
            p = move(np);
        }   
        return p == a;
    };
    Z ans = 0;
    do {
        if(ck(p)) {
            ans += 1;
        }
    } while(next_permutation(p.begin() + 1, p.end()));
    return ans;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get(int L, int R) {
    return rng() % (R - L + 1) + L;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n = 5;
    vector<int> a(n + 1);
    for(int t = 1; t <= 10000; t++) {
        for(int i = 1; i <= n; i++) {
            a[i] = get(1, n);
        }
        if(solve(a) != solve_brute(a)) {
            cerr << "WA\n";
            for(int i = 1; i <= n; i++) {
                cerr << a[i] << " \n"[i == n];
            }
            cerr << solve(a) << " " << solve_brute(a) << "\n";
        } 
    }


    return 0;
}
