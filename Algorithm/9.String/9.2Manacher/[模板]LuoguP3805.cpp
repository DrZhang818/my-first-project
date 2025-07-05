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
    t += "&";
    int n = t.size();
    vector<int> P(n);
    int R = 0, C;
    for(int i = 1; i < n - 1; i++) {
        P[i] = i < R ? min(P[2 * C - i], P[C] + C - i) : 1;
        while(t[i + P[i]] == t[i - P[i]]) P[i]++;
        if(P[i] + i > R) R = P[i] + i, C = i;
    }
    int ans = 1;
    for(int i = 0; i < n; i++) ans = P[i] > ans ? P[i] : ans;
    cout << ans - 1 << "\n"; 
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}