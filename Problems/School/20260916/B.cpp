#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 1E6;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    vector<int> lo(k + 1), hi(k + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(!lo[a[i]]) lo[a[i]] = i;
        hi[a[i]] = i;
    }

    vector<i64> ans(k + 1);
    i64 sum = 0;
    int l = inf, r = 0;
    for(int i = k; i >= 1; i--) {
        if(lo[i] == 0) continue;
        l = min(l, lo[i]);
        r = max(r, hi[i]);
        sum = 2 * (r - l + 1);
        ans[i] = sum;
    }

    for(int i = 1; i <= k; i++) {
        cout << ans[i] << " \n"[i == k];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}