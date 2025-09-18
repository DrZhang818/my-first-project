#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int d, lo;
    friend bool operator < (const info &a, const info &b) {
        return a.lo < b.lo;
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    ll ans = 0;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        ans += a[i];
    }
    vector<info> b(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> b[i].lo;
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i].d;
    }
    sort(a.begin() + 1, a.end());
    sort(b.begin() + 1, b.end());
    priority_queue<int> q;
    int j = 1;
    for(int i = 1; i <= n; i++) {
        while(j <= m && b[j].lo <= a[i]) {
            q.push(b[j].d);
            j++;
        }
        if(!q.empty()) {
            ans -= q.top();
            q.pop();
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
