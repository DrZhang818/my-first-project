#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;

    vector<pair<int,int>> a;

    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        if(x == 1) {
            a.emplace_back(1, 0);
            a.emplace_back(2, 1);
        } else {
            int cur = 0;
            while(1) {
                a.emplace_back(x, cur);                
                cur++;
                if(x == 1) break;
                x = x % 2 == 0 ? x / 2 : x + 1;
            }
        }
    }

    sort(a.begin(), a.end());

    int ans = inf;
    int m = a.size();

    for(int l = 0, r = 0; l < m; l = r) {
        int sum = 0;
        while(r < m && a[r].first == a[l].first) {
            sum += a[r].second;
            r++;
        }

        if(r - l != n) continue;
        ans = min(ans, sum);
    }

    cout << ans << "\n";
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