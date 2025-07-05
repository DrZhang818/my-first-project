#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    string s, t;
    cin >> s >> t;
    int a, b;
    cin >> a >> b;
    string ss;
    cin >> ss;
    if(ss == s) a--;
    else b--;
    cout << a << " " << b << "\n";    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
