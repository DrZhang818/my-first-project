#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
db eps = 1E-7;
void solve() {
    int n;
    cin >> n;
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll mn = a[1], mx = a[1];
    for(int i = 2; i <= n; i++) {
        if(mn - a[i] <= eps && mx - a[i] >= eps) {
            mn = 0;
        } else {
            mn = min(abs(mx - a[i]), abs(mn - a[i]));
        }
        mx += a[i];
    }
    db dis = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    if(dis >= mn - eps && dis <= mx + eps) { 
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
