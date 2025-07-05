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
    cout << 4 + n * 3 << "\n";
    cout << "0 0\n";
    cout << "1 0\n";
    for(int i = 1; i <= n; i++) {
        cout << i - 1 << " " << i << "\n";
        cout << i << " " << i << "\n";
        cout << i + 1 << " " << i << "\n";
    }
    cout << n << " " << n + 1 << "\n";
    cout << n + 1 << " " << n + 1 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
