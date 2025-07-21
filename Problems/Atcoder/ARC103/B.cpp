#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int x, y;
};
void solve() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    ll dis, mx = -1;
    bool ok = true;
    for(int i = 1; i <= n; i++) {
        ll cur = abs(a[i].x) + abs(a[i].y);
        if(i == 1) dis = cur;
        else if(dis % 2 != cur % 2) {
            ok = false;
            break;
        }
        mx = max(mx, dis);
    }
    if(!ok) {
        cout << -1 << "\n";
        return;
    }
    
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
