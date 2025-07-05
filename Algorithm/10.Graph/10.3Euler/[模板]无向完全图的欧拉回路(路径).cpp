#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n; cin >> n;
    vector<int> g(n, 0);
    vector vis(n, vector<bool>(n, false));
    if(n % 2 == 0) {
        //去掉n/2-1条边, 保证至多两个奇点
        //如果要求欧拉回路的话, i从1开始
        for(int i = 2; i < n; i += 2) {
            vis[i - 1][i] = true;
            vis[i][i - 1] = true;
        }
    }
    //如果不允许自环, 加上下面这段for循环
    for(int i = 0; i < n; i++) {
        vis[i][i] = true;
    }
    vector<int> path;
    auto dfs = [&](this auto &&self, int u) -> void {
        for(; g[u] < n; g[u]++) {
            int v = g[u];
            if(!vis[u][v]) {
                vis[u][v] = true;
                vis[v][u] = true;
                self(v);
            }
        }
        path.push_back(u);
    };
    dfs(0);
    reverse(path.begin(), path.end());
    for(int i = 0; i < path.size(); i++) {
        cout << path[i] << " \n"[i == path.size() - 1];
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
