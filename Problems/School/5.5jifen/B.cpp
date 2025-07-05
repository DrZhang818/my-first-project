#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    string s;
    cin >> s;
    int n = s.size();
    s = "#" + s;
    int ans = 0;
    for(int l = 1, r = n; l < r; l++, r--) {
        ans += s[l] != s[r];
    }
    cout << ans << "\n";
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
