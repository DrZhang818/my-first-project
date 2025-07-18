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
    vector<int> a(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
    }
    int l = 1, r = n;
    vector<int> vis(n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        if(vis[a[i]]) {
            l = i;
            break;
        }
        vis[a[i]] = 1;
    }
    vis.assign(n + 1, 0);
    for(int i =  2 * n; i >= 1; i--) {
        if(vis[a[i]]) {
            r = i;
            break;
        }
        vis[a[i]] = 1;
    }
    swap(a[l], a[r]);
    vis.assign(n + 1, 0);
    ll ans = 0;
    for(int i = 1; i <= 2 * n; i++) {
        if(vis[a[i]]) {
            ans += i - vis[a[i]] - 1;
        }
        vis[a[i]] = i;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
