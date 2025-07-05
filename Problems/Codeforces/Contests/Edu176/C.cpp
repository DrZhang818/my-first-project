#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<int> a(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    vector<ll> pre(n + 2);
    for(int i = 1; i <= m; i++) {
        pre[1] += 1;
        pre[a[i] + 1] -= 1;
    }
    for(int i = 1; i <= n; i++) {
        pre[i] += pre[i - 1];
    }
    ll ans = 0;
    for(int i = 1; i <= n - i; i++) {
        if(i == n - i) {
            ans += pre[i] * (pre[i] - 1);
        } else {
            ans += 2 * (pre[i] * pre[n - i] - pre[n - i]);
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
    
