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
    int need = 0;
    for(int i = 0; i < n; i++) {
        need += s[i] == 'a' ? 1 : -1;
    }
    map<int,int> mp;
    mp[0] = -1;
    int cur = 0, ans = n;
    for(int i = 0; i < n; i++) {
        cur += s[i] == 'a' ? 1 : -1;
        mp[cur] = i;
        if(mp.contains(cur - need)) {
            ans = min(ans, i - mp[cur - need]);
        }
    }
    if(ans == n) {
        ans = -1;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
