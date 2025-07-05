#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    string s;
    cin >> s;
    int n = s.size();
    vector<int> lps(n + 1);
    for(int i = 1; i < n; i++) {
        int j = lps[i];
        while(j && s[i] != s[j]) j = lps[j];
        lps[i + 1] = s[i] == s[j] ? j + 1 : 0;
    }
    int mx = 0;
    for(int i = 1; i <= n - 1; i++) mx = max(mx, lps[i]);
    int cur = lps[n];
    while(cur > 0) {
        if(cur <= mx) {
            cout << s.substr(0, cur) << "\n";
            return ;
        }
        cur = lps[cur];
    }
    cout << "Just a legend\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
