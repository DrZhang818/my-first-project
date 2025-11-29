#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    cout << 2 * ((n + 2) / 3) + (n + 1) / 2 - (n % 3 == 1 || n % 6 == 5) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
