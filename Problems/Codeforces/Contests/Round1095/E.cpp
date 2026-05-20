#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    auto b = a;
    sort(a.begin() + 1, a.end());

    auto ck = [&](int x) -> bool {
        int mex = 0;
        vector<bool> vis(x), tag(n + 1);
        for(int i = 1; i <= n; i++) {
            if(a[i] < x && !vis[a[i]]) vis[a[i]] = true, tag[i] = true;
        }
        for(int i = 1; i <= n; i++) {
            while(mex < x && vis[mex]) mex++;
            if(tag[i]) continue;
            if(mex * 2 < a[i]) mex++;
        }
        while(mex < x && vis[mex]) mex++;
        return mex >= x;
    };

    int l = -1, r = n + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    int x = l;

    int mex = 0;
    vector<bool> vis(x), tag(n + 1);
    for(int i = 1; i <= n; i++) {
        if(a[i] < x && !vis[a[i]]) vis[a[i]] = true, tag[i] = true;
    }
    int cnt = 0;
    multiset<int> keep, used, cands;
    for(int i = 1; i <= n; i++) {
        while(mex < x && vis[mex]) mex++;
        if(tag[i]) {
            keep.insert(a[i]);
            continue;
        }
        if(mex * 2 < a[i]) {
            used.insert(a[i]);
            mex++;
        } else {
            cands.insert(a[i]);
        }
    }

    a = move(b);

    vector<int> ans(n + 1);

    for(int i = n; i >= 1; i--) {
        ans[i] = keep.size() + used.size();

        while(!keep.empty() && *keep.rbegin() >= ans[i]) {
            int x = *keep.rbegin();
            keep.extract(x);
            used.insert(x);
        }

        while(keep.size() + used.size() > ans[i]) {
            int x = *used.rbegin();
            used.extract(x);
            cands.insert
        }

        if(cands.contains(a[i])) {
            cands.extract(a[i]);
        } else if(used.contains(a[i])) {
            used.extract(a[i]);
            auto it = cands.lower_bound(a[i]);
            if(it != cands.end()) {
                used.insert(*it);
                cands.erase(it);
            }
        } else {
            keep.extract(a[i]);
            auto it = cands.upper_bound(2 * a[i]);
            if(it != cands.end()) {
                used.insert(*it);
                cands.erase(it);
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}