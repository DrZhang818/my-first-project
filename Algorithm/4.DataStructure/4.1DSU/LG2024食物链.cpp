#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.luogu.com.cn/problem/P2024
class DSU {
    vector<int> fa;
    vector<int> d;
public:
    DSU(int n) {
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
        d.assign(n, 0);
    }
    int find(int x) {
        if(x != fa[x]) {
            int temp = fa[x];
            fa[x] = find(fa[x]);
            d[x] = (d[x] + d[temp] + 3) % 3;
        }
        return fa[x];
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y, int v) {
        int fx = find(x);
        int fy = find(y);
        if(fx == fy) {
            return (d[x] - d[y] + 3) % 3 == v;
        }
        fa[fx] = fy;
        d[fx] = (d[y] - d[x] + v + 3) % 3;
        return true;
    }
};
void solve(){ 
    int n, k;
    cin >> n >> k;
    int ans = 0;
    DSU g(n + 1);
    while(k--) {
        int flag, x, y;
        cin >> flag >> x >> y;
        if(x > n || y > n) {
            ans += 1;
            continue;
        }
        if(flag == 1) {
            if(!g.merge(x, y, 0)) {
                ans += 1;
            }
        } else {
            if(x == y) {
                ans += 1;
                continue;
            }
            if(!g.merge(x, y, 1)) {
                ans += 1;
            }
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
    
    