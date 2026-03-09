#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr int MOD = 998244353;

void add(int& x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

auto mod(int x) {
    return (x % MOD + MOD) % MOD;
};

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<vector<int>> pos(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }

    vector<int> cnt(n + 1);
    vector<int> dp(n + 1), pre(n + 1);
    pre[0] = 1;

    int ans = 0;

    // for(int i = 1; i <= n; i++) {
    //     int x = a[i];
    //     cnt[x]++;

    //     if(cnt[x] >= x) {
    //         int L_idx = cnt[x] - x - 1;
    //         int L = L_idx >= 0 ? pos[x][L_idx] : 0;

    //         int j = pos[x][cnt[x] - x];

    //         dp[i] = mod(pre[j - 1] - dp[L]);
    //     }

    //     pre[i] = mod(pre[i - 1] + dp[i]);
    //     if(cnt[x] >= 2) {
    //         add(pre[i], MOD - dp[pos[x][cnt[x] - 2]]);
    //     }
    // }

    for(int i = 1; i <= n; i++) {
        int x = a[i];
        int L = -1;
        if(cnt[x] > 0) {
            L = pos[x][cnt[x] - 1];
        }

        int num = pre[i - 1];
        if(L != -1) {
            add(num, MOD - pre[L]);
        }

        int R_idx = cnt[x] + x - 1;
        if(R_idx < pos[x].size()) {
            int R = pos[x][R_idx];
            add(dp[R], num);     
            add(ans, num);
        }

        cnt[x]++;
        pre[i] = mod(pre[i - 1] + dp[i]);
    }

    cout << mod(pre[n] - 1) << "\n";
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
