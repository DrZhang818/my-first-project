#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

bitset<466> dp[31];

void solve() {
    int n, k;
    cin >> n >> k;
    k = n * (n + 1) / 2 - k;
    if(!dp[n][k]) {
        cout << 0 << "\n";
        return;
    }
    vector<int> ans;
    for(int i = 1; i <= 30 && n > 0; i++) {
        if(dp[n - i][k - i * (i + 1) / 2]) {
            for(int j = i; j >= 1; j--) {
                ans.push_back(n - j + 1);
            }
            n -= i;
            k -= i * (i + 1) / 2;
            i--;
        }
    }
    for(int x : ans) {
        cout << x << " \n"[x == ans.back()];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

  
    dp[0][0] = 1;
    for(int i = 0; i < 30; i++) {
        for(int j = 1; i + j <= 30; j++) {
            dp[i + j] |= dp[i] << (j * (j + 1) / 2);
        }
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
