#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(2 * n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    vector<int> cnt(m + 1);
    cnt[0] = 1;
    vector<int> dp(2 * n + 1);
    ll cur = 0, ans = 0;
    for(int i = 1; i <= 2 * n - 1; i++) {
        cur = (cur + a[i]) % m;
        dp[i + 1] = cur;
        ans += cnt[cur];
        if(i <= n - 1) cnt[cur]++;
        if(i >= n - 1) {
            cnt[dp[i - n + 2]]--;
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
