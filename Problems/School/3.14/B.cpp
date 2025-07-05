#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    ll ans = 0;
    vector<int> ord(n + 1);
    for(int i = 1; i <= n; i++) {   
        cin >> ord[i];
    }
    for(int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        ans += x;
    }
    vector<int> a(n + 1);
    for(int i = 1; i <= n - 1; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        if(i && ord[i] == ord[i - 1] + 1) {
            ans += a[ord[i - 1]];
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
