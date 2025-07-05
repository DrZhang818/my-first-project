#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://icpc.bjtu.edu.cn/contest/1383/problem/D
/*
    图论 || 最短路
    题意:
        给定一颗n个节点的树, 以及每两个边之间的距离c
        现有q次询问和一个节点k, 要求计算出每次询问给出的两个点经过节点k的最短路
    关键思考:
        树上路径唯一, 经过节点k的dist(x,y)就等于dist(x,k) + dist(k,y)
        因此只需要以节点k为起点跑一次bfs即可
        注:
            bfs一般用来求无权图的最短路
            但本题由于是树结构, 任意两点的路径唯一
            因此可以直接使用bfs做到O(n)的时间复杂度
*/
void solve(){
    int n;
    cin >> n;
    vector<vector<pair<int,ll>>> adj(n + 1);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        ll c;
        cin >> u >> v >> c;
        adj[u].emplace_back(v, c);
        adj[v].emplace_back(u, c);
    }
    int t, k;
    cin >> t >> k;
    vector<ll> dist(n + 1, -1);
    queue<int> q;
    dist[k] = 0;
    q.push(k);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto &e : adj[u]){
            int v = e.first;
            ll c = e.second;
            if(dist[v] == -1){
                dist[v] = dist[u] + c;
                q.push(v);
            }
        }
    }
    for(int i = 0; i < t; i++){
        int x, y;
        cin >> x >> y;
        cout << dist[x] + dist[y] << "\n";
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);


    solve();
    return 0;
}