#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    int ans = 1;
    for(int i = 2; i * i <= n; i++) {
        if(n % i != 0) continue;
        int p = i;
        ans *= p;
        while(n % p == 0) {
            n /= p;
        }
    }
    ans *= n;
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
