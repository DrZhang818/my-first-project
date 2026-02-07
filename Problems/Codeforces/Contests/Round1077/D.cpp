#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 100000;
constexpr int MOD = 998244353;

using B = bitset<N + 1>;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {  
    int n, x, y;
    cin >> n >> x >> y;

    string s;
    cin >> s;

    B b0, b1;
    b0.set(0);

    for(int i = 0; i < n; i++) {
        if(s[i] == '1') {
            swap(b0, b1);
        } else if(s[i] == '?') {
            b0 = b1 = b0 | b1;
        }
        b1 <<= 1;
    }

    b0 |= b1;

    vector<ll> val;
    for(int i = 0; i <= n; i++) {
        if(b0.test(i)) {
            val.push_back(1LL * x * (n - 2 * i) * (n - 2 * i + 1) / 2 + 1LL * y * i);
        }
    }

    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());

    int ans = 0;
    for(ll v : val) {
        add(ans, v % MOD);
    }

    cout << ans << "\n";

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // int n = 1;

    // for(int s = 0; s < 1 << n; s++) {
    //     int x = 0, y = 0;
    //     int sx = 0, sy = 0;
    //     for(int i = n - 1; i >= 0; i--) {
    //         if(s >> i & 1) {
    //             x = -x;
    //             y = -y;
    //             y++;
    //         } else {
    //             x++;
    //         }
    //         sx += x;
    //         sy += y;
    //     }
    //     cout << bitset<5>(s) << " : " << sx << " " << sy << "\n";
    // }

    // return 0;

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
