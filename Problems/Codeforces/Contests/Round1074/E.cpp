#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < m; i++) {
        cin >> b[i];
    }
    string s;
    cin >> s;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    map<int,vector<int>> adj;
    for(int i = 0; i < n; i++) {
        auto it = lower_bound(b.begin(), b.end(), a[i]);
        if(it != b.end()) {
            adj[*it - a[i]].push_back(i);
        }
        if(it != b.begin()) {
            --it;
            adj[*it - a[i]].push_back(i);
        }
    }
    int rem = n, d = 0;
    vector<int> vis(n);
    for(int i = 0; i < k; i++) {
        d += s[i] == 'L' ? -1 : 1;
        for(auto x : adj[d]) {
            if(!vis[x]) {
                rem--;
                vis[x] = 1;
            }
        }
        adj[d].clear();
        cout << rem << " \n"[i == k - 1];
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
