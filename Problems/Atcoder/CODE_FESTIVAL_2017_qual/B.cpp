#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = 0; i <= m; i++) {
        for(int j = 0; j <= n; j++) {
            if(i * n + j * m - 2 * i * j == k) {
                cout << "Yes\n";
                return;
            }
        }
    }
    cout << "No\n";
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
