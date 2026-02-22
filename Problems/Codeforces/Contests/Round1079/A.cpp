#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    ll p, q;
    cin >> p >> q;
    if(p >= q) {
        cout << "Alice\n";
        return;
    }
    if(3 * p < 2 * q) {
        cout << "Alice\n";
        return;
    }
    cout << "Bob\n";    
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
