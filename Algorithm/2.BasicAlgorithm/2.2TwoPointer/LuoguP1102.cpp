#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    ll c;
    cin >> n >> c;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    ll ans = 0;
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        while(a[i] - a[l] > c) l++;
        while(a[i] - a[r] >= c) r++;
        if(a[i] - a[l] == c) ans += r - l;
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
    
