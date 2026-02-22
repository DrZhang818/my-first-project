#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;

    if(n == 3 || n == 5) {
        cout << -1 << "\n";
        return;
    }

    vector<int> bad;
    vector<vector<int>> adj(3);

    for(int x = 1; x <= n; x++) {
        if(x % 6 == 0) {
            adj[0].push_back(x);
        } else if(x % 2 == 0) {
            adj[1].push_back(x);
        } else if(x % 3 == 0) {
            adj[2].push_back(x);
        } else {
            bad.push_back(x);
        }
    }

    vector<int> good;
    for(int i : {1, 0, 2}) {
        good.insert(good.end(), adj[i].begin(), adj[i].end());
    }

    int i = 0, j = 0;

    vector<int> p(n);

    for(int k = 0; k < n; k++) {
        if(k % 3 == 0 && i < bad.size()) {
            p[k] = bad[i++];
        } else {
            p[k] = good[j++];
        }
    }

    for(int x : p) {
        cout << x << " \n"[x == p.back()];
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
