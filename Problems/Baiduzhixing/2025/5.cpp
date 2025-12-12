#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000007;

void solve() {
    ll n, d, l;
    cin >> n >> d >> l;
    ll mn = inf, mx = 0;
    ll k = (l - 1 - n) / d;
    mn = n * k;
    ll pos = 1 + k * d;
    if(pos + d >= l) {
        mn += 1;
    } else {
        ll start = pos + d;
        mn += 1 + l - start;
    }
    cout << mn << " ";
    mx = n * (l - 1 - n) + 1;
    cout << mx << "\n";
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