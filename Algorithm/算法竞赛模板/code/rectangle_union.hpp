#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct CoverSeg {
    int n;
    const vector<i64>& ys;
    vector<int> cover;
    vector<__int128> len;
    CoverSeg(const vector<i64>& ys_)
        : n(int(ys_.size()) - 1), ys(ys_), cover(4 * max(1, n)), len(4 * max(1, n)) {
    }
    void pull(int p, int l, int r) {
        if(cover[p]) {
            len[p] = (__int128)ys[r + 1] - ys[l];
        } else if(l == r) {
            len[p] = 0;
        } else {
            len[p] = len[p << 1] + len[p << 1 | 1];
        }
    }
    void add(int p, int l, int r, int x, int y, int v) {
        if(x <= l && r <= y) {
            cover[p] += v;
            pull(p, l, r);
            return;
        }
        int m = (l + r) >> 1;
        if(x <= m) {
            add(p << 1, l, m, x, y, v);
        }
        if(y > m) {
            add(p << 1 | 1, m + 1, r, x, y, v);
        }
        pull(p, l, r);
    }
    void add(int l, int r, int v) {
        if(l <= r) {
            add(1, 0, n - 1, l, r, v);
        }
    }
    __int128 coveredLength() const {
        return n ? len[1] : 0;
    }
};
__int128 rectArea(const vector<array<i64, 4>>& rects) {
    struct Event {
        i64 x, y1, y2;
        int v;
    };
    vector<Event> events;
    vector<i64> ys;
    for(auto [x1, y1, x2, y2] : rects) {
        if(x1 > x2) {
            swap(x1, x2);
        }
        if(y1 > y2) {
            swap(y1, y2);
        }
        if(x1 == x2 || y1 == y2) {
            continue;
        }
        events.push_back({x1, y1, y2, 1});
        events.push_back({x2, y1, y2, -1});
        ys.push_back(y1);
        ys.push_back(y2);
    }
    if(events.empty()) {
        return 0;
    }
    sort(events.begin(), events.end(),
         [](const Event& a, const Event& b) { return a.x < b.x; });
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    CoverSeg seg(ys);
    __int128 ans = 0;
    i64 last = events[0].x;
    for(int i = 0, j; i < int(events.size()); i = j) {
        ans += (__int128)seg.coveredLength() * ((__int128)events[i].x - last);
        for(j = i; j < int(events.size()) && events[j].x == events[i].x; j++) {
            int l = int(lower_bound(ys.begin(), ys.end(), events[j].y1) - ys.begin());
            int r = int(lower_bound(ys.begin(), ys.end(), events[j].y2) - ys.begin()) - 1;
            seg.add(l, r, events[j].v);
        }
        last = events[i].x;
    }
    return ans;
}
