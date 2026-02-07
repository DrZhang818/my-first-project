#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    ll a, b, c;
    cin >> a >> b >> c;
    ll t = a + b + c;
    t /= 3;
    if(a < t || b < t || c < t || a - t >= 2 || b - t >= 2 || c - t >= 2) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }

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
