#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<int> fa;
int cnt;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    fa[v] = u;
    cnt--;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<int> p(n + 1), q(n + 1);
    iota(p.begin(), p.end(), 0);
    iota(q.begin(), q.end(), 0);
    stable_sort(p.begin() + 1, p.end(), 
        [&](auto x, auto y) {
            return a[x] < a[y];
        });
    stable_sort(q.begin() + 1, q.end(), 
        [&](auto x, auto y) {
            return b[x] < b[y];
        });
    for(int i = 1; i <= n; i++) {
        if(a[p[i]] > b[q[i]]) {
            cout << "No\n";
            return;
        }
    }
    for(int i = 2; i <= n; i++) {
        if(a[p[i]] <= b[q[i - 1]]) {
            cout << "Yes\n";
            return;
        }
    }
    vector<int> np(n + 1), nq(n + 1);
    for(int i = 1; i <= n; i++) {
        np[p[i]] = i;
        nq[q[i]] = i;
    }
    swap(p, np);
    swap(q, nq);
    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    cnt = n;
    for(int i = 1; i <= n; i++) {
        merge(p[i], q[i]);
    }
    if(cnt == 1) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
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
