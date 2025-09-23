#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 2E18;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    int _or = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        _or |= a[i];
    }

    int base = __builtin_popcount(_or);

    vector<ll> cost{0};

    int x = _or;
    for(int i = 0; i <= 30; i++) {
        if(x >> i & 1) {
            continue;
        }
        ll cur = cost.back();
        for(int j = i; j >= 0; j--) {
            int u = (1 << j) - 1;
            int mx = 1;
            bool ok = false;
            for(int k = 1; k <= n; k++) {
                if(a[k] >> j & 1) {
                    ok = true;
                    break;
                }
                if((a[k] & u) > (a[mx] & u)) {
                    mx = k;
                }
            }
            if(ok) {
                continue;
            }
            cur += u + 1 - (a[mx] & u);
            a[mx] &= ~u;
            a[mx] |= (u + 1);
        }
        cost.push_back(cur);
    }

    while(q--) {
        int b;
        cin >> b;
        auto it = upper_bound(cost.begin(), cost.end(), b) - cost.begin();
        it--;
        cout << base + it << "\n";
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
