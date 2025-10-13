#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int v, col;
};
void solve() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].v;
        mx = max(mx, a[i].v);
    }
    for(int i = 1; i <= n; i++) {
        cin >> a[i].col;
    }

    auto ck = [&](int x) -> bool {
        multiset<int> st0, st1;
        for(int i = 1; i <= n; i++) {
            auto [v, col] = a[i];
            if(col == 0) {
                if(st1.empty()) {
                    st0.insert(v);
                } else {
                    auto it = st1.lower_bound(x - v);                    
                    if(it == st1.end()) {
                        return false;
                    }
                    st1.erase(it);
                }
            } else {
                if(st0.empty()) {
                    st1.insert(v);
                } else {
                    auto it = st0.lower_bound(x - v);
                    if(it == st0.end()) {
                        return false;
                    }
                    st0.erase(it);
                }
            }
        }
        return true;
    };

    int l = 0, r = 2 * mx + 1;
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
    while(t--) {
        solve();
    }
    return 0;
}
