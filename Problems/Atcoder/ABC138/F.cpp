#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
int mod(int x) {
    return (x % MOD + MOD) % MOD;
}
int numL[64], numR[64];
int dp[64][2][2];

int dfs(int pos, bool limL, bool limR) {
    if(pos == 0) return 1;
    int &res = dp[pos][limL][limR];
    if(res != -1) return res;
    res = 0;
    int down = limL ? numL[pos] : 0, up = limR ? numR[pos] : 1;
    for(int y = down; y <= up; y++) {
        for(int x = down; x <= y; x++) {
            add(res, dfs(pos - 1, limL && x == down, limR && y == up));
        }
    }
    return res;
}
void solve() {
    ll l, r;
    cin >> l >> r;
    int lenL = 0, lenR = 0;
    while(l) {
        numL[++lenL] = l & 1;
        l >>= 1;
    }
    while(r) {
        numR[++lenR] = r & 1;
        r >>= 1;
    }
    int ans = 0;
    for(int i = lenL; i <= lenR; i++) {
        add(ans, dfs(i - 1, i == lenL, i == lenR));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(dp, -1, sizeof(dp));
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
