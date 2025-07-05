#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1), cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    ll tot = 0;
    for(int i = 1; i <= n; i++) {
        tot += cnt[i] * (cnt[i] - 1) / 2;
    }
    for(int i = 1; i <= n; i++) {
        ll cur = tot - cnt[a[i]] * (cnt[a[i]] - 1) / 2 + (cnt[a[i]] - 1) * (cnt[a[i]] - 2) / 2;
        cout << cur << "\n";
    }
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
