#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

auto dfs(int n, int x, int y) -> int {
    if(n == 0) return 0;

    int mid = 1 << n - 1;
    int cnt = mid * mid;

    if(x <= mid && y <= mid) 
        return dfs(n - 1, y, x);
    if(x <= mid && y > mid)  
        return dfs(n - 1, x, y - mid) + cnt;
    if(x > mid && y > mid)   
        return dfs(n - 1, x - mid, y - mid) + cnt * 2;
    return dfs(n - 1, mid - y + 1, 2 * mid - x + 1) + cnt * 3;
}

void solve() {
    int n, x, y;
    cin >> n >> x >> y;

    cout << dfs(n, x, y) + 1;
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