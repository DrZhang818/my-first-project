#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    ll x, y;
};
void solve() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    sort(a.begin() + 1, a.end(),
        [&](auto u, auto v) {
            return abs(u.x + inf) + abs(u.y + inf) < abs(v.x + inf) + abs(v.y + inf);
        });
    ll u, v, s, x1, y1, x2, y2;
    cout << "? L " << inf << endl;
    cin >> s;
    cout << "? L " << inf << endl;
    cin >> s;
    cout << "? D " << inf << endl;
    cin >> s;
    cout << "? D " << inf << endl;
    cin >> s;
    v = s;
    x2 = a[1].x;
    y2 = a[1].y;
    sort(a.begin() + 1, a.end(),
        [&](auto u, auto v) {
            return abs(u.x + inf) + abs(u.y - inf) < abs(v.x + inf) + abs(v.y - inf);
        });
    cout << "? U " << inf << endl;
    cin >> s;
    cout << "? U " << inf << endl;
    cin >> s;
    cout << "? U " << inf << endl;
    cin >> s;
    cout << "? U " << inf << endl;
    cin >> s;
    u = s;
    x1 = a[1].x;
    y1 = a[1].y;
    ll p = x1 + x2 + y2 - y1 + 4LL * inf - u - v;
    ll q = x2 - x1 + y2 + y1 - 4LL * inf + u - v;
    p /= 2;
    q /= 2;
    cout << "! " << p + 2 * inf << " " << q + 2 * inf << endl;
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
