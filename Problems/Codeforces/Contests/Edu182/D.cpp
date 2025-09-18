#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;
const int N = 200000;

void solve() {
    int n, w;
    cin >> n >> w;
    vector<int> a(n + 1);
    vector<int> cnt(N + 1);
    int mx = 2;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
        mx = a[i] > mx ? a[i] : mx;
    }
    ll ans = -inf;
    vector<int> pre(N + 1);
    for(int i = 1; i <= N; i++) {
        pre[i] = pre[i - 1] + cnt[i];
    }
    for(int x = 2; x <= mx; x++) {
        ll cur = 0;
        int L = 1;
        for(int t = 1; t <= (mx + x - 1) / x && L <= N; t++) {
            int R = x * t;
            R = min(R, N);
            cur += 1LL * t * (pre[R] - pre[L - 1]);
            cur -= 1LL * w * max(0, (pre[R] - pre[L - 1]) - cnt[t]);
            L = R + 1;
        }
        ans = max(ans, cur);
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
