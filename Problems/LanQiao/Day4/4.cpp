#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n, m;
    cin >> n >> m;
    vector<set<int>> adj(n + 1);
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        adj[x].insert(y);
        adj[y].insert(x);
    }
    vector<int> vis(n + 1, -1);
    vector<int> size(n + 1);
    int id = 1;
    auto bfs = [&](int i){
        queue<int> q;
        int cur = 0;
        q.push(i);
        while(!q.empty()){
            cur++;
            int idx = q.front();
            vis[idx] = id;
            q.pop();
            for(auto c : adj[idx]){
                if(vis[c] == -1){
                    q.push(c);
                    vis[c] = id;
                }
            }
        }
        size[id++] = cur;
    };  
    for(int i = 1; i <= n; i++){
        if(vis[i] == -1){
            bfs(i);
        }
        cout << size[vis[i]] << " ";
    }
}
    
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}