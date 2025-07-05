#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> d(n + 2);
    for(int i = 1; i <= m; i++) {
        int L, R;
        cin >> L >> R;
        d[L]++;
        d[R + 1]--;
    }
    int mn = inf;
    for(int i = 1; i <= n; i++) {
        d[i] += d[i - 1];
        mn = min(mn, d[i]);
    }
    cout << mn << "\n";
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
