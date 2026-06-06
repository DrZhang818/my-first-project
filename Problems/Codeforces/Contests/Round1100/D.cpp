#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    auto ck = [&](int x) -> bool {
        vector<int> stk;
        int c0 = 0, c1 = 0;
        for(int i = 1; i <= n; i++) {
            int u = a[i] >= x;
            int v = b[i] >= x;
            if(u == 1 && v == 1) {
                stk.push_back(1);
                c1++;
            } else if(u == 0 && v == 0) {
                if(stk.empty() || stk.back() != 0) {
                    stk.push_back(0);
                    c0++;
                }
            }
        }
        return c1 > c0;
    };

    int l = 0, r = 2 * n + 1;
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
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}