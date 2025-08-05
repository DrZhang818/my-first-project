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
    vector<int> a(n + m + 2), b(n + m + 2);
    for(int i = 1; i <= n + m + 1; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n + m + 1; i++) {
        cin >> b[i];
    }
    vector<int> pre0(n + m + 2), pre1(n + m + 2);
    vector<ll> sum(n + m + 2), sum0(n + m + 2), sum1(n + m + 2);
    for(int i = 1; i <= n + m + 1; i++) {
        pre0[i] = pre0[i - 1] + (a[i] > b[i]);
        pre1[i] = pre1[i - 1] + (b[i] > a[i]);
        sum[i] = sum[i - 1] + max(a[i], b[i]);
        sum0[i] = sum0[i - 1] + a[i];
        sum1[i] = sum1[i - 1] + b[i];
    }
    int c0 = n, c1 = m;
    ll cur = 0;
    auto find = [&](int x, int st, vector<int> &pre) -> int {
        int l = st, r = n + m + 2;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(pre[mid] - pre[st] <= x) {
                l = mid;
            } else {
                r = mid;
            }
        }
        return l;
    };
    for(int i = 1; i <= n + m + 1; i++) {
        ll ans = 0;
        int pos0 = find(c0, i, pre0);
        int pos1 = find(c1, i, pre1);
        if(pos0 < pos1) {
            ans = cur + sum[pos0] - sum[i] + sum1[n + m + 1] - sum1[pos0];
        } else {
            ans = cur + sum[pos1] - sum[i] + sum0[n + m + 1] - sum0[pos1];
        }
        if(a[i] > b[i]) {
            if(c0) c0--, cur += a[i];
            else c1--, cur += b[i];
        } else {
            if(c1) c1--, cur += b[i];
            else c0--, cur += a[i];
        }
        cout << ans << " \n"[i == n + m + 1];
    }
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
