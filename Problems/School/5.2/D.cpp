#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> fa, tag;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v, int tg) {
    u = find(u);
    v = find(v);
    fa[u] = v;
    tag[v] |= tg;
}
void solve() {
    int n, m;
    cin >> n >> m;
    fa.resize(n + m + 1);
    iota(fa.begin(), fa.end(), 0);
    tag.resize(n + m + 1);
    vector<int> a(n), b(m);
    int x, y;
    cin >> x;
    for(int i = 1; i <= x; i++) {
        int t;
        cin >> t;
        a[t] = 1;
    }
    cin >> y;
    for(int i = 1; i <= y; i++) {
        int t;
        cin >> t;
        b[t] = 1;
    }
    int L = lcm(n, m);
    for(int i = 0; i < L; i++) {
        int p = i % n, q = i % m;
        int tg = (a[p] | b[q]);
        p++;
        q = n + q + 1;
        merge(p, q, tg);
    }
    bool ok = true;
    for(int i = 1; i <= n + m; i++) {
        if(tag[find(i)] == 0) {
            ok = false;
            break;
        }
    }
    if(ok) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
