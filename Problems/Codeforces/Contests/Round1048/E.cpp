#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

bitset<200005> bt, s;
void solve() {
    s.set(0);
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n + 1);
    for(int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        adj[p].push_back(i);
    }
    vector<int> a{0}, q{1};
    while(!q.empty()) {
        a.push_back(q.size());
        vector<int> nq;
        bool ok = true;
        for(int u : q) {
            if(adj[u].empty()) {
                ok = false;
                break;
            }
            for(int v : adj[u]) {
                nq.push_back(v);
            }
        }
        if(!ok) {
            break;
        }
        swap(q, nq);
    }
    int m = a.size() - 1;
    vector<int> pre(m + 1);
    for(int i = 1; i <= m; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    k = min(k, n - k);
    for(int i = 1; i <= k; i++) {
        s.set(i);
    }
    bt.set(0);
    for(int i = 1; i <= m; i++) {
        bool ok = false;
        bt |= bt << a[i];
        bt &= s;
        int t = pre[i - 1] + a[i] + k - n - 1;
        if(t >= 0) {
            bt >>= t + 1;
            bt <<= t + 1;
        }
        if(bt.none()) {
            cout << i - 1 << "\n";
            return;
        }
    }
    cout << m << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
        bt.reset();
        s.reset();
    }
    return 0;
}
