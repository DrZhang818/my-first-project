#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    string s;
    cin >> s;
    int ans = 0, n = s.size();
    bool ok = false;
    for(int i = n - 1; i >= 0; i--) {
        int x = s[i] - '0';
        if(x > 0) ans++, ok = true;
        else if(!ok) ans++;
        else continue;  
    }
    cout << ans - 1 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
