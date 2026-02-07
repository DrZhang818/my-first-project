#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    ll n;
    cin >> n;
    int bit = __lg(n) + 1;
    ll k = 1LL << bit;
    cout << n * k << " " << n * (k + 1) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int n = 1; n <= 100; n++) {
        for(int i = 1; i <= 100; i++) {
            for(int j = i + 1; j <= 100; j++) {
                if(gcd(i, j) != 1) continue;
                int x = n * i, y = n * j;
                if((x ^ y) < n) {
                    cerr << n << " " << x << " " << y << "\n";
                }
            }
        }
    }
    return 0;

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
