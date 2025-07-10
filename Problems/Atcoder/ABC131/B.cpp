#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, l;
    cin >> n >> l;
    vector<int> a(n + 1);
    int tot = 0;
    for(int i = 1; i <= n; i++) {
        a[i] = l + i - 1;
        tot += a[i];
    }
    int mn = inf, ans = -1;
    for(int i = 1; i <= n; i++) {
        int cur = abs(tot - (tot - a[i]));
        if(cur < mn) {
            mn = cur;
            ans = tot - a[i];
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
