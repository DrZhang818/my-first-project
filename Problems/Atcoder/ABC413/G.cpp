#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc413/tasks/abc413_g
vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) { fa[find(u)] = find(v); }
struct info {
    int x, y;
};
int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    fa.resize(k + 1);
    iota(fa.begin(), fa.end(), 0);
    vector<info> a(k + 1);
    map<PII, int> mp;
    for(int i = 1; i <= k; i++) {
        cin >> a[i].x >> a[i].y;
        mp[{a[i].x, a[i].y}] = i;
    }
    for(int i = 1; i <= k; i++) {
        auto [x, y] = a[i];
        for(int s = 0; s < 8; s++) {
            int nx = x + dx[s], ny = y + dy[s];
            if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if(mp[{nx, ny}]) {
                merge(i, mp[{nx, ny}]);
            }
        }
    }
    bool ok = true;
    vector<int> vis(k + 1);
    for(int i = 1; i <= k; i++) {
        auto [x, y] = a[i];
        if(x == 1 || y == m) {
            vis[find(i)] = true;
        }
    }
    for(int i = 1; i <= k; i++) {
        auto [x, y] = a[i];
        if(x == n || y == 1) {
            if(vis[find(i)]) {
                ok = false;
                break;
            }
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
 