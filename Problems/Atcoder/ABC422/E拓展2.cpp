#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int rd(int L, int R) {
    return rnd() % (R - L + 1) + L;
}
bool ck(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
    return (y3 - y1) * (x2 - x1) == (y2 - y1) * (x3 - x1);
}
PII get(int n) {
    PII a = {rd(1, n), rd(1, n)};
    while(a.second == a.first) {
        a.second = rd(1, n);
    }
    return a;
}

void solve() {
    int n;
    cin >> n;
    vector<int> x(n + 1), y(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }
    if(n <= 6) {
        cout << "possible\n";
        return;
    }
    for(int t = 1; t <= 1000; t++) {
        int x1, y1, x2, y2;
        auto [u, v] = get(n);
        x1 = x[u], y1 = y[u], x2 = x[v], y2 = y[v];
        vector<int> b{0};
        for(int i = 1; i <= n; i++) {
            if(!ck(x1, y1, x2, y2, x[i], y[i])) {
                b.push_back(i);
            }
        }
        if(b.size() <= 5) {
            cout << "possible\n";
            return;
        }
        auto [p, q] = get(b.size() - 1);
        x1 = x[b[p]], y1 = y[b[p]], x2 = x[b[q]], y2 = y[b[q]];
        vector<int> c{0};
        for(int i = 1; i < b.size(); i++) {
            if(!ck(x1, y1, x2, y2, x[b[i]], y[b[i]])) {
                c.push_back(b[i]);
            }
        }
        if(c.size() <= 3) {
            cout << "possible\n";
            return;
        }
        bool ok = true;
        x1 = x[c[1]], y1 = y[c[1]], x2 = x[c[2]], y2 = y[c[2]];
        for(int i = 1; i < c.size(); i++) {
            if(!ck(x1, y1, x2, y2, x[c[i]], y[c[i]])) {
                ok = false;
                break;
            }
        }
        if(ok) {
            cout << "possible\n";
            return;
        }
    }
    cout << "impossible\n";
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
