#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;
constexpr int N = 2E5;

struct Info {
    int l, r;
    friend bool operator<(const Info& a, const Info& b) {
        if(a.l != b.l) {
            return a.l < b.l;
        }
        return a.r < b.r;
    }
    bool operator==(const Info&) const = default;
};

vector<int> fac[N + 1];

auto init = []() {
    for(int i = 1; i <= N; i++) {
        for(int j = i; j <= N; j += i) {
            fac[j].push_back(i);
        }
    }
    return 1;
}();

struct FenwickTree {
    int n;
    vector<int> tr;
    int timer;
    vector<int> T;
    FenwickTree(int n) : n(n), tr(n), timer(0), T(n) {}
    void reset() {
        timer++;
    }
    void add(int o, int d) {
        for(; o < n; o += o & -o) {
            if(T[o] != timer) {
                T[o] = timer;
                tr[o] = d;
            } else {
                tr[o] += d;
            }
        }
    }
    int query(int o) {
        int res = 0;
        for(; o > 0; o -= o & -o) {
            if(T[o] != timer) {
                continue;
            }
            res += tr[o];
        }
        return res;
    }
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(2 * n + 1);   
    int g = n;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(i > 1 && x < a[i - 1]) {
            g = gcd(g, i - 1);
        }
        a[i] = a[n + i] = x;
    }
    FenwickTree fen(n + 1);

    i64 ans = numeric_limits<i64>::max();

    for(int d : fac[g]) {
        fen.reset();
        bool ok = true;
        int m = n / d;
        vector<Info> b(2 * m + 1);
        for(int i = 1, j = 1; i <= n; i += d, j++) {
            b[j] = b[m + j] = Info(a[i], a[i + d - 1]);
        }

        vector<int> p(m + 1);
        iota(p.begin(), p.end(), 0);
        sort(p.begin() + 1, p.end(), 
            [&](int i, int j) {
                return b[i] < b[j];
            });

        for(int i = 2; i <= m; i++) {
            if(b[p[i]].l < b[p[i - 1]].r) {
                ok = false;
            }
        }
        if(!ok) {
            continue;
        }

        vector<int> id(2 * m + 1);
        for(int i = 1, j = 0; i <= m; i++) {
            if(i == 1 || b[p[i]] != b[p[i - 1]]) {
                id[p[i]] = id[m + p[i]] = ++j;
            } else {
                id[p[i]] = id[m + p[i]] = j;
            }
        }

        i64 cur = 0;
        for(int i = m; i >= 1; i--) {
            cur += fen.query(id[i] - 1);
            fen.add(id[i], 1);
        }
        ans = min(ans, cur);

        for(int i = m + 1; i < 2 * m; i++) {
            cur -= fen.query(id[i] - 1);
            cur += fen.rangeQuery(id[i] + 1, m);
            ans = min(ans, cur + i - m);
        }
    }

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
