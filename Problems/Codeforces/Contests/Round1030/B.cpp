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
    cout << 2 * n - 1 << "\n";
    for(int i = 1; i <= n; i++) {
        cout << i << " " << 1 << " " << i << "\n";
    }
    for(int i = n - 1; i >= 1; i--) {
        cout << i << " " << i + 1 << " " << n << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
