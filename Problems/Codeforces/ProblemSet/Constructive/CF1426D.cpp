#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    map<ll,int> mp;
    int ans = 0;
    for(int i = 0; i <= n; i++) {
        if(mp[a[i]]) {
            mp.clear();
            mp[a[i - 1]]++;
            ans += 1;
        }
        mp[a[i]]++;
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
    
