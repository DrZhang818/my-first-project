#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// 定义最大顶点数和权重范围
const int MAXN = 500005;

// 邻接表：adj[u][w] 存储从 u 出发，权重为 w 的所有目标顶点 v
vector<int> adj[MAXN][9]; 

int n, m;
long long k;

// 核心递归函数
// current_nodes: 当前所有活跃路径的终点及对应的路径数量 {vertex, count}
// len: 当前路径的长度
void solve(vector<pair<int, long long>>& current_nodes, int len) {
    if (k <= 0) return;

    // 1. 统计当前层有多少条路径
    long long total_here = 0;
    for (auto& p : current_nodes) {
        total_here += p.second;
    }

    // 2. 输出当前长度。
    // 这些路径的权重序列是相同的，长度也是相同的(len)。
    // 按照题目要求，我们要输出它们的长度。
    long long output_count = min((long long)k, total_here);
    for (int i = 0; i < output_count; i++) {
        cout << len << "\n";
    }
    k -= output_count;
    if (k <= 0) return;

    // 3. 按字典序尝试扩展：先走权重1，再走权重2...
    for (int w = 1; w <= 8; w++) {
        // 收集下一层的状态
        // 使用 vector 而不是 map 以提高效率，之后排序去重
        vector<pair<int, long long>> next_raw;
        
        bool possible = false;

        for (auto& p : current_nodes) {
            int u = p.first;
            long long count = p.second;
            
            // 遍历 u 的所有权重为 w 的出边
            if (!adj[u][w].empty()) {
                possible = true;
                for (int v : adj[u][w]) {
                    next_raw.push_back({v, count});
                }
            }
        }

        if (possible) {
            // 合并相同终点的路径数量
            sort(next_raw.begin(), next_raw.end());
            
            vector<pair<int, long long>> next_nodes;
            if (!next_raw.empty()) {
                int curr_v = next_raw[0].first;
                long long curr_sum = 0;
                
                for (auto& p : next_raw) {
                    if (p.first == curr_v) {
                        curr_sum += p.second;
                        // 剪枝：如果数量已经超过 k，没必要存具体的超大数，存 k+1 即可
                        if (curr_sum > k) curr_sum = k + 1;
                    } else {
                        next_nodes.push_back({curr_v, curr_sum});
                        curr_v = p.first;
                        curr_sum = p.second;
                        if (curr_sum > k) curr_sum = k + 1;
                    }
                }
                next_nodes.push_back({curr_v, curr_sum});
            }

            // 递归进入下一层（长度+1）
            solve(next_nodes, len + 1);
            
            // 如果在子树中找够了 k 个，直接返回
            if (k <= 0) return;
        }
    }
}

int main() {
    // 优化 I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m >> k)) return 0;

    // 存储初始边（相当于路径长度为 1 的情况）
    // initial_edges[w] 存储所有权重为 w 的边的终点
    vector<int> initial_edges[9]; 

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // 建图
        adj[u][w].push_back(v);
        // 记录所有作为起点的边（所有边都可以是路径的起点）
        initial_edges[w].push_back(v); 
    }

    // 字典序遍历：先处理所有权重为 1 的初始边，再处理 2...
    for (int w = 1; w <= 8; w++) {
        if (initial_edges[w].empty()) continue;

        // 合并相同终点
        sort(initial_edges[w].begin(), initial_edges[w].end());
        
        vector<pair<int, long long>> start_nodes;
        int curr_v = initial_edges[w][0];
        long long count = 0;
        
        for (int v : initial_edges[w]) {
            if (v == curr_v) {
                count++;
            } else {
                if (count > k) count = k + 1;
                start_nodes.push_back({curr_v, count});
                curr_v = v;
                count = 1;
            }
        }
        if (count > k) count = k + 1;
        start_nodes.push_back({curr_v, count});

        // 开始递归，初始长度为 1
        solve(start_nodes, 1);
        
        if (k <= 0) break;
    }

    // 如果 k 还没用完（说明图中路径总数少于 k），补 -1
    while (k > 0) {
        cout << "-1\n";
        k--;
    }

    return 0;
}