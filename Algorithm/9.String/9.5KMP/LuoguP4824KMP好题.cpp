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
    vector<int> nxt(m + 1);
    for(int i = 1; i < m; i++) {
        int j = nxt[i];
        while(j && t[i] != t[j]) j = nxt[j];
        nxt[i + 1] = t[i] == t[j] ? j + 1 : 0;
    }
    vector<int> to(n + 1);
    vector<int> ans(n + 1);
    int idx = 0, j = 0;
    for(int i = 0; i < n; i++) {
        ans[++idx] = i;
        while(j && s[i] != t[j]) j = nxt[j];
        if(s[i] == t[j]) j++;
        if(j == m) {
            idx -= m;
            j = to[ans[idx]];
        }
        to[i] = j;
    }
    for(int i = 1; i <= idx; i++) {
        cout << s[ans[i]];
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
