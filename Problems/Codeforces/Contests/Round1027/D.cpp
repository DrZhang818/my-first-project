#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1e18;


void solve() {
    int n;
    cin >> n;
    vector<array<ll,2>> prex(n + 1), prey(n + 1), sufx(n + 2), sufy(n + 2);
    vector<ll> x(n + 1), y(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }
    if(n == 1) {
        cout << 1 << "\n";
        return ;
    }
    prex[0][0] = prey[0][0] = sufx[n + 1][0] = sufy[n + 1][0] = inf;
    prex[0][1] = prey[0][1] = sufx[n + 1][1] = sufy[n + 1][1] = -inf;
    for(int i = 1; i <= n; i++) {
        prex[i][0] = min(prex[i - 1][0], x[i]);
        prey[i][0] = min(prey[i - 1][0], y[i]);
        prex[i][1] = max(prex[i - 1][1], x[i]);
        prey[i][1] = max(prey[i - 1][1], y[i]);
    }
    for(int i = n; i >= 1; i--) {
        sufx[i][0] = min(sufx[i + 1][0], x[i]);
        sufy[i][0] = min(sufy[i + 1][0], y[i]);
        sufx[i][1] = max(sufx[i + 1][1], x[i]);
        sufy[i][1] = max(sufy[i + 1][1], y[i]);
    }
    ll ans = inf;
    for(int i = 1; i <= n; i++) {
        ll lx, rx, ly, ry;
        lx = min(prex[i - 1][0], sufx[i + 1][0]);        
        rx = max(prex[i - 1][1], sufx[i + 1][1]);        
        ly = min(prey[i - 1][0], sufy[i + 1][0]);        
        ry = max(prey[i - 1][1], sufy[i + 1][1]);
        ll a = rx - lx + 1, b = ry - ly + 1;
        if(a * b >= n) {
            ans = min(ans, a * b);
        } else {
            ans = min({ans, a * (b + 1), b * (a + 1)});
        }
    }
    cout << ans << "\n";
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
