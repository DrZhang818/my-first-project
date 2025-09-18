#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int a, b;
    cin >> a >> b;
    if(a == b) {
        cout << 0 << "\n";
    } else if(a % b == 0 || b % a == 0) {
        cout << 1 << "\n";
    } else {
        cout << 2 << "\n";
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
