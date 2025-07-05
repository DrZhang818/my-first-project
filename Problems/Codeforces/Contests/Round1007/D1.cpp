#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n;
    ll l, r;
    cin >> n >> l >> r;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> pre(n + 1, 0);
    for(int i = 1; i <= n; i++) {
        pre[i] = (pre[i - 1] ^ a[i]);
    }
    int t = pre[n];
    if(l <= n) {
        cout << a[l] << "\n";
        return;
    }
    ll x = l / 2, ans = 0;
    if(x <= n) {
        ans = pre[x];
    } else {
        ll cnt = x - n;
        if((n + 1) % 2 == 0) {
            if(cnt % 2 == 0) {
                ans = t;
            } else {
                ans = (t ^ pre[(n + 1) / 2]);
            }
        } else {
            if(cnt == 0) {
                ans = t;
            } else {
                int cur = (t ^ pre[(n + 1) / 2]);
                if((cnt - 1) % 2 == 1) {
                    cur ^= pre[(n + 2) / 2];
                }
                ans = cur;
            }
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
    
