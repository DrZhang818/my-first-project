#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int dp[50][50][50];

bool dfs(int x, int y, int z) {
    if(x > y) swap(x, y);
    if(x > z) swap(x, z);
    if(y > z) swap(y, z);
    int &res = dp[x][y][z];
    if(res != -1) {
        return res;
    }
    int sum = x + y + z;
    int mn = sum / 3, mx = (sum + 2) / 3;
    if(x == mn && z == mx) {
        return res = 0;
    }
    int ok = 1;
    for(int p = x + 1; p <= (x + y) / 2; p++) {
        ok &= dfs(p, x + y - p, z);
    }
    for(int p = x + 1; p <= (x + z) / 2; p++) {
        ok &= dfs(p, y, x + z - p);
    }
    for(int p = y + 1; p <= (y + z) / 2; p++) {
        ok &= dfs(x, p, y + z - p);
    }
    return res = (ok ^ 1);
}
void solve() {
    for(int k = 0; k <= 50; k++) {
        for(int j = 0; j <= k; j++) {
            for(int i = 0; i <= j; i++) {
                if(dfs(i, j, k)) {
                    // cout << "Alice\n";
                
                } else {
                    cout << "i: " << i << " j: " << j << " k: " << k << " ";
                    cout << "Bob\n";
                }
            }
        }
        cout << "\n";
    }
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
