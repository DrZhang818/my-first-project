#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;
    if(n < m) swap(n, m);

    if(n == m) {
        cout << 0 << " ";
        cout << 8;
        for(int i = 0; i < n - 1; i++) cout << 9;
        cout << "\n";
    } else {
        if(n > m + 1) {
            for(int i = 0; i < n - m - 1; i++) cout << 9;
            for(int i = 0; i < m - 1; i++) cout << 0;
        }    
        cout << 1 << " ";

        for(int i = 0; i < n - m; i++) cout << 9;
        cout << 8;
        for(int i = 0; i < m - 1; i++) cout << 9;
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}