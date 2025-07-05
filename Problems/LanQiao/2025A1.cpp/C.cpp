#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> a, b, c;
int cal(int u, int v, int w) {
    if(u == v && v == w) return 200;
    if(u == v - 1 && v == w - 1) return 200;
    if(u == v || v == w || u == w) return 100;
    vector<int> tmp(3);
    tmp[0] = u, tmp[1] = v, tmp[2] = w;
    sort(tmp.begin(), tmp.end());
    if(tmp[0] == tmp[1] - 1 && tmp[1] == tmp[2] - 1) return 100;
    return 0;
}
void solve() {
    int n;
    cin >> n;
    a.resize(n), b.resize(n), c.resize(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    for(int i = 0; i < n; i++) cin >> c[i];
    int m;
    cin >> m;
    int p1 = 0, p2 = 0, p3 = 0;
    ll ans = 0;
    for(int u = 1; u <= m; u++) {
        int i, j, k;
        cin >> i >> j >> k;
        p1 = (p1 + i) % n;
        p2 = (p2 + j) % n;
        p3 = (p3 + k) % n;
        ans += cal(a[p1], b[p2], c[p3]);
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
