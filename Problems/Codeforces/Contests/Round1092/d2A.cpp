#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= k; i++) {
        int x;
        cin >> x;
    }
    vector<vector<int>> adj(k + 2); 
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        adj[x].push_back(i);
    }
    vector<int> ans;
    for(int i = k; i >= 1; i--) {
        for(int j : adj[i]) {
            for(int p = 0; p < k + 1 - i; p++) {
                ans.push_back(j);
            }
        }
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " \n"[i == ans.size() - 1];
    }
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