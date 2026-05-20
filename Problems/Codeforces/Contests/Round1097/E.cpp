#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
using i128 = __int128;
constexpr i64 inf = i64(1E18) + 1;

i64 norm(i64 x, i64 m) {
    x %= m;
    if(x < 0) x += m;
    return x;
}

i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i64 x1, y1;
    i64 g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return g;
}

i64 inv(i64 a, i64 m) {
    i64 x, y;
    exgcd(a, m, x, y);
    return norm(x, m);
}

struct CRT {
    bool ok;
    i128 a;
    i128 m;
};

CRT crt(i64 a, i64 m, i64 b, i64 n) {
    i64 g = gcd(m, n);
    if((b - a) % g) {
        return {false, 0, 0};
    }
    i64 m1 = m / g;
    i64 n1 = n / g;

    i128 mod = (i128)m1 * n;
    i128 t = 0;

    if(n1 != 1) {
        i64 c = norm((b - a) / g, n1);
        i64 iv = inv(m1 % n1, n1);
        t = (i128)c * iv % n1;
    }

    i128 x = (i128)a + (i128)m * t;
    x %= mod;
    if(x < 0) x += mod;

    return {true, x, mod};
}

void solve() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> adj(n + 1);
    vector<int> fa(n + 1);
    for(int i = 2; i <= n; i++) {
        cin >> fa[i];
        adj[fa[i]].push_back(i);
    }

    vector<i64> w(n + 1), dep(n + 1);
    for(int i = 2; i <= n; i++) {
        cin >> w[i];
        dep[i] = dep[fa[i]] + w[i];
    }

    vector<i64> p(n + 1), a(n + 1);
    p[1] = 1;

    for(int u = 1; u <= n; u++) {
        if(!p[u]) continue;

        int d = adj[u].size();
        if(!d) continue;

        if(p[u] == inf || p[u] % d == 0) {
            int k = (a[u] + dep[u]) % d;
            int v = adj[u][k];

            p[v] = p[u];
            a[v] = a[u];
        } else {
            i64 g = gcd(p[u], d);
            int st = (a[u] + dep[u]) % g;
            for(int k = st; k < d; k += g) {
                int v = adj[u][k];
                i64 r = norm(k - dep[u], d);

                auto res = crt(a[u], p[u], r, d);
                
                if(res.m >= inf) {
                    if(res.a < inf) {
                        p[v] = inf;
                        a[v] = res.a;
                    }
                } else {
                    p[v] = res.m;
                    a[v] = res.a;
                }
            }
        }
    }

    vector<int> go(n + 1);

    for(int u = n; u >= 1; u--) {
        if(p[u] == 0) continue;
        int d = adj[u].size();
        if(d == 0) {
            go[u] = u;
        } else if(p[u] == inf || p[u] % d == 0) {
            int k = (a[u] + dep[u]) % d;
            go[u] = go[adj[u][k]];
        } else {
            go[u] = u;
        }
    }

    while(q--) {
        i64 m;
        cin >> m;

        int u = 1;

        while(!adj[u].empty()) {
            int d = adj[u].size();
            int k = (m + dep[u]) % d;
            u = go[adj[u][k]];
        }
                
        cout << u << " \n"[q == 0];
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