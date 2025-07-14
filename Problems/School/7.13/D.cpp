#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int r;
    cin >> r;
    if(r < 1200) {
        cout << "ABC\n";
    } else if(r < 2800) {
        cout << "ARC\n";
    } else {
        cout << "AGC\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
