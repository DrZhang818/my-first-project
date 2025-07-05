#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



//https://www.luogu.com.cn/problem/P1113
/*
    拓扑排序 || DP
    题意:
        给定n个任务, 每个任务i可能有若干个前置任务, 前置任务的编号一定小于i
        每个任务i完成所需的时间为a[i], 两个互相无依赖关系的任务可以同时进行
        求完成所有任务所需的最小时间
    关键思考:
        可以把n个任务抽象成n个点, i的前置任务j抽象成一条j -> i的有向边
        每个任务所需的时间抽象为每个点的点权
        那么问题就变为求出有向无环图(DAG)的关键路径(最长路径), 因为它决定了完成所有任务的最短时间
        这个问题可以使用拓扑排序 + DP来解决
        定义dp[i] := 任务i的最早完成时间
        则有转移方程dp[i] = max{dp[j] | j是i的前置任务} + a[i]
        为什么需要拓扑排序?
        dp[i]的转移需要得到所有dp[j]的状态
        因此要以一个正确的状态转移序来填充DP表
        而拓扑排序能够保证在DAG图中的在访问每个节点之前, 一定访问了它的所有前置节点
        这样就保证了DP的无后效性, 从而正确求得每个任务的最早完成时间
        而完成所有任务的最短时间就是max{dp[i] | i ∈ [1, n]}, 这也是DAG的关键路径
*/
void solve(){
    int n;
    cin >> n;
    vector<int> cost(n + 1);
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1);
    vector<int> dp(n + 1);
    for(int i = 0; i < n; i++) {
        int u, w;
        cin >> u >> w;
        cost[u] = w;
        int v;
        while(cin >> v && v != 0) {
            adj[v].push_back(u);
            deg[u]++;
        }
    }   
    queue<int> q; 
    for(int i = 1; i <= n; i++) {
        if(deg[i] == 0) {
            q.push(i);
            dp[i] = cost[i];
        }
    }
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int v : adj[u]) {
            if(--deg[v] == 0) {
                q.push(v);
            }
            dp[v] = max(dp[v], dp[u] + cost[v]);
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
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

