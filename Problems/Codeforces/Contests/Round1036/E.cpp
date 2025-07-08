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
    vector<ll> a(n + 1);
    ll tot = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        tot += a[i];
    }
    if(a[i] & 1) {
        cout << -1 << "\n";
        return;
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
