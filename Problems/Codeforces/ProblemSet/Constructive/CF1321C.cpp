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
    s = "#" + s;
    int ans = 0;
    vector<bool> vis(n + 1);
    for(int i = 2; i <= n; i++) {
        for(int j = i - 1; j >= 1; j--) {
            if(s[j] == s[i] - 1) {
                vis[i] = true;
                ans += 1;
            }
            if(s[j] == s[i] + 1 && !vis[j]) {
                vis[j] = true;
                ans += 1;
            }
            if(s[j] < s[i] || !vis[j]) {
                break;
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
