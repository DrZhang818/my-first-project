#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    string s, t;
    cin >> s >> t;
    s = "#" + s;
    t = "#" + t;
    int n = s.size() - 1, m = t.size() - 1;
    vector<int> z(m + 1);
    z[1] = m;   
    for(int i = 2, l, r = 0; i <= m; i++) {
        if(i <= r) z[i] = min(z[i - l + 1], r - i + 1);
        while(i + z[i] <= m && t[1 + z[i]] == t[i + z[i]]) z[i]++;
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    vector<int> p(n + 1);
    for(int i = 1, l, r = 0; i <= n; i++) {
        if(i <= r) p[i] = min(z[i - l + 1], r - i + 1);
        while(1 + p[i] <= m && i + p[i] <= n && t[1 + p[i]] == s[i + p[i]]) p[i]++;
        if(i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
    }
    ll msk = 0;
    for(int i = 1; i <= m; i++) {
        msk ^= (ll)i * (z[i] + 1);
    }
    cout << msk << "\n";
    msk = 0;
    for(int i = 1; i <= n; i++) {
        msk ^= (ll)i * (p[i] + 1);
    } 
    cout << msk << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
