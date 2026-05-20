#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    auto ck = [&](int x) -> bool {
        vector<int> stk;
        stk.reserve(n);
        for(int i = 1; i <= n; i++) {
            stk.push_back(a[i] >= x ? 1 : 0);
            while(stk.size() >= 3) {
                int m = stk.size();
                int x = stk[m - 3], y = stk[m - 2], z = stk[m - 1];
                if(x == 0 && y == 0 && z == 0) {
                    stk.pop_back();
                    stk.pop_back();
                } else if(x == 0 && y == 1 && z == 0) {
                    stk.pop_back();
                    stk.pop_back();
                } else {
                    break;
                }
            }
        }
        int d = 0;
        while(!stk.empty()) {
            d += stk.back() == 1 ? 1 : -1;
            stk.pop_back();
        }
        return d >= 0;
    };

    int l = 0, r = inf + 1;
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