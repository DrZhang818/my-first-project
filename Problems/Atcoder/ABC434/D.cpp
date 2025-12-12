#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 2000;

void solve() {
    vector a(N + 2, vector<int>(N + 2));
    int n;
    cin >> n;

    vector<array<int,4>> line(n + 1);
    for(int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        line[i] = {x1, y1, x2, y2};
        a[x1][y1]++;
        a[x2 + 1][y1]--;
        a[x1][y2 + 1]--;
        a[x2 + 1][y2 + 1]++;
    }
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }
    int tot = N * N;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            if(a[i][j] >= 1) {
                tot--;
            }
            if(a[i][j] > 1) {
                a[i][j] = 0;
            } 
        }
    }
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }
    for(int i = 1; i <= n; i++) {
        auto [x1, y1, x2, y2] = line[i];
        int ans = tot + (a[x2][y2] - a[x1 - 1][y2] - a[x2][y1 - 1] + a[x1 - 1][y1 - 1]);
        cout << ans << "\n";
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
