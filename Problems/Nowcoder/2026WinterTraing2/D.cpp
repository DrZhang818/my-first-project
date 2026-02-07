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

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> id(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        id[a[i]] = i;
    }   

    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int root = find(a.begin() + 1, a.end(), 0) - a.begin();

    vector<int> fa(n + 1);
    vector<Z> dp(n + 1);

    auto dfs = [&](auto&& self, int u, int p) -> void {
        fa[u] = p;
        dp[u] = 1;
        for(int v : adj[u]) {
            if(v == p) continue;
            self(self, v, u);
            dp[u] *= dp[v];
        }
        dp[u] += 1;
    };

    dfs(dfs, root, 0);

    Z cur = 1;
    int c0 = 0;
    for(int v : adj[root]) {
        if(dp[v] != 0) {
            cur *= dp[v];
        } else {
            c0++;
        }
    }

    int mex = 1;
    vector<int> cnt(n + 1);
    Z ans = c0 == 0 ? cur : 0;

    vector<int> vis(n + 1);
    vis[root] = true;

    while(mex < n) {
        int x = mex;
        int u = id[x];
        while(1) {
            vis[u] = true;
            for(int v : adj[u]) {
                if(!vis[v] && v != fa[u]) {
                    if(dp[v] == 0) {
                        c0++;
                    } else {
                        cur *= dp[v];
                    }
                }
            }
            cnt[a[u]]++;
            if(vis[fa[u]]) {
                if(dp[u] == 0) {
                    c0--;
                } else {
                    cur *= dp[u].inv();
                }
                break;
            }
            u = fa[u];
        }

        while(cnt[mex]) {
            mex++;
        }

        int d = mex - x;
        if(c0 == 0) {
            ans += cur * d;
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
