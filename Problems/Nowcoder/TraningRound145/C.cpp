#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    rotate(a.begin() + 1, max_element(a.begin() + 1, a.end()), a.end());
    int mx = a[2];
    ll ans = 0;
    vector<int> suf(n + 1, a[n]);
    for(int i = n - 1; i >= 1; i--) {
        suf[i] = max(suf[i + 1], a[i]);
    }
    for(int i = 3; i < n; i++) {
        ans = max(ans, 1LL * (a[1] + a[i]) * (mx + suf[i + 1]));
        mx = max(mx, a[i]);
    }
    cout << ans << "\n";
}

// void solve() {
//     int n;
//     cin >> n;
//     vector<int> a(n + 1);
//     for(int i = 1; i <= n; i++) {
//         cin >> a[i];
//     }
//     ll ans = 0;
//     auto work = [&]() {
//         vector<int> suf(n + 1);
//         suf[n] = a[n];
//         for(int i = n - 1; i >= 1; i--) {
//             suf[i] = max(suf[i + 1], a[i]);
//         }
//         PII Lmx{0, 0}, Rmx{0, 0};
//         for(int i = 1; i < n; i++) {
//             if(Lmx.second) {
//                 auto [x1, x2] = Lmx;
//                 int x3 = a[i], x4 = suf[i + 1];
//                 ans = max(ans, 1LL * (x1 + x3) * (x2 + x4));
//             }
//             if(Rmx.first) {
//                 auto [x1, x2] = Rmx;
//                 int x3 = a[i], x4 = suf[i + 1];
//                 ans = max(ans, 1LL * (x1 + x3) * (x2 + x4));
//             }
//             if(a[i] >= Rmx.second) {
//                 Rmx.first = Rmx.second;
//                 Rmx.second = a[i];
//             }
//             if(a[i] > Lmx.second) {
//                 if(a[i] > Lmx.first) {
//                     Lmx.first = a[i];
//                     Lmx.second = 0;
//                 } else {
//                     Lmx.second = a[i];
//                 }
//             }
//         }
//     };
//     work();
//     reverse(a.begin() + 1, a.end());
//     work();
//     cout << ans << "\n";
// }

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
