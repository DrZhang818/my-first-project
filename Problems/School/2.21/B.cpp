#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    string s, t;
    cin >> s >> t;
    for(int i = 0; i < t.size(); i++) {
      cout << s[i] << t[i];
    }
    if(s.size() != t.size()) {
      cout << s.back();
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
    
