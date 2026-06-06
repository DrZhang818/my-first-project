#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

constexpr int P = 998244353;
int norm(int x) {
    if(x < 0) {
        x += P;
    }
    if(x >= P) {
        x -= P;
    }
    return x;
}
template<class T>
T power(T a, int b) {
    T res = 1;
    while(b) {
        if(b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}
struct Z {
    int x;
    Z(int x = 0) : x(norm(x)) {}
    Z(i64 x) : x(norm(x % P)) {}
    int val() const {
        return x;
    }
    Z operator - () const {
        return Z(norm(P - x));
    }
    Z inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    Z &operator *= (const Z &rhs) {
        x = i64(x) * rhs.x % P;
        return *this;
    }
    Z &operator += (const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator -= (const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator /= (const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator * (const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator + (const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator - (const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator / (const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend istream &operator >> (istream &is, Z &a) {
        i64 v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend ostream &operator << (ostream &os, const Z &a) {
        return os << a.val();
    }
};

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if(adj[n].size() == 1) {
        cout << 1 << "\n";
        return;
    }

    vector<int> fa(n + 1), bel(n + 1), ord;
    ord.push_back(n);
    for(int i = 0; i < n; i++) {
        int u = ord[i];
        for(int v : adj[u]) {
            if(v == fa[u]) continue;
            fa[v] = u;
            bel[v] = u == n ? v : bel[u];
            ord.push_back(v);
        }
    }

    vector<int> mx(n + 1), lim(n + 1);
    for(int i = n - 1; i >= 0; i--) {
        int u = ord[i];
        mx[u] = u;
        for(int v : adj[u]) {
            if(v == fa[u]) continue;
            mx[u] = max(mx[u], mx[v]);
            lim[u] = max(lim[u], mx[v]);
        }
    }

    int o = 0, mx1 = 0, mx2 = 0;
    for(int v : adj[n]) {
        if(mx[v] > mx1) {
            tie(mx2, mx1, o) = tuple(mx1, mx[v], v);
        } else if(mx[v] > mx2) {
            mx2 = mx[v];
        }
    }

    vector<Z> dp(n + 1), del(n + 1);
    dp[n] = 1;
    Z sum = 0;

    for(int u = n - 1; u >= 1; u--) {
        sum -= del[u];

        if(lim[u] > u) continue;

        dp[u] = sum;
        if(bel[u] == o && u > mx2) {
            dp[u] += 1;
        }

        sum += dp[u];
        del[lim[u]] += dp[u];

        if(adj[u].size() == 1) {
            cout << dp[u] << "\n";
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}