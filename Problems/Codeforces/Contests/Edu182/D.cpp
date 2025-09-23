#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;
const int N = 200000;

void solve() {
    int n, y;
    cin >> n >> y;
    int mx = 2;
    vector<int> cnt(N + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
        mx = max(mx, x);
    }

    vector<int> pre(mx + 1);
    for(int i = 1; i <= mx; i++) {
        pre[i] = pre[i - 1] + cnt[i];
    }

    ll ans = -inf;
    for(int x = 2; x <= mx; x++) {
        ll sum = 0;
        for(int i = 1; i <= (mx - 1) / x + 1; i++) {
            ll now_cnt = pre[min(mx, i * x)] - pre[(i - 1) * x];
            ll need = max(0LL, now_cnt - cnt[i]);
            sum += i * now_cnt - need * y;
        }
        ans = max(ans, sum);
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
