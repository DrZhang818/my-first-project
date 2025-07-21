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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    auto ck = [&](int x) -> bool {
        ll cur = 0;
        for(int i = 1; i <= n; i++) {
            cur += max(0, a[i] - x);
        }
        return cur >= m;
    };
    int l = 0, r = 4e5 + 5;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l << "\n";
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
