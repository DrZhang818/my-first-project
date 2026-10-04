#pragma once
#include <bits/stdc++.h>
using namespace std;
struct KthOffline {
    // type=0: add d copies of value x at pos. type=1: kth query on [l,r], answer id.
    struct Event {
        int type, pos, x, d, l, r, k, id;
    };
    vector<Event> a, buf;
    vector<int> bit, v, ans, side;
    int n;
    void add(int x, int d) {
        for(; x <= n; x += x & -x) {
            bit[x] += d;
        }
    }
    int sum(int x) {
        int s = 0;
        for(; x; x -= x & -x) {
            s += bit[x];
        }
        return s;
    }
    void dfs(int l, int r, int L, int R) {
        if(l == r) {
            return;
        }
        if(L == R) {
            for(int i = l; i < r; i++) {
                if(a[i].type == 1) {
                    ans[a[i].id] = v[L];
                }
            }
            return;
        }
        int m = (L + R) / 2, cnt = 0;
        for(int i = l; i < r; i++) {
            Event& e = a[i];
            side[i] = 0;
            if(e.type == 0) {
                if(e.x <= m) {
                    add(e.pos, e.d), side[i] = 1;
                }
            } else {
                int s = sum(e.r) - sum(e.l - 1);
                if(e.k <= s) {
                    side[i] = 1;
                } else {
                    e.k -= s;
                }
            }
            cnt += side[i];
        }
        for(int i = l; i < r; i++) {
            if(a[i].type == 0 && side[i]) {
                add(a[i].pos, -a[i].d);
            }
        }
        int x = l, y = l + cnt;
        for(int i = l; i < r; i++) {
            buf[side[i] ? x++ : y++] = a[i];
        }
        copy(buf.begin() + l, buf.begin() + r, a.begin() + l);
        dfs(l, l + cnt, L, m);
        dfs(l + cnt, r, m + 1, R);
    }
    vector<int> solve(int n_, vector<Event> e, int q) {
        n = n_;
        a = move(e);
        v.clear();
        for(Event e : a) {
            if(!e.type) {
                v.push_back(e.x);
            }
        }
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        for(Event& e : a) {
            if(!e.type) {
                e.x = lower_bound(v.begin(), v.end(), e.x) - v.begin();
            }
        }
        buf.resize(a.size());
        side.resize(a.size());
        bit.assign(n + 1, 0);
        ans.assign(q, 0);
        if(!a.empty()) {
            assert(!v.empty());
            dfs(0, a.size(), 0, v.size() - 1);
        }
        return ans;
    }
};
