#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

inline int lowbit(int o) { return o & -o; }
struct BIT {
    int n;
    vector<int> tr;
    BIT(int x) : n(x), tr(x + 1) {}
    void modify(int o, int x) {
        for(; o <= n; o += lowbit(o)) {
            tr[o] = max(tr[o], x);
        }   
    }
    int query(int o) {
        int res = -inf;
        for(; o > 0; o -= lowbit(o)) {
            res = max(res, tr[o]);
        }
        return res;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        adj[x].push_back(i);
    }
    BIT tr(n + 1);
    for(int x = n; x >= 1; x--) {
        int res = tr.query(n + 1);
        for(int i : adj[x]) {
            tr.modify(i + 1, tr.query(i) + 1);
        }
        tr.modify(1, res);
    }
    cout << n - tr.query(n + 1) << "\n";
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
