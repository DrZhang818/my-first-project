#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

ll power2(ll x) { return x * x; }

void solve() {  
    ll a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    ll dis1 = power2(c - a) + power2(d - b);
    ll dis2 = power2(e - c) + power2(f - d);
    ll dis3 = power2(e - a) + power2(f - b);
    if(dis1 == dis2 && dis1 == dis3 && dis1 != 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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
