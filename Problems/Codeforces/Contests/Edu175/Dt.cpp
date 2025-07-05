#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 3e5 + 5;

vector<vector<int>> adj; // 邻接表表示树
vector<int> depth;       // 每个节点的深度

// 计算每个节点的深度
void dfs(int v, int p, int d) {
    depth[v] = d;
    for(int u : adj[v]) {
        if(u != p) {
            dfs(u, v, d + 1);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    
    // 初始化
    adj.assign(n + 1, vector<int>());
    depth.assign(n + 1, 0);
    
    // 读入父节点数组并建树
    for(int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }
    
    // 计算每个节点的深度
    dfs(1, 0, 0);
    
    // dp[i] 表示以节点 i 结尾的合法序列数量
    vector<long long> dp(n + 1, 0);
    
    // 初始化：每个节点都可以作为单独的序列
    for(int i = 1; i <= n; i++) {
        dp[i] = 1;
    }
    
    // 对于每个深度，从小到大处理
    for(int d = 0; d < n; d++) {
        vector<int> curr_nodes; // 当前深度的所有节点
        for(int i = 1; i <= n; i++) {
            if(depth[i] == d) {
                curr_nodes.push_back(i);
            }
        }
        
        // 对于当前深度的每个节点
        for(int v : curr_nodes) {
            // 找到所有深度为 d+1 的合法后继节点
            for(int u = 1; u <= n; u++) {
                if(depth[u] != d + 1) continue;
                
                // 检查移动是否合法
                bool can_move = true;
                if(v != 1) { // 如果不是根节点
                    // 检查 u 是否是 v 的邻居
                    for(int nei : adj[v]) {
                        if(nei == u) {
                            can_move = false;
                            break;
                        }
                    }
                }
                
                if(can_move) {
                    dp[u] = (dp[u] + dp[v]) % MOD;
                }
            }
        }
    }
    
    // 统计所有可能的序列数量
    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        ans = (ans + dp[i]) % MOD;
    }
    
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    
    return 0;
}
