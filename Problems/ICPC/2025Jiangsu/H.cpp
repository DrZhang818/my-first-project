#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> dp(n);
    vector<int> idx(26, -1);
    string s;
    cin >> s;
    vector<vector<int>> p(26);
    vector<int> cnt(26);
    for(int i = 0; i < n; i++) {
        int x = s[i] - 'a';
        dp[i] = 1;
        for(int c = 0; c < 26; c++) {
            if(idx[c] + 1 < p[c].size() && p[c][idx[c] + 1] + k < i) {
                idx[c]++;
            }
            if(idx[c] != -1) {
                add(dp[i], dp[p[c][idx[c]]]);
            }
        }
        p[x].push_back(i);
        cnt[x] = dp[i];
    }
    int ans = 0;
    for(int i = 0; i < 26; i++) {
        add(ans, cnt[i]);
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
