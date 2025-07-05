#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    auto ck = [&](int x) -> bool {
        int j = 1;
        ll cnt = 0;
        for(int i = n; i >= 1; i--) {
            while(j <= n && a[i] + a[j] < x) {
                j++;
            }
            cnt += n - j + 1;
        }
        return cnt >= m;
    };
    ll l = a[1] + a[1] - 1, r = a[n] + a[n] + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    ll cnt = 0, j = 1;
    ll ans = 0;
    for(int i = n; i >= 1; i--) {
        while(j <= n && a[i] + a[j] <= l) {
            j++;
        }
        cnt += n - j + 1;
        ans += a[i] * (n - j + 1) + pre[n] - pre[j - 1];
    }
    ans += l * (m - cnt);
    cout << ans << "\n";
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
