#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    string s;
    cin >> s;
    string t = "$#";
    for(int i = 0; i < s.size(); i++) {
        t += s[i];
        t += "#";
    }
    t += "@";
    int n = t.size();
    vector<int> p(n + 1);
    for(int i = 1, c, r = 0; i < n; i++) {
        p[i] = i <= r ? min(p[2 * c - i], p[c] + c - i) : 1;
        while(t[i + p[i]] == t[i - p[i]]) p[i]++;
        if(i + p[i] - 1 > r) r = i + p[i] - 1, c = i;
    }
    int ans = 0;
    for(int i = 1; i < n; i++) {
        ans = max(ans, p[i] - 1);
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
    
