#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    
    i64 g = 0;
    for(int i = 1; i <= n; i++) {
        i64 l, r;
        cin >> l >> r;
        if(l == r) {
            g = gcd(g, l);
        } else {
            g = 1;
        }
    }
    
    cout << g << "\n";
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
