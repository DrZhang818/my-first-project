#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    int m = __lg(n - 1) + 1;
    cout << m << endl;

    vector<vector<int>> adj(m);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i >> j & 1) {
                adj[j].push_back(i + 1);
            }
        }
    }

    for(int i = 0; i < m; i++) {
        cout << adj[i].size();
        for(int x : adj[i]) {
            cout << " " << x;
        }
        cout << endl;
    }

    string s;
    cin >> s;
    int x = 0;
    for(int i = m - 1; i >= 0; i--) {
        x = x << 1 | (s[i] - '0');
    }

    cout << x + 1 << endl;

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
