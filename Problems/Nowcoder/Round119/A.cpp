#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int x, y, p1, p2;
    cin >> x >> y >> p1 >> p2;
    if(x < y) {
        cout << "B\n";
    } else if(x > y) {
        cout << "A\n";
    } else {
        if(p1 < p2) {
            cout << "A\n";
        } else if(p1 > p2) {
            cout << "B\n";
        } else {
            cout << "C\n";
        }
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
