#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    cout << "YES\n";
    int x = 1, y = n / 2 + 1;
    for(int i = 1; i <= n; i++) {
        if(i & 1) {
            cout << y++ << " \n"[i == n];
        } else {
            cout << x++ << " \n"[i == n];
        }
    }
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
