#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    string s, t;
    cin >> s >> t;
    int c = 0;
    for(int i = 0; i < 3; i++) {
        c += (s[i] == t[i]);
    }
    cout << c << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
