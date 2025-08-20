#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 i128;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 2000000007;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0) {
        x = 1; 
        y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
ll inv(ll a, ll p) {
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    i128 M = 1;
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
        M *= b[i];
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans = (ans + a[i] * (M / b[i]) % M * inv(M / b[i], b[i]) % M) % M;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
