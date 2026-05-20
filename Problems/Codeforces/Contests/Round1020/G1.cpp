#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

int query(int l, int r) {
    cout << "? " << 1 << " " << r - l + 1;
    for(int i = l; i <= r; i++) {
        cout << " " << i;
    }
    cout << endl;
    int res;
    cin >> res;
    return res;
}

void modify(int x) {
    cout << "? " << 2 << " " << x << endl;
}

void answer(const vector<int>& a) {
    cout << "!";
    for(int i = 1; i < a.size(); i++) {
        cout << " " << a[i];
    }
    cout << endl;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> ans(n + 1);

    int v1 = query(1, 1);
    if(v1 & 1) {
        ans[1] = v1;
        for(int i = 2; i <= n; i++) {
            ans[i] = query(i, i) - v1;
        }
        answer(ans);
        return;
    }

    if(v1 == 0) {
        modify(1);
        v1 = query(1, 1);
    }
    if(v1 == 2) {
        modify(1);
        ans[1] = -1;
    } else if(v1 == -2) {
        modify(1);
        ans[1] = 1;
    } 

    for(int i = 2; i <= n; i++) {
        ans[i] = query(i, i);
    }

    answer(ans);
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
