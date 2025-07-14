#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int cal(ll x) {
    int res = 0;
    while(x) {
        res += x % 10;
        x /= 10;
    }
    return res;
}
ll pow_10[16];
// void solve() {
//     pow_10[0] = 1;
//     for(int i = 1; i <= 15; i++) {
//         pow_10[i] = pow_10[i - 1] * 10;
//     }
//     int k;
//     cin >> k;
//     if(k <= 10) {
//         for(int i = 1; i <= k && i <= 9; i++) {
//             cout << i << "\n";
//         }
//         if(k == 10) {
//             cout << 19 << "\n";
//         }
//         return;
//     }
//     vector<ll> a(k + 1);
//     for(int i = 1; i <= 9; i++) {
//         a[i] = i;
//     }
//     a[10] = 19;
//     int c = 11;
//     ll x = 19, d = 0;
//     while(c <= k) {
//         ll res1 = (x + pow_10[d]) / cal(x + pow_10[d]);
//         ll res2 = (x + pow_10[d + 1]) / cal(x + pow_10[d + 1]);
//         if(res1 < res2) {
//             a[c++] = x + pow_10[d];
//             x += pow_10[d];
//         } else {
//             a[c++] = x + pow_10[d + 1];
//             x += pow_10[d + 1];
//         }
//         if(x / pow_10[d] >= 100) d++;
//     }
//     for(int i = 1; i <= k; i++) {
//         cout << a[i] << "\n";
//     }
// }

void solve() {
    int k;
    cin >> k;
    vector<pair<db,int>> a;
    for(int i = 1; i <= 1E7; i++) {
        a.push_back({1.0 * i / cal(i), i});
        // cerr << i << " " << 1.0 * i / cal(i) << "\n";
    }
    cerr << 1.0 * 30999 / cal(30999) << "\n";
    sort(a.begin(), a.end());
    vector<PII> b;
    int mx = 1;
    for(int i = 0; i < a.size(); i++) {
        if(a[i].second < mx) {
            continue;
        }
        b.push_back(a[i]);
        mx = max(mx, a[i].second);
    }
    for(int i = 0; i < 200; i++) {
        cout << b[i].second << " " << b[i].first << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}