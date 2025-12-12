#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

constexpr int N = 5000;

void solve() {  
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    vector<int> dp(3 * N + 1), pre(3 * N + 1);
    for(int i = 1; i <= n; i++) {
        vector<int> ndp(3 * N + 1);
        for(int j = 0; j <= 3 * N; j++) {
            ndp[j] = dp[j] + abs(j - N - a[i]);
            if(j - k - 1 >= 0) {
                ndp[j] = min(ndp[j], pre[j - k - 1] + abs(j - N - a[i]));
            }
        }
        swap(dp, ndp);
        pre[0] = dp[0];
        for(int j = 1; j <= 3 * N; j++) {
            pre[j] = min(pre[j - 1], dp[j]);
        }
    }
    cout << *min_element(dp.begin(), dp.end()) << "\n";
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
