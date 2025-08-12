#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P5906
struct info {
    int bid, l, r, qid;
    friend bool operator < (const info &a, const info &b) {
        if(a.bid != b.bid) return a.bid < b.bid;
        return a.r < b.r;
    }
};
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> v;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        v.emplace_back(a[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int sz = v.size();
    for(int i = 1; i <= n; i++) {
        a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
    }

    int q;
    cin >> q;
    int block = ceil(n / sqrt(2 * q));
    vector<int> ans(q + 1);
    vector<info> Q;
    int len = 0;
    vector<int> rmx(sz), rmn(sz), lmn(sz);
    auto add = [&](int x, int pos, bool tag) -> void {
        if(tag) {
            rmx[x] = pos;
            if(rmn[x] == 0) rmn[x] = pos;
            len = max(len, pos - rmn[x]);
        } else {
            if(lmn[x] == 0) lmn[x] = pos;
            if(rmx[x]) len = max(len, rmx[x] - pos);
            len = max(len, pos - lmn[x]);
        }
    };
    for(int i = 1; i <= q; i++) {
        int l, r;
        cin >> l >> r;
        if(r - l + 1 > block) {
            Q.emplace_back(l / block, l, r, i);
            continue;
        }
        for(int j = l; j <= r; j++) {
            add(a[j], j, 1);
        }
        ans[i] = len;
        for(int j = l; j <= r; j++) {
            rmx[a[j]] = rmn[a[j]] = 0;
        }
        len = 0;
    }
    sort(Q.begin(), Q.end());
    for(int i = 0, R = 0; i < Q.size(); i++) {
        auto [bid, l, r, qid] = Q[i];
        int l0 = (bid + 1) * block;
        if(i == 0 || bid != Q[i - 1].bid) {
            if(i != 0) {
                for(int j = (Q[i - 1].bid + 1) * block; j <= R; j++) {
                    rmx[a[j]] = rmn[a[j]] = 0;
                }
            }
            len = 0;
            R = l0;
        }
        for(; R <= r; R++) {
            add(a[R], R, 1);
        }
        int tlen = len;
        for(int j = l; j < l0; j++) {
            add(a[j], j, 0);
        }
        ans[qid] = len;
        for(int j = l; j < l0; j++) {
            lmn[a[j]] = 0;
        }
        len = tlen;
    }
    for(int i = 1; i <= q; i++) {
        cout << ans[i] << "\n";
    }
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
