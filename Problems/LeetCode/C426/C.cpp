#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/maximize-the-number-of-target-nodes-after-connecting-trees-i/description/
/*
    问题: 两棵树中节点连接后的目标节点数最大化
    图论(一般树 自顶向下DFS) || 思维  
    经过观察, 对于每一个节点i, 连接第二棵树的最优节点是固定的 即max2
    而对于第一棵树, 对于ans[i], 连接的最优方式一定是从第一颗树的节点i开始连接
*/


int dfs(int x, int fa, int d, vector<vector<int>>& adj, int k){
    if(d > k) return 0;
    int cnt = 1; // 当前本身节点
    for(auto& y : adj[x]){
        if(y != fa){
            cnt += dfs(y, x, d + 1, adj, k);
        }
    }
    return cnt;
}

void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> adj1(n, vector<int>());
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        adj1[u].push_back(v);
        adj1[v].push_back(u);
    }
    vector<vector<int>> adj2(m, vector<int>());
    for(int i = 0; i < m - 1; i++){
        int u, v;
        cin >> u >> v;
        adj2[u].push_back(v);
        adj2[v].push_back(u);
    }
    int max2 = 0;
    if(k > 0){
        for(int j = 0; j < m; j++){
            max2 = max(max2, dfs(j, -1, 0, adj2, k - 1));
        }
    }

    vector<int> ans(n, 0);
    for(int i = 0; i < n; i++){
        ans[i] = dfs(i, -1, 0, adj1, k) + max2;
    }
    for(int i = 0; i < n; i++){
        cout << ans[i] << (i == n - 1 ? "\n" : " ");
    }
}

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}