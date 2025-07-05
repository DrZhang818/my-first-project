#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/268/C
void solve() {
    int n, m;
    cin >> n >> m;
    cout << min(n, m) + 1 << "\n";
    for(int i = n, j = 0; i >= 0 && j <= m; i--, j++) {
        cout << i << " " << j << "\n";
    }
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
