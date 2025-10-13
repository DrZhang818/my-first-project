#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int h, d;
    cin >> h >> d;
    int ans = d;
    if(h == 1) {
        h++;
        ans += 1;
    }

    auto ck = [&](int x) -> bool {
        int ave = d / (x + 1);
        int rem = d % (x + 1);
        ll tot = h + x;
        ll need = 1LL * (1 + ave) * ave / 2 * (x + 1);
        need += 1LL * (ave + 1) * (rem);
        return need <= tot - 1;
    };

    int l = -1, r = d;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }

    ans += r;

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
