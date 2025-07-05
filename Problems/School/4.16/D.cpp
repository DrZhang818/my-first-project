#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

bool ck(string &s) {
    string t = s;
    reverse(t.begin(), t.end());
    return t == s;
}
void solve() { 
    string s;
    cin >> s;
    int n = s.size();
    for(int i = 0; i <= n; i++) {
        string t = s;
        t.insert(t.begin() + i, s[n - i - (i <= n - i)]);
        if(ck(t)) { cout << t << "\n"; return ; }
    }

    cout << "NA\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
