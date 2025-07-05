#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    s = "#" + s;
    t = "#" + t;
    vector<int> z(m + 1);
    z[1] = m;
    for(int i = 2, l, r = 0; i <= m; i++) {
        if(i <= r) z[i] = min(z[i - l + 1], r - i + 1);
        while(t[1 + z[i]] == t[i + z[i]]) z[i]++;
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    vector<int> e(n + 1);
    for(int i = 1, l, r = 0; i <= n; i++) {
        if(i <= r) e[i] = min(z[i - l + 1], r - i + 1);
        while(1 + e[i] <= m && i + e[i] <= n && t[1 + e[i]] == s[i + e[i]]) e[i]++;
        if(i + e[i] - 1 > r) l = i, r = i + e[i] - 1;
    }
    ll ans = 0;
    for(int i = 1; i <= m; i++) {
        ans ^= (ll)i * (z[i] + 1);
    }
    cout << ans << "\n";
    ans = 0;
    for(int i = 1; i <= n; i++) {
        ans ^= (ll)i * (e[i] + 1);
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
    
