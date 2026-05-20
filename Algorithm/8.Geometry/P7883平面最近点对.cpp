#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

struct Point {
    i64 x, y;
};

i64 dist(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

void solve() {
    int n;
    cin >> n;
    vector<Point> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    sort(a.begin(), a.end(), 
        [&](const auto& p1, const auto& p2) {
            return p1.x < p2.x;
        });

    auto dfs = [&](auto&& self, int l, int r) -> i64 {
        if(r - l <= 1) return 1E18;
        if(r - l == 2) return dist(a[l], a[l + 1]);

        int mid = l + r >> 1;
        i64 mid_x = a[mid].x;

        i64 d = min(self(self, l, mid), self(self, mid, r));

        vector<Point> cands;
        for(int i = l; i < r; i++) {
            auto val = a[i].x - mid_x;
            if(val * val < d) {
                cands.emplace_back(a[i]);
            }
        }

        sort(cands.begin(), cands.end(),
            [&](const auto& p1, const auto& p2) {
                return p1.y < p2.y;
            });

        for(int i = 0; i < cands.size(); i++) {
            for(int j = i + 1; j < cands.size(); j++) {
                auto val = cands[j].y - cands[i].y;
                if(val * val >= d) break;
                d = min(d, dist(cands[i], cands[j]));
            }
        }
    
        return d;
    };

    cout << dfs(dfs, 0, n) << "\n";
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