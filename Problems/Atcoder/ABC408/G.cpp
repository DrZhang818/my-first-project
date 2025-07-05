#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc408/tasks/abc408_g
PII get(ll a, ll b, ll c, ll d) {
    cerr << "(" << a << "," << b << ") (" << c << "," << d << ")\n";
    ll n = a / b;
    a -= n * b, c -= n * d;
    if(c > d) {
        return {n + 1, 1};
    }
    auto [p, q] = get(d, c, b, a);
    return {p * n + q, p};
}   
void solve() {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    auto [p, q] = get(a, b, c, d);
    cout << "ans: " << "(" << p << "," << q << ")" << "\n";
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
