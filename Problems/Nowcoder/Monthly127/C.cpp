#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    if(n <= 2 || n == 4) {
        cout << -1 << "\n";
        return;
    }
    if(~n & 1) {
        cout << "1 2 1 ";
        n -= 3;
    }
    for(int i = 1; i <= n; i++) {
        cout << min(i, n - i + 1) << " \n"[i == n];
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
