#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = "0" + s;
    int ans = n;
    for(int i = 1; i <= n; i++) if(s[i] != s[i - 1]) ans++;
    int t1 = 0, t2 = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '0' && s[i - 1] == '1') t1++;
        if(s[i] == '1' && s[i - 1] == '0') t2++;
    }
    if(t1 >= 2 || t2 >= 2) ans -= 2;
    else if(t1 && t2) ans -= 1;
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
