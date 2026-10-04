#include <bits/stdc++.h>
using namespace std;
// a[1..n]. qs are closed intervals; values are compressed internally.
vector<int> moDistinct(vector<int> a, const vector<pair<int, int>>& qs) {
    struct Q {
        int l, r, id;
    };
    int n = a.size() - 1, b = max(1, int(sqrt(max(1, n))));
    vector<Q> v;
    for(size_t i = 0; i < qs.size(); i++) {
        v.push_back(Q{qs[i].first, qs[i].second, int(i)});
    }
    sort(v.begin(), v.end(), [&](Q x, Q y) {
        int p = (x.l - 1) / b, q = (y.l - 1) / b;
        if(p != q) {
            return p < q;
        }
        return p & 1 ? x.r > y.r : x.r < y.r;
    });
    vector<int> values(a.begin() + 1, a.end());
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    int m = values.size();
    for(int i = 1; i <= n; i++) {
        a[i] = lower_bound(values.begin(), values.end(), a[i]) - values.begin();
    }
    vector<int> cnt(m), ans(qs.size());
    int l = 1, r = 0, sum = 0;
    auto add = [&](int i) {
        if(cnt[a[i]]++ == 0) {
            ++sum;
        }
    };
    auto del = [&](int i) {
        if(--cnt[a[i]] == 0) {
            --sum;
        }
    };
    for(size_t i = 0; i < v.size(); i++) {
        Q x = v[i];
        while(l > x.l) {
            add(--l);
        }
        while(r < x.r) {
            add(++r);
        }
        while(l < x.l) {
            del(l++);
        }
        while(r > x.r) {
            del(r--);
        }
        ans[x.id] = sum;
    }
    return ans;
}
