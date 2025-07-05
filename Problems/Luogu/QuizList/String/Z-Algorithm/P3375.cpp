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
    int j = 0;
    for(int i = 0; i < n; i++) {
        while(j && s[i] != t[j]) j = nxt[j];
        if(s[i] == t[j]) j++;
        if(j >= m) {
            cout << i - m + 2 << "\n";
            j = nxt[j];
        }
    }
    for(int i = 1; i <= m; i++) {
        cout << nxt[i] << " \n"[i == m];
    }
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
