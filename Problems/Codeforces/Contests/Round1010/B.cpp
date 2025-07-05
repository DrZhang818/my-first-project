#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    ll x, n, m;
    cin >> x >> n >> m;
    ll mn = 0, mx = 0;
    ll t = x, tn = n, tm = m;

    while(t) {
        if(tm && t != 1) {
            t = (t + 1) / 2;
            tm--;
        } else if(tn) {
            t >>= 1;
            tn--;
        } else {
            mn = t;
            break;
        }
    }
    t = x, tn = n, tm = m;
    while(t) {
        if(tn) {
            t >>= 1;
            tn--;
        } else if(tm && t != 1) {
            t = (t + 1) / 2;
            tm--;
        } else {
            mx = t;
            break;
        }
    }
    cout << mn << " " << mx << "\n";
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
    
