#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

struct Info {
    int x, y, w;
    friend bool operator<(const Info& a, const Info& b) {
        return a.w > b.w;
    }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<Info> a;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int w;
            cin >> w;
            if(w) {
                a.emplace_back(i, j, w);
            }
        }
    }

    sort(a.begin(), a.end());
        
    int ans = 0, time = 0;
    int x = 0, y = 0;

    for(auto [nx, ny, w] : a) {
        int dis = abs(nx - x) + abs(ny - y);
        if(x == 0) dis = nx;
        int need = dis + 1 + nx;
        if(time + need > k) break;
        ans += w;
        time += dis + 1;
        x = nx;
        y = ny;
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