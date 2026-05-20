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

    cout << l << "\n";
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