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
void solve() {
    map<int,char> mp;
    mp[0] = 'A', mp[1] = 'C', mp[2] = 'G', mp[3] = 'T';
    int n;
    cin >> n;
    vector dp(4, vector(4, vector<int>(4, 1)));
    dp[0][1][2] = dp[0][2][1] = dp[2][0][1] = 0;
    for(int p = 3; p < n; p++) {
        vector ndp(4, vector(4, vector<int>(4)));
        for(int s = 0; s < 4; s++) {
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    for(int k = 0; k < 4; k++) {
                        if(i == 0 && k == 2 && s == 1) continue;
                        if(i == 0 && j == 2 && s == 1) continue;
                        if(k == 0 && j == 2 && s == 1) continue;
                        if(j == 0 && k == 2 && s == 1) continue;
                        if(j == 0 && s == 2 && k == 1) continue;
                        add(ndp[j][k][s], dp[i][j][k]);
                    }
                }
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                add(ans, dp[i][j][k]);
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
