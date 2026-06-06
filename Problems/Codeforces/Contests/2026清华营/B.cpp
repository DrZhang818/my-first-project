#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    i64 a, b, c;
    cin >> a >> b >> c;

    i64 cur = a + b;

    int lg = __lg(b);
    for(int i = 60; i >= lg; i--) {
        if((cur >> i & 1) != (c >> i & 1)) {
            cout << "NO\n";
            return;
        }
    }
    
    for(int i = lg - 1; i >= 0; i--) {
        if((cur >> i & 1) == (c >> i & 1)) {
            b >>= 2;
        } else if((cur >> i & 1) == 0 && (c >> i & 1)) {
            b >>= 1;
        } else {
            cout << "NO\n";
            return;
        }
        cur += b;
    }
    if(cur == c) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}