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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        int c = 0;
        if(i == 1) {
            c = __builtin_popcount(a[2]);
        } else if(i == n) {
            c = __builtin_popcount(a[n - 1]);
        } else {
            c = __builtin_popcount(a[i - 1] & a[i + 1]);
        }
        ans += (1LL << c) - 1;
    }    
    cout << ans << "\n";
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
