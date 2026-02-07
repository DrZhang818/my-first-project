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
    if(n == 1) {
        cout << "YES\n";
        cout << 1 << "\n";
        return;
    }
    if(n == 3) {
        cout << "YES\n";
        cout << 1 << " " << 2 << " " << 3 << "\n";
        return;
    }
    cout << "NO\n";
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
