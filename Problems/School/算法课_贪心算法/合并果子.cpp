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
    priority_queue<int, vector<int>, greater<int>> q;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        q.push(x);
    }

    i64 ans = 0;
    while(q.size() > 1) {
        int u = q.top(); q.pop();
        int v = q.top(); q.pop();
        ans += u + v;
        q.push(u + v);
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