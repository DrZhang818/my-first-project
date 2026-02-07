#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int x, y;
    cin >> x >> y;
    if((x & y) == 0) {
        cout << x << " " << y << "\n";
        return;
    }

    ll p = 0, q = 0;
    ll mn = numeric_limits<ll>::max();
    ll u = 0, v = 0;
    for(int i = 30; i >= 0; i--) {

        for(auto s : {x & ((1 << i) - 1), (1 << i) - 1, 1 << i}) {
            for(auto t : {y & ((1 << i) - 1), (1 << i) - 1, 1 << i}) {
                ll a = u | s;
                ll b = v | t;
                ll cur = abs(a - x) + abs(b - y);
                if((a & b) == 0 && cur < mn) {
                    mn = cur;
                    p = a;
                    q = b;
                }
            }
        }

        u = x >> i << i;
        v = y >> i << i;
    }
    cout << p << " " << q << "\n";
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