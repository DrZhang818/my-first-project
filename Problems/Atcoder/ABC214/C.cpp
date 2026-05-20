#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr i64 inf = 1E18;

struct Info {
    int v;
    i64 w;
    friend bool operator<(const Info& a, const Info& b) {
        return a.w > b.w;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<i64> a(n + 1), t(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    priority_queue<Info> q;
    vector<i64> ans(n + 1, inf);
    for(int i = 1; i <= n; i++) {
        q.emplace(i, t[i]);
        ans[i] = t[i];
    }

    while(!q.empty()) {
        auto [u, w] = q.top(); q.pop();
        if(w != ans[u]) continue;
        int v = u % n + 1;
        if(w + a[u] < ans[v]) {
            ans[v] = w + a[u];
            q.emplace(v, ans[v]);
        }
    }

    for(int i = 1; i <= n; i++) {
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
