#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    ll x, v;
};
void solve() {
    int n;
    ll c;
    cin >> n >> c;
    vector<info> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].v;
        b[n - i + 1].x = c - a[i].x;
        b[n - i + 1].v = a[i].v;
    }
    vector<ll> prea(n + 1), preb(n + 1);
    vector<ll> disa(n + 1), disb(n + 1);
    vector<ll> mxa(n + 1), mxb(n + 1);
    for(int i = 1; i <= n; i++) {
        prea[i] = prea[i - 1] + a[i].v - (a[i].x - a[i - 1].x);
        preb[i] = preb[i - 1] + b[i].v - (b[i].x - b[i - 1].x);
        disa[i] = a[i].x;
        disb[i] = b[i].x;
        mxa[i] = max(mxa[i - 1], prea[i]);
        mxb[i] = max(mxb[i - 1], preb[i]);
    }
    ll ans = 0;
    for(int s = 0; s <= n; s++) {
        ll d = disb[s];
        ans = max(ans, preb[s] + mxa[n - s] - (s != n ? d : 0));
    }
    for(int s = 0; s <= n; s++) {
        ll d = disa[s];
        ans = max(ans, prea[s] + mxb[n - s] - (s != n ? d : 0));
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
