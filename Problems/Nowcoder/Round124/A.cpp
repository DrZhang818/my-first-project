#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int x, y;
    cin >> x >> y;
    if(x == y) {
        cout << "Draw\n";
    } else if(x > y) {
        cout << "Alice\n";
    } else {
        cout << "Bob\n";
    }
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
