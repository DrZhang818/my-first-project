#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr i64 inf = 5E18;

struct Segment {
    i64 L, R;
};

void solve() {
    int n;
    cin >> n;
    vector<i64> X(n + 1), L(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> X[i];
    }    
    for(int i = 1; i <= n; i++) {
        cin >> L[i];
    }

    vector<vector<Segment>> a(n + 1);

    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            Segment cur {X[j] - L[i], X[j - i + 1] + L[i]};            
            if(!a[i].empty() && cur.L <= a[i].back().R) {
                a[i].back().R = cur.R;
            } else {
                a[i].emplace_back(move(cur));
            }
        }
    }

    vector<Segment> b;
    b.emplace_back(-inf, inf);

    for(int i = 1; i <= n; i++) {
        vector<Segment> nb;
        for(int j = 0, k = 0; j < b.size() && k < a[i].size(); ) {
            auto [l1, r1] = b[j];
            auto [l2, r2] = a[i][k];
            i64 lo = max(l1, l2);
            i64 hi = min(r1, r2);
            if(lo <= hi) {
                nb.emplace_back(lo, hi);
            }
            if(r1 < r2) {
                j++;
            } else {
                k++;
            }
        }
        b = move(nb);
    }

    i64 ans = 0;
    for(auto [l, r] : b) {
        ans += r - l + 1;
    }
    cout << ans << "\n";
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
