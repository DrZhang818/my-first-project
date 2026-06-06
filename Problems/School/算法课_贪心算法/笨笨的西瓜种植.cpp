#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

struct Info {
    int l, r, t;
    friend bool operator<(const Info& a, const Info& b) {
        return a.r < b.r;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Info> a(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i].l >> a[i].r >> a[i].t;
    }

    sort(a.begin() + 1, a.end());
    vector<int> used(n + 1);

    for(int i = 1; i <= m; i++) {
        auto [l, r, t] = a[i];
        for(int j = l; j <= r; j++) {
            t -= used[j];
        }
        for(int j = r; j >= l && t > 0; j--) {
            if(!used[j]) {
                used[j] = 1;
                t--;
            }
        }
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += used[i];
    }

    cout << ans << "\n";
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