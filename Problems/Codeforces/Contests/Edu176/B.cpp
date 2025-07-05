#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    if(k == 1) {
        ans = a[1] + a[n];
        ll mx = max(a[1], a[n]);
        for(int i = 2; i <= n - 1; i++) {
            ans = max(ans, a[i] + mx);
        }
    } else {
        sort(a.begin() + 1, a.end(), greater<ll>());
        for(int i = 1; i <= k + 1 && i <= n; i++) {
            ans += a[i];
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
