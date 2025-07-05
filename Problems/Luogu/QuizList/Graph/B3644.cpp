#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1);
    for(int i = 1; i <= n; i++) {
        int v;
        while(cin >> v && v != 0) {
            adj[i].push_back(v);
            deg[v]++;
        }
    }
    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(deg[i] == 0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        int u = q.front();
        cout << u << " ";
        q.pop();
        for(int v : adj[u]) {
            if(--deg[v] == 0) {
                q.push(v);
            }
        }   
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

