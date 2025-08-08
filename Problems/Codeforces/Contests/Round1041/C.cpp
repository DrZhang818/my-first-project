#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<ll> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] > b[i]) {
            swap(a[i], b[i]);
        }
        ans += b[i] - a[i];
    }
    vector<int> ord(n + 1);
    for(int i = 1; i <= n; i++) {
        ord[i] = i;
    }
    sort(ord.begin() + 1, ord.end(), [&](auto x, auto y){
        return b[x] < b[y];
    });
    ll mx = b[ord[1]];
    ll mind = inf;
    for(int i = 2; i <= n; i++) {
        ll cur = a[ord[i]];
        if(cur <= mx) {
            mind = 0;
            break;
        }
        mind = min(mind, 2 * (cur - mx));
        mx = max(mx, b[ord[i]]);
    }
    cout << ans + mind << "\n";
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
