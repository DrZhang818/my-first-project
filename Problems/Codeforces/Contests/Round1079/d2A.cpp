#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int calc(int x) {
    int res = 0;
    while(x) {
        res += x % 10;
        x /= 10;
    }
    return res;
}

void solve() {  
    int x;
    cin >> x;
    int ans = 0;
    for(int d = 0; d <= 81; d++) {
        int y = x + d;
        if(calc(y) == d) {
            ans++;
        }
    }
    cout << ans << "\n";
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
