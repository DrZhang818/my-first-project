#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    auto ck = [&](int x, int o, int k) -> bool {
        int l = lower_bound(a.begin() + 1, a.end(), o - x) - a.begin();
        int r = upper_bound(a.begin() + 1, a.end(), o + x) - a.begin() - 1;
        return r - l + 1 >= k;
    };
    for(int i = 1; i <= q; i++) {
        int b, k;
        cin >> b >> k;
        int l = -1, r = inf;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(ck(mid, b, k)) {
                r = mid;
            } else {
                l = mid;
            }
        }
        cout << r << "\n";
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
