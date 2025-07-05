#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


class DSU {
private:
    vector<int> fa;
    int n;
public:
    DSU(int x) {
        n = x;
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int u) {
        if(u != fa[u]) {
            fa[u] = find(fa[u]);
        }
        return fa[u];
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }
    bool merge(int u, int v) {
        int fu = find(u), fv = find(v);
        if(fu == fv) return false;
        fa[fu] = fv;
        return true;
    }
};    
void solve() { 
    int n, MOD;
    cin >> n >> MOD;
    vector<int> a(n + 5);
    DSU g(n + 5);
    int idx = 0;
    ll t = 0;
    deque<int> q;
    while(n--) {
        char c;
        cin >> c;
        if(c == 'A') {
            ll p;
            cin >> p;
            p = ((p + t) % MOD + MOD) % MOD;
            a[idx] = p;
            while(!q.empty() && a[idx] > a[q.back()]) {
                g.merge(q.back(), idx);
                q.pop_back();
            }
            q.push_back(idx);
            idx++;
        } else {
            int L;
            cin >> L;
            int f = g.find(idx - L);
            cout << a[f] << "\n";
            t = a[f];
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
