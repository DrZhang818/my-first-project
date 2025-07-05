#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>
#include <algorithm>
#include <map>

using namespace std;

// 定义一个大数表示无穷远，用于初始化最小花费
const long long INF = numeric_limits<long long>::max();

// 定义优先队列中的状态：风景指数（用于优先排序）、花费、城市编号
// 使用 tuple 默认是按元素顺序进行最大堆排序
// 我们希望风景指数最大优先，花费最小优先
struct State {
    int scenic;
    long long cost;
    int city;

    // 自定义比较运算符，用于优先队列排序
    // 优先队列默认是最大堆
    // 排序规则：首先按风景指数降序，如果风景指数相同，则按花费升序
    bool operator<(const State& other) const {
        if (scenic != other.scenic) {
            return scenic < other.scenic; // 风景指数大的优先级高 (最大堆)
        }
        return cost > other.cost; // 风景指数相同时，花费小的优先级高
    }
};

int main() {
    // 提高输入输出效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long b; // 银行卡消费额度
    int n; // 城市总数
    int m; // 道路条数
    int k; // 咨询次数

    cin >> b >> n >> m >> k;

    // 存储图的邻接表
    vector<vector<pair<int, pair<int, int>>>> adj(n + 1);

    // 读取道路信息，构建邻接表
    for (int i = 0; i < m; ++i) {
        int u, v, cost, scenic;
        cin >> u >> v >> cost >> scenic;
        // 道路是双向的
        adj[u].push_back({v, {cost, scenic}});
        adj[v].push_back({u, {cost, scenic}});
    }

    // 读取需要咨询的出发城市编号
    vector<int> query_cities(k);
    for (int i = 0; i < k; ++i) {
        cin >> query_cities[i];
    }

    // 对于每个查询的出发城市
    for (int start_city : query_cities) {
        // dp[i][s] 表示到达城市 i，累计风景指数为 s 时的最小花费
        // 使用 vector<map> 以处理稀疏的风景指数值
        vector<map<int, long long>> min_cost_for_scenic(n + 1);

        // 优先队列，用于搜索
        priority_queue<State> pq; // 使用自定义的 < 运算符，实现最大风景指数优先

        // 起始状态：到达起始城市，花费 0，风景指数 0
        pq.push({0, 0, start_city});
        min_cost_for_scenic[start_city][0] = 0;

        // 搜索过程
        while (!pq.empty()) {
            State current = pq.top();
            pq.pop();

            int current_scenic = current.scenic;
            long long current_cost = current.cost;
            int u = current.city;

            // 如果当前花费已经大于记录的达到相同风景指数的最小花费，则跳过
            // 注意：这里需要确保 min_cost_for_scenic[u] 中存在 current_scenic 这个 key
            if (min_cost_for_scenic[u].count(current_scenic) && current_cost > min_cost_for_scenic[u][current_scenic]) {
                continue;
            }

            // 遍历当前城市 u 的所有邻居
            for (auto& edge : adj[u]) {
                int v = edge.first; // 邻居城市
                int travel_cost = edge.second.first; // 到邻居的旅费
                int travel_scenic = edge.second.second; // 到邻居的风景指数

                long long new_cost = current_cost + travel_cost;
                int new_scenic = current_scenic + travel_scenic;

                // 如果新路径的总花费在预算内
                if (new_cost <= b) {
                    // 如果是第一次达到这个风景指数，或者找到了更便宜的路径达到这个风景指数
                    if (min_cost_for_scenic[v].find(new_scenic) == min_cost_for_scenic[v].end() || new_cost < min_cost_for_scenic[v][new_scenic]) {
                         min_cost_for_scenic[v][new_scenic] = new_cost;
                         pq.push({new_scenic, new_cost, v});
                    }
                }
            }
        }

        // 查找在预算内可以到达的城市（不包括起始城市）
        vector<int> reachable_cities;
        for (int i = 1; i <= n; ++i) {
            if (i != start_city) {
                // 检查是否存在任何一个风景指数 s，使得到达城市 i 的最小花费 <= b
                for(auto const& [scenic_val, cost_val] : min_cost_for_scenic[i]) {
                    if (cost_val <= b) {
                        reachable_cities.push_back(i);
                        break; // 只要有一种方式可达即可
                    }
                }
            }
        }
        // 对可到达城市按编号升序排序
        sort(reachable_cities.begin(), reachable_cities.end());

        // 输出第一行：在预算内可以到达的城市编号
        if (reachable_cities.empty()) {
            cout << "T_T\n";
        } else {
            for (size_t i = 0; i < reachable_cities.size(); ++i) {
                cout << reachable_cities[i] << (i == reachable_cities.size() - 1 ? "" : " ");
            }
            cout << "\n";

            // 查找在可到达城市中，通过预算内任意路径能够达到的最高风景指数总值
            vector<int> highest_scenic_cities;
            int max_scenic_value = -1; // 初始化为 -1，因为风景指数 >= 0

            // 找到最高的风景指数总值
            for (int city : reachable_cities) {
                // 对于每个可到达城市，找到在预算内能达到的最高风景指数
                int current_city_max_scenic = -1;
                 for(auto const& [scenic_val, cost_val] : min_cost_for_scenic[city]) {
                    if (cost_val <= b) {
                        current_city_max_scenic = max(current_city_max_scenic, scenic_val);
                    }
                }
                max_scenic_value = max(max_scenic_value, current_city_max_scenic);
            }

            // 收集所有能够达到这个最高风景指数总值的城市
            for (int city : reachable_cities) {
                 for(auto const& [scenic_val, cost_val] : min_cost_for_scenic[city]) {
                    if (cost_val <= b && scenic_val == max_scenic_value) {
                        highest_scenic_cities.push_back(city);
                        break; // 找到一个符合条件的即可
                    }
                }
            }
            // 对这些城市按编号升序排序
            sort(highest_scenic_cities.begin(), highest_scenic_cities.end());

            // 输出第二行：能够达到最高风景指数总值的城市编号
            for (size_t i = 0; i < highest_scenic_cities.size(); ++i) {
                cout << highest_scenic_cities[i] << (i == highest_scenic_cities.size() - 1 ? "" : " ");
            }
            cout << "\n";
        }
    }

    return 0;
}
