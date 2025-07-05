#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


class DSU {
    vector<int> fa;
    int K;
public:
    DSU(int n) {
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
        K = n;
    }
    int find(int x) {
        if(x != fa[x]) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }
    bool merge(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if(fx == fy) {
            return false;
        }
        fa[fx] = fy;
        K -= 1;
        return true;
    }
    int kinds() {
        return K;
    }
};
struct info {
    int x, y, t;
};
void solve(){ 
    int n, m;
    cin >> n >> m;
    vector<info> a(m);
    DSU g(n);
    for(int i = 0; i < m; i++) {
        cin >> a[i].x >> a[i].y >> a[i].t;
    } 
    sort(a.begin(), a.end(), [](auto &a, auto &b) -> bool {
        return a.t < b.t;
    });
    int ans = -1;
    for(int i = 0; i < m; i++) {
        int x = a[i].x - 1, y = a[i].y - 1, t = a[i].t;
        g.merge(x, y);
        if(g.kinds() == 1) {
            ans = t;
            break;
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
    