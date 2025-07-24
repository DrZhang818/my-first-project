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
    int n = s.size() - 1;
    int ans = inf;
    for(int i = 0; i <= n - 2; i++) {
        int cur = stoi(s.substr(i, 3));
        ans = min(ans, abs(cur - 753));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
