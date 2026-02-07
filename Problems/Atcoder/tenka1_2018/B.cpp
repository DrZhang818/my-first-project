#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    ll a, b, k;
    cin >> a >> b >> k;
    for(int i = 0; i < k; i++) {
        if(i % 2 == 0) {
            if(a & 1) a--;
            ll v = a / 2;
            a -= v;
            b += v;
        } else {
            if(b & 1) b--;
            ll v = b / 2;
            a += v;
            b -= v;
        }
    }
    cout << a << " " << b << "\n";
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
