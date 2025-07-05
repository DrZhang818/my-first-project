#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int n, m;
int st, en;
struct info { 
    int v, w;
    friend bool operator < (const info &a, const info &b) {
        return a.w < b.w;
    }
};
vector<vector<info>> adj(n + 1);
vector<int> solve1() {
    vector<int> path;
    vector<bool> vis(n + 1);
    vis[st] = true;
    auto dfs = [&](this auto &&self, int u) -> bool {
        if(u == en) return true;
        for(auto [v, w] : adj[u]) {
            if(vis[v]) continue;
            vis[v] = true;
            path.push_back(w);
            if(self(v)) return true;
            path.pop_back();
        }
        return false;
    };
    dfs(st);
    return path;
}

vector<int> solve2() {
    vector<int> path;
    vector<bool> vis(n + 1);
    vis[st] = true;
    auto dfs = [&](this auto &&self, int u, int en) -> bool {
        if(u == en) return true;
        for(auto &[v, w] : adj[u]) {
            if(!vis[v]) {
                path.push_back(w);
                vis[v] = true;
                if(self(v, en)) return true;
                vis[v] = false;
                path.pop_back();
            }
        }
        return false;
    };  
    dfs(st, en);
    return path;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    srand(time(0));
    n = 100, m = 100;
    for(int i = 1; i <= 500; i++) {
        cerr << "test" << i << ": " << "\n";
        adj.assign(n + 1, vector<info>());
        for(int i = 1; i <= m; i++) {
            int u, v, w;
            u = 1 + rand() % n;
            v = 1 + rand() % n;
            while(v == u) v = 1 + rand() % n;
            adj[u].emplace_back(v, i);
            adj[v].emplace_back(u, i);
        }
        st = 1 + rand() % n;
        en = 1 + rand() % n;
        while(en == st) en = 1 + rand() % n;
        for(int i = 1; i <= n; i++) {
            sort(adj[i].begin(), adj[i].end());
        }

        auto ans1 = solve1();
        // cerr << "ok1\n";
        auto ans2 = solve2();
        // cerr << "ok2\n";
        if(ans1 != ans2) {
            cerr << "WA!\n";
            for(int i = 1; i <= n; i++) {
                for(auto [j, w] : adj[i]) {
                    cerr << "(" << i << "," << j << "," << w << ")\n"; 
                }
            }
            cerr << st << " " << en << "\n";
            for(int x : ans1) {
                cerr << x << " ";
            }
            cerr << "\n";
            for(int x : ans2) {
                cerr << x << " ";
            }
            cerr << "\n";
        } else {
            cerr << "AC!\n";
        }
    }
    return 0;
}
