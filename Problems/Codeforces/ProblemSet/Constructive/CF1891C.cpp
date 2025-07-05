#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int l = 1, r = n;
    ll ans = 0, x = 0;
    while(l < r) {  
        if(x + a[l] < a[r]) {
            ans += a[l];
            x += a[l++];            
        } else {
            ans += a[r] - x + 1;
            a[l] -= a[r--] - x;
            if(a[l] == 0) l++;
            x = 0;
        }
    }
    ll p = max(0LL, (a[r] - x) / 2);
    ans += min((ll)a[r], a[r] - p - x + 1);
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
    
