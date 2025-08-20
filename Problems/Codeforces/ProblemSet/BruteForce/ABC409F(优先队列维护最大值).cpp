#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return;
    fa[u] = v;
}
struct info {
    int u, v;
    ll d;
    friend bool operator < (const info &a, const info &b) {
        return a.d > b.d;
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> x(n + 1), y(n + 1);
    fa.resize(n + q + 1);
    iota(fa.begin(), fa.end(), 0);
    for(int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];        
    }
    priority_queue<info> pq;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < i; j++) {
            pq.push({i, j, abs(x[i] - x[j]) + abs(y[i] - y[j])});
        }
    }
    int cnt = n;
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            cnt++;
            int xx, yy;
            cin >> xx >> yy;
            x.push_back(xx);
            y.push_back(yy);
            for(int i = 1; i < cnt; i++) {
                pq.push({cnt, i, abs(xx - x[i]) + abs(yy - y[i])});
            }
        } else if(op == 2) {
            while(!pq.empty() && find(pq.top().u) == find(pq.top().v)) {
                pq.pop();
            }
            if(pq.empty()) {
                cout << -1 << "\n";
                continue;
            }
            ll k = pq.top().d;
            while(!pq.empty() && pq.top().d == k) {
                auto [u, v, d] = pq.top(); pq.pop();
                merge(u, v);
            }
            cout << k << "\n";
        } else {
            int u, v;
            cin >> u >> v;
            if(find(u) == find(v)) {
                cout << "Yes\n"; 
            } else {
                cout << "No\n";
            }
        }
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
