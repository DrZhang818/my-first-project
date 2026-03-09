#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int ans = inf;
    for(int i = 0; i < n; i++) {
        int c0 = 0, c1 = 0;
        auto& cur = a[i];
        for(int j = 0; j < m; j++) {
            if(cur[j] == 'x') {
                c0++;
            } else if(cur[j] == '.') {
                c1++;
            }
            if(j < k - 1) {
                continue;
            }
            if(c0 == 0) {
                ans = min(ans, c1);
            }
            if(cur[j - k + 1] == 'x') {
                c0--;
            } else if(cur[j - k + 1] == '.') {
                c1--;
            }
        }
    }

    for(int j = 0; j < m; j++) {
        int c0 = 0, c1 = 0;
        for(int i = 0; i < n; i++) {
            if(a[i][j] == 'x') {
                c0++;
            } else if(a[i][j] == '.') {
                c1++;
            }
            if(i < k - 1) {
                continue;
            }
            if(c0 == 0) {
                ans = min(ans, c1);
            }
            if(a[i - k + 1][j] == 'x') {
                c0--;
            } else if(a[i - k + 1][j] == '.') {
                c1--;
            }
        }
    }

    if(ans == inf) {
        cout << -1 << "\n";
        return;
    }
    cout << ans << "\n";
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
