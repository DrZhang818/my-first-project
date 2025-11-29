#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<array<int,3>> vec;
    array<int,3> mn{-1, -1, -1}, mx{-1, -1, -1};
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 3; j++) {
            if(mn[j] != -1) {
                vec.push_back({a[i] - a[mn[j]], mn[j], i});
            } 
        }
        int v = i;
        for(int j = 0; j < 3 && v != -1; j++) {
            if(mn[j] == -1 || a[v] < a[mn[j]]) {
                swap(v, mn[j]);
            }
        }
    }
    for(int i = n; i >= 1; i--) {
        for(int j = 0; j < 3; j++) {
            if(mx[j] != -1) {
                vec.push_back({a[mx[j]] - a[i], i, mx[j]});
            }
        }
        int v = i;
        for(int j = 0; j < 3 && v != -1; j++) {
            if(mx[j] == -1 || a[v] > a[mx[j]]) {
                swap(v, mx[j]);
            }
        }
    }
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    vector<vector<PII>> adj(n + 1);
    int k = vec.size();
    vector<int> deg(n + 1);
    for(int p = 0; p < k; p++) {
        auto [_, i, j] = vec[p];
        adj[i].emplace_back(j, p);
        adj[j].emplace_back(i, p);
    }
    int bad = 0;
    for(int x = 1; x <= n; x++) {
        for(auto [y, i] : adj[x]) {
            if(i >= k) {
                bad -= (--deg[x] == 1);
                bad -= (--deg[y] == 1);
            }
        }
        while(bad == 0) {
            auto [w, i, j] = vec[--k];
            if(i == x || j == x) {
                continue;
            }
            bad += (++deg[i] == 2);
            bad += (++deg[j] == 2);
        }
        for(auto [y, i] : adj[x]) {
            if(i >= k) {
                bad += (++deg[x] == 2);
                bad += (++deg[y] == 2);
            }
        }
    }
    cout << vec[k][0] << "\n";
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
