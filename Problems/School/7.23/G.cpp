#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int num[11];
int dp[11][2][2][2][2][2];
int dfs(int pos, bool tag7, bool tag5, bool tag3, bool lead, bool lim) {
    if(pos == 0) {
        return tag3 && tag5 && tag7 && !lead;
    }
    int &res = dp[pos][tag7][tag5][tag3][lead][lim];
    if(res != -1 && !lead && !lim) return res;
    int up = lim ? num[pos] : 9;
    int cur = 0;
    for(int i = 0; i <= up; i++) {
        if(i == 0 && lead) cur += dfs(pos - 1, tag7, tag5, tag3, true, lim && i == up);
        if(i != 3 && i != 5 && i != 7) continue;
        if(i == 3) cur += dfs(pos - 1, tag7, tag5, true, false, lim && i == up);
        if(i == 5) cur += dfs(pos - 1, tag7, true, tag3, false, lim && i == up);
        if(i == 7) cur += dfs(pos - 1, true, tag5, tag3, false, lim && i == up);
    }
    if(!lead && !lim) res = cur;
    return cur;
}

int work(int n) {
    int c = 0;
    while(n) {
        num[++c] = n % 10;
        n /= 10;
    }
    return dfs(c, false, false, false, true, true);
}

void solve() {
    memset(dp, -1, sizeof(dp));
    int n;
    cin >> n;
    int ans = work(n);
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
