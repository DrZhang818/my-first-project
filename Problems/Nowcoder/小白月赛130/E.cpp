#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<int> tar(m + 1);
    vector<int> pos(k);
    for(int i = 0; i < k; i++) {
        cin >> pos[i];
        tar[pos[i]] = 1;
    }

    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if(a[i][j] == 1) {
                cnt++;
            }
        }
    }
    if(cnt != n * k) {
        cout << -1 << "\n";
        return;
    }

    i64 ans = 0;
    for(int i = n; i >= 1; i--) {
        for(int j : pos) {
            if(a[i][j] > 0) continue;
            for(int p = j + 1; p <= m; p++) {
                if(a[i][p] > 0) {
                    a[i][j] += 1;
                    a[i][p] -= 1;
                    ans += p - j;
                    break;
                }
            }
            if(a[i][j] == 0) {
                cout << -1 << "\n";
                return;
            }
        }
        for(int j = 1; j <= m; j++) {
            int d = a[i][j] - tar[j];
            a[i - 1][j] += d;
            a[i][j] -= d;
            ans += d;
        }
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
