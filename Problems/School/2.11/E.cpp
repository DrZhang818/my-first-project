#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    
    int n, m;
    cin >> n >> m;
    struct Node {
        int to, next;
    };
    vector<int> head(n, -1);
    vector<Node> nodes(m);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[i] = {v, head[u]};
        head[u] = i;
    }
    int s, t;
    cin >> s >> t;
    s--, t--;
    queue<PII> q;
    q.push({s, 0});
    int step = 0;
    vector<vector<int>> vis(n, vector<int>(3, false));
    vis[s][0] = true;
    while(!q.empty()) {
        int len = q.size();
        for(int i = 0; i < len; i++) {
            int u = q.front().first;
            int r = q.front().second;
            if(step % 3 == 0 && u == t) {
                cout << step / 3 << "\n";
                return;
            }
            q.pop();
            int nr = (r + 1) % 3;
            for(int cur = head[u]; cur != -1; cur = nodes[cur].next) {
                int v = nodes[cur].to;
                if(!vis[v][nr]) {
                    vis[v][nr] = true;
                    q.push({v, nr});
                }
            }
        }
        step++;
        if(step > 3 * m + 5) break;
    }
    cout << -1 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

