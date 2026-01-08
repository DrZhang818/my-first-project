#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

// void solve() {  
//     int l, a, b;
//     cin >> l >> a >> b;
//     vector<int> vis(l);
//     int ans = a;
//     while(!vis[a]) {
//         vis[a] = true;
//         a = (a + b) % l;
//         ans = max(ans, a);
//     }
//     cout << ans << "\n";
// }

void solve() {
    int l, a, b;
    cin >> l >> a >> b;
    int g = gcd(l, b);
    cout << l - g + a % g << "\n";
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
