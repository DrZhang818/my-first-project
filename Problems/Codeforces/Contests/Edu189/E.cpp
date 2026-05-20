#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, r;
    cin >> n >> r;
    vector<pair<i64, i64>> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    i64 diff = sqrt(3.0 * r * r) + 1;
    set<pair<i64, i64>> ans;

    for(auto [x, y] : a) {
        i64 vx = round(x / (2.0 * r));
        i64 vy = round(y / db(diff));

        for(i64 nx = vx - 3; nx <= vx + 3; nx++) {
            for(i64 ny = vy - 3; ny <= vy + 3; ny++) {
                i64 cx = ny % 2 == 0 ? nx * 2 * r : nx * 2 * r + r;
                i64 cy = ny * diff;

                i64 dx = x - cx;
                i64 dy = y - cy;
                if(dx * dx + dy * dy <= r * r) {
                    ans.insert({cx, cy});
                }
            }
        }
    }

    cout << ans.size() << "\n";
    for(auto [cx, cy] : ans) {
        cout << cx << " " << cy << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}