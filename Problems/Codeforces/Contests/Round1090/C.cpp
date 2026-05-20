#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    int l = 1, r = n * 3;
    for(int i = 1; i <= 3 * n; i++) {
        if(i % 3 == 0) {
            cout << (l++) << " ";
        } else {
            cout << (r--) << " ";
        }
    }
    cout << "\n";
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