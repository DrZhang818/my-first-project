#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/2071/problem/C
/*
    构造 || 贪心
    题意:
        给定一棵包含N个节点(编号1到N)的树, 以及两个节点编号st和en,分别表示起点和终点。
        定义一个由1到N构成的排列P[1…N], 按照排列P定义的顺序进行N步操作:
        在第i步, 设当前所在节点为cur, 目标节点为P[i]
        如果cur与P[i]不同, 则沿着cur到P[i]的唯一简单路径前进一步, 即从cur移动到该路径上的下一个节点;
        如果cur已经等于P[i], 则原地不动
        当且仅当从起点st出发, 按照上述规则恰好在经过N步后到达终点en时, 称排列P为合法排列
        要求构造一个合法排列, 不存在输出-1
        范围: n∈[1,1e5], st,en∈[1,n]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中分析性质与规律, 从特殊到一般
        我们定义当前位置到en的距离为d, 由于每次只能行动一格, 按照方向的向心、离心
        可以很容易的得到一个性质
        *每次移动对d的贡献∈{-1, 0, 1}
        最终要求在N步结束后的d = 0
        那么我们就很容易得到以下结论:
        第i步对应的d[i]必须小于等于N-i
        但难点在于这一结论不能很好的帮助我们构造排列, 因为这种移动方式太难以控制了
        但我们有个大概的感觉: d呈现总体递减的趋势, 越往后, 我们的深度要越小
        进一步想, P[i]就像不动点理论中的吸引子, 那么贪心地想, 把d = 0的en放在最后一定是
        最优的, 因为无论哪个位置, 都会被吸引向d = 0的位置, 这正是目标点
        紧接着的最后几个应该放d = 1的节点, 因为所有位置都会向d = 1的位置移动, 这是去往
        d = 0的最近位置
        因此, 这样贪心地想, 我们就应该按照深度从大到小进行构造排列了
        下面证明正确性:
        从大到小, 处理完深度为di的节点后, 所在位置的深度一定 <= di
        这可以用数学归纳法证明:
        (1)处理叶子节点, 设深度为D
           显然地, 处理完叶子节点后深度 <= D
        (2)处理深度为D-1的节点,
           如果当前位置为D, 那么移动后到达D-1
           如果当前位置<=D-1, 那么移动后一定不会变得更深, 还是<=D-1
        这样一层一层处理完之后, 当我们处理完第0层节点, 所处深度就会<=0, 那么一定就在end节点了
*/
void solve() { 
    int n, st, end;
    cin >> n >> st >> end;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<vector<int>> dis(n);
    vector<int> d(n + 1);
    auto dfs = [&](this auto &&dfs, int fa, int u) -> void {
        dis[d[u]].push_back(u);
        for(int v : adj[u]) {
            if(v == fa) continue;
            d[v] = d[u] + 1;
            dfs(u, v);
        }
    };
    dfs(0, end);
    for(int i = n - 1; i >= 0; i--) {
        for(int v : dis[i]) {
            cout << v << " ";
        }
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
