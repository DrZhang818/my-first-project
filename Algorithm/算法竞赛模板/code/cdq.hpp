#pragma once
#include <bits/stdc++.h>
using namespace std;
// For every point, count OTHER points with x<=X, y<=Y, z<=Z.
vector<long long> dominance(vector<array<int, 3>> p) {
    struct P {
        int x, y, z, c;
        long long ans = 0;
    };
    int n = p.size();
    vector<int> id(n), zs;
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int x, int y) { return p[x] < p[y]; });
    for(auto v : p) {
        zs.push_back(v[2]);
    }
    sort(zs.begin(), zs.end());
    zs.erase(unique(zs.begin(), zs.end()), zs.end());
    vector<P> a;
    vector<int> bel(n);
    for(int k : id) {
        int z = lower_bound(zs.begin(), zs.end(), p[k][2]) - zs.begin() + 1;
        if(a.empty() || a.back().x != p[k][0] || a.back().y != p[k][1] || a.back().z != z) {
            a.push_back({p[k][0], p[k][1], z, 0, 0});
        }
        bel[k] = a.size() - 1;
        ++a.back().c;
    }
    // Store the original group index as an additional array, then carry it through merges.
    struct Q {
        P p;
        int id;
    };
    vector<Q> v, buf;
    for(int i = 0; i < int(a.size()); i++) {
        v.push_back({a[i], i});
    }
    buf.resize(v.size());
    vector<int> bit(zs.size() + 1);
    auto add = [&](int x, int k) {
        for(; x < int(bit.size()); x += x & -x) {
            bit[x] += k;
        }
    };
    auto sum = [&](int x) {
        int s = 0;
        for(; x; x -= x & -x) {
            s += bit[x];
        }
        return s;
    };
    function<void(int, int)> dfs = [&](int l, int r) {
        if(r - l <= 1) {
            return;
        }
        int m = (l + r) / 2;
        dfs(l, m);
        dfs(m, r);
        int i = l, j = m, k = l;
        while(j < r) {
            while(i < m && v[i].p.y <= v[j].p.y) {
                add(v[i].p.z, v[i].p.c), buf[k++] = v[i++];
            }
            v[j].p.ans += sum(v[j].p.z);
            buf[k++] = v[j++];
        }
        for(int t = l; t < i; t++) {
            add(v[t].p.z, -v[t].p.c);
        }
        while(i < m) {
            buf[k++] = v[i++];
        }
        copy(buf.begin() + l, buf.begin() + r, v.begin() + l);
    };
    dfs(0, v.size());
    vector<long long> g(a.size()), ans(n);
    for(auto q : v) {
        g[q.id] = q.p.ans + q.p.c - 1;
    }
    for(int i = 0; i < n; i++) {
        ans[i] = g[bel[i]];
    }
    return ans;
}
