#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

inline int lowbit(int o) { return o & -o; }
struct FenwickTree {
    int n;
    vector<ll> tr;
    FenwickTree(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        tr.assign(n, {});
    }
    void add(int o, ll x) {
        for(; o < n; o += lowbit(o)) {
            tr[o] += x;
            tr[o] %= 26;
        }
    }
    ll query(int o) {
        ll res = 0;
        for(; o > 0; o -= lowbit(o)) {
            res += tr[o];
        }
        return res % 26;
    }
    ll rangeQuery(int l, int r) {
        return (query(r) - query(l - 1) + 26) % 26;
    }
    int select(ll k) {
        int x = 0;
        ll cur = 0;
        for(int i = 1 << __lg(n); i; i >>= 1) {
            if(x + i < n && cur + tr[x + i] < k) {
                x += i;
                cur += tr[x];
            }
        }
        return x + 1;
    }
};

void solve() {  
    string s;
    cin >> s;
    int n = s.size();
    int m;
    cin >> m;
    
    vector<int> L(m + 1), R(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> L[i] >> R[i];
    }

    vector<vector<int>> adj(n + 1);

    for(int i = 1; i <= m; i++) {
        if(n & 1) {
            if(L[i] == (n + 1) / 2) L[i]++;
            if(R[i] == (n + 1) / 2) R[i]--;
            if(L[i] > R[i]) continue;
        }
        if(R[i] <= n / 2) {
            adj[R[i]].push_back(L[i]);
        } else if(L[i] > (n + 1) / 2) {
            adj[n - L[i] + 1].push_back(n - R[i] + 1);
        } else {
            int l = min(L[i], n - R[i] + 1);
            int r = max(L[i], n - R[i] + 1);
            if(r == l) continue;
            adj[r - 1].push_back(l);
        }
    }


    vector<int> to(n + 1, -1);

    for(int i = n / 2; i >= 1; i--) {
        if(adj[i].empty()) continue;
        to[i] = adj[i][0];
        sort(adj[i].begin(), adj[i].end(), greater());
        adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());

        for(int j = 1; j < adj[i].size(); j++) {
            adj[adj[i][j - 1] - 1].push_back(adj[i][j]);
        }
    }

    vector<int> d(n + 1);
    for(int i = 1; i <= n / 2; i++) {
        d[i] = (s[i - 1] - s[n - i] + 26) % 26;
    }

    FenwickTree fen(n + 1);

    for(int i = n / 2; i >= 1; i--) {
        int add = fen.query(i);
        d[i] = (d[i] + add) % 26;

        if(to[i] == -1 && d[i]) {
            cout << "NO\n";
            return;
        }
        if(to[i] != -1) {
            fen.add(to[i], 26 - d[i]);
        }
    }

    cout << "YES\n";
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
