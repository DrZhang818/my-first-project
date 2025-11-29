#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    if(n == 2) {
        cout << -1 << "\n";
    } else if(n == 3) {
        cout << "1 3\n2 3\n";
    } else if(n == 4) {
        cout << "1 2\n1 3\n1 4\n";
    } else if(n == 5) {
        cout << "1 3\n3 5\n5 2\n2 4\n";
    } else if(n == 6) {
        cout << "3 5\n5 2\n2 4\n2 6\n4 1\n";
    } else {
        for(int i = 3; i <= n - 1; i++) {
            cout << 2 << " " << i << "\n";
        }
        cout << 1 << " " << 6 << "\n";
        cout << 1 << " " << n << "\n";
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
