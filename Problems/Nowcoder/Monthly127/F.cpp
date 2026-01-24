#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, k;
    cin >> n >> k;
    vector<int> adj0, adj1, adj2;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        x %= 4;
        if(x == 0) {
            adj0.push_back(i);
        } else if(x & 1) {
            adj1.push_back(i);
        } else {
            adj2.push_back(i);
        }
    }
    if(n == 1) {
        cout << 1 << "\n";
        return;
    }
    int c0 = adj0.size(), c1 = adj1.size(), c2 = adj2.size();
    if(1LL * c0 * k < c1 - 1 || 1LL * c0 * k == c1 - 1 && c2 > 0) {
        cout << -1 << "\n";
        return;
    }
    vector<PII> ans;
    int root = -1;
    int j = 0;
    for(int i = 0; i < c0; i++) {
        int p = 0;
        if(root != -1) {
            ans.push_back({adj0[i], root});
        }
        root = adj0[i];
        for(; p < k && j < c1; p++, j++) {
            ans.push_back({adj0[i], adj1[j]});
            root = adj1[j];
        }
    }
    if(root == -1) {
        root = adj2[0];
    } else {
        if(j < c1) {
            ans.push_back({adj0[0], adj1[j]});
        }
        if(c2 > 0) {
            ans.push_back({adj0[0], adj2[0]});
        }
    }
    for(int i = 1; i < c2; i++) {
        ans.push_back({adj2[i], adj2[i - 1]});
    }
    assert(ans.size() == n - 1);
    cout << root << "\n";
    for(auto [u, v] : ans) {
        cout << u << " " << v << "\n";
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
