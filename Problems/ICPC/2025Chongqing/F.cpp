#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    if(a > b) {
        cout << "Win\n";
    } else if(c > b) {
        cout << "WIN\n";
    } else {
        cout << "nowin\n";
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
