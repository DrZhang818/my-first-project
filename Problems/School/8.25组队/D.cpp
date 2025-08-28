#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    ll l, r;
};
void solve() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    ll mn = 0, mx = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].r;
        mn += a[i].l;
        mx += a[i].r;
    }
    if(mn > 0 || mx < 0) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    ll rem = -mn;
    for(int i = 1; i <= n; i++) {
        ll x = min(rem, a[i].r - a[i].l);
        rem -= x;
        cout << a[i].l + x << " \n"[i == n];
    }
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
