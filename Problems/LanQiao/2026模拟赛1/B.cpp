#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

int ans = 0;
int n = 5;
int a[5][5];

auto ck(int i, int j) {
    int x = a[i][j];
    int cnt = 0;
    for(int k = 0; k < 5; k++) {
        if(a[i][k] == x) {
            cnt++;
        }
    }
    if(cnt == 5) return false;
    cnt = 0;
    for(int k = 0; k < 5; k++) {
        if(a[k][j] == x) {
            cnt++;
        }
    }
    if(cnt == 5) return false;
    if(i == j) {
        cnt = 0;
        for(int k = 0; k < 5; k++) {
            if(a[k][k] == x) {
                cnt++;
            }
        }
        if(cnt == 5) return false;
    }
    if(i == n - 1 - j) {
        cnt = 0;
        for(int k = 0; k < 5; k++) {
            if(a[k][n - 1 - k] == x) {
                cnt++;
            }
        }
        if(cnt == 5) return false;
    }
    return true;
}

auto dfs(int i, int j, int c1, int c2) -> void {
    if(c1 == 0 && c2 == 0) {
        ans++;
        return;
    }
    int ni = j == n - 1 ? i + 1 : i;
    int nj = j == n - 1 ? 0 : j + 1;
    a[i][j] = 1;
    if(c1 - 1 >= 0 && ck(i, j)) {
        dfs(ni, nj, c1 - 1, c2);
    }
    a[i][j] = 2;
    if(c2 - 1 >= 0 && ck(i, j)) {
        dfs(ni, nj, c1, c2 - 1);
    }
    a[i][j] = 0;
}

void solve() {
    dfs(0, 0, 13, 12);
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