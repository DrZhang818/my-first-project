#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, k;
    ll x;
    cin >> n >> k >> x;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    ll sum = pre[n];
    ll t = x / sum;
    x %= sum;
    if(t > k || t == k && x > 0) {
        cout << 0 << "\n";
        return;
    }
    int l = upper_bound(pre.begin() + 1, pre.end(), sum - x) - pre.begin() - 1;
    ll ans = (k - t - 1) * n + l + 1;
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
    
