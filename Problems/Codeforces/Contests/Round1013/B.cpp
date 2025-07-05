#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    ll x;
    cin >> n >> x;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end(), greater<int>());
    int ans = 0;
    ll mn = 1000000000, cnt = 0; 
    for(int i = 1; i <= n; i++) {
        mn = min(mn, a[i]);
        cnt++;
        if(mn * cnt >= x) {
            ans++;
            mn = 1000000000, cnt = 0;
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
    
