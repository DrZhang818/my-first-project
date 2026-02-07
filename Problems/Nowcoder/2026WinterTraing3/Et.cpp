#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct Edge {
    int u, v, w;
};

bool solve(int n, int m, int k) {  

    ll cur = 1LL * n * (n - 1) / 2;

    if(cur > k) {
        return false;
    }

    vector<int> w(n);
    iota(w.begin(), w.end(), 0);

    for(int i = n - 1; i >= 1; i--) {
        ll d = min((ll)m - n + 1, 1LL * i * (i - 1) / 2 + 1 - i);
        w[i] += min(k - cur, d);
        cur += min(k - cur, d);
    }

    if(cur < k) {
        return false;
    }

    vector<Edge> e;
    vector<PII> can;

    int idx = 1;

    for(int i = 1; i <= m; i++) {
        if(idx < n && w[idx] == i) {
            idx++;
            e.emplace_back(1, idx, i);
            if(can.size() < m) {
                for(int j = 2; j < idx; j++) {
                    can.push_back({j, idx});
                }
            }
        } else {
            if(can.empty()) {
                return false;
            }
            auto [u, v] = can.back();
            can.pop_back();
            e.emplace_back(u, v, i);
        }
    }

    return true;
}
template<class T1, class T2> bool cmin(T1 &x, const T2 &y) { if (y < x) { x = y; return 1; } return 0; }
template<class T1, class T2> bool cmax(T1 &x, const T2 &y) { if (x < y) { x = y; return 1; } return 0; }
#define all(x) (x).begin(),(x).end()
bool answer(int n, int m, ll q) {
    int i, j;
    vector<int> a(n);
    for (i = 1; i < n; i++) a[i] = min<ll>(m, i * (i - 1ll) / 2 + 1);
    for (i = n - 1; i > 1; i--) cmin(a[i - 1], a[i] - 1);
    // dbg(a);
    if (q<n * (n - 1ll) / 2 || q>reduce(all(a), 0ll))
    {
        return false;
    }
    vector<int> b(n);
    for (i = 1; i < n; i++) b[i] = i, q -= i;
    for (i = n - 1; i; i--)
    {
        ll d = min<ll>(q, a[i] - b[i]);
        b[i] += d;
        q -= d;
    }
    return true;
    int x = 3, y = 1;
    vector<pair<int, int>> eg;
    for (i = 1, j = 1; i < n; i++)
    {
        while (j < b[i])
        {
            assert(x <= i);
            eg.push_back({x, y});
            ++y;
            if (y == x - 1) ++x, y = 1;
            ++j;
        }
        eg.push_back({i, i + 1});
        ++j;
    }
    while (j <= m)
    {
        assert(x <= n);
        eg.push_back({x, y});
        ++y;
        if (y == x - 1) ++x, y = 1;
        ++j;

    }
    for (i = 0; i < m; i++)
    {
        auto [u, v] = eg[i];
        cout << u << ' ' << v << ' ' << i + 1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    for(int n = 1; n <= 100; n++) {
        for(int m = n - 1; m <= n * (n - 1) / 2; m++) {
            for(int k = 1; k <= m * m; k++) {
                bool ok1 = solve(n, m, k);
                bool ok2 = answer(n, m, k);
                if(ok1 != ok2) {
                    cerr << "WA!" << "\n";
                    cerr << n << " " << m << " " << k << " " << ok1 << " " << ok2 << "\n";
                }
            }
        }
    }

    return 0;
}
