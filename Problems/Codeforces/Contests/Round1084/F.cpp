#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        adj[y].push_back(x);
    }

    i64 ans = 0;
    vector<i64> pre(n + 1);

    i64 sum = 0;
    priority_queue<int, vector<int>, greater<int>> pq;

    for(int y = n; y >= 0; y--) {
        for(auto x : adj[y]) {
            pq.push(x);
            sum += x;
        }
        while(pq.size() > y + 1) {
            sum -= pq.top();
            pq.pop();
        }
        ans = max(ans, sum);
        if(pq.size() == y + 1) {
            pre[y] = max(pre[y], sum - pq.top());
        } else {
            pre[y] = max(pre[y], sum);
        }
    }

    for(int i = 1; i <= n; i++) {
        pre[i] = max(pre[i], pre[i - 1]);
    }

    for(int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        i64 res = max(ans, pre[y] + x);
        cout << res << " \n"[i == m];
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
