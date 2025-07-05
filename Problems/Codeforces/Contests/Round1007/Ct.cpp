#include <bits/stdc++.h>
using namespace std;
 
// This solution constructs a permutation that forces the mouse 
// (starting at st) to end at en. 
// We first compute the unique simple path Q from st to en.
// Then let R be all vertices not in Q. We compute distances from en 
// (via BFS) and sort R in descending order (by distance from en; break ties by id).
// Finally, we output permutation p = (R in sorted order) concatenated with Q (in order from st to en).
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t; 
    cin >> t;
    while(t--){
        int n, st, en;
        cin >> n >> st >> en;
        vector<vector<int>> adj(n+1);
        for (int i = 1; i <= n - 1; i++){
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
 
        // Find the unique path Q from st to en.
        vector<int> parent(n+1, -1);
        vector<bool> vis(n+1, false);
        queue<int>q;
        q.push(st);
        vis[st] = true;
        while(!q.empty()){
            int cur = q.front(); q.pop();
            if(cur == en) break;
            for (int nxt : adj[cur]){
                if(!vis[nxt]){
                    vis[nxt] = true;
                    parent[nxt] = cur;
                    q.push(nxt);
                }
            }
        }
 
        // Reconstruct Q (from st to en).
        vector<int> Q;
        int cur = en;
        while(cur != -1){
            Q.push_back(cur);
            if(cur == st) break;
            cur = parent[cur];
        }
        reverse(Q.begin(), Q.end());
 
        // Mark vertices on the path.
        vector<bool> onPath(n+1, false);
        for (int v : Q)
            onPath[v] = true;
 
        // Compute distances from en (BFS from en).
        vector<int> dist(n+1, -1);
        {
            queue<int> qq;
            qq.push(en);
            dist[en] = 0;
            while(!qq.empty()){
                int cur = qq.front();
                qq.pop();
                for (int nxt : adj[cur]){
                    if(dist[nxt] == -1){
                        dist[nxt] = dist[cur] + 1;
                        qq.push(nxt);
                    }
                }
            }
        }
 
        // Build R = vertices not in Q.
        vector<int> R;
        for (int i = 1; i <= n; i++){
            if(!onPath[i])
                R.push_back(i);
        }
 
        // Sort R in descending order by distance from en 
        // (if equal, break ties by larger vertex id)
        sort(R.begin(), R.end(), [&](int a, int b){
            if(dist[a] == dist[b])
                return a > b;
            return dist[a] > dist[b];
        });
 
        // Our permutation: first the vertices in R (in our chosen order) then Q.
        vector<int> perm;
        for (int v : R) 
            perm.push_back(v);
        for (int v : Q) 
            perm.push_back(v);
 
        // (The permutation must be of length n.)
        if((int)perm.size() != n){
            cout << -1 << "\n";
            continue;
        }
 
        // Output the permutation.
        for (int i = 0; i < n; i++){
            cout << perm[i] << (i+1 == n ? "\n" : " ");
        }
    }
    return 0;
}
