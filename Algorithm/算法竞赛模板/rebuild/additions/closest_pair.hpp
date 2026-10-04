#include <bits/stdc++.h>
using namespace std;
struct Point {
    long long x, y;
};
typedef __int128 i128;
const i128 CP_INF = i128(1) << 120;
i128 dist2(Point a, Point b) {
    i128 x = i128(a.x) - b.x, y = i128(a.y) - b.y;
    return x * x + y * y;
}
i128 closestPairSquared(vector<Point> a) {
    sort(a.begin(), a.end(),
         [](Point x, Point y) { return x.x < y.x || (x.x == y.x && x.y < y.y); });
    vector<Point> tmp(a.size());
    function<i128(int, int)> dfs = [&](int l, int r) -> i128 {
        if(r - l <= 3) {
            i128 d = CP_INF;
            for(int i = l; i < r; i++) {
                for(int j = i + 1; j < r; j++) {
                    d = min(d, dist2(a[i], a[j]));
                }
            }
            sort(a.begin() + l, a.begin() + r, [](Point x, Point y) { return x.y < y.y; });
            return d;
        }
        int m = (l + r) / 2;
        long long x = a[m].x;
        i128 d = min(dfs(l, m), dfs(m, r));
        merge(a.begin() + l, a.begin() + m, a.begin() + m, a.begin() + r, tmp.begin() + l,
              [](Point p, Point q) { return p.y < q.y; });
        copy(tmp.begin() + l, tmp.begin() + r, a.begin() + l);
        vector<Point> s;
        for(int i = l; i < r; i++) {
            i128 dx = i128(a[i].x) - x;
            if(dx * dx >= d) {
                continue;
            }
            for(int j = int(s.size()) - 1; j >= 0; j--) {
                i128 dy = i128(a[i].y) - s[j].y;
                if(dy * dy >= d) {
                    break;
                }
                d = min(d, dist2(a[i], s[j]));
            }
            s.push_back(a[i]);
        }
        return d;
    };
    return dfs(0, a.size());
}
