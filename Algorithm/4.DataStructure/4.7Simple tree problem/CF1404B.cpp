#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/contest/1404/problem/B
/*
    博弈论 || 树的直径 
    题意:
        给定一棵N个节点的树, Alice位于a节点, Bob位于b节点
        Alice每次可以移动da个边, Bob每次可以移动db个边
        Alice先移动, 二人都按最优策略进行, 判断Alice能否抓到Bob(即位于同一个节点)
        范围: N∈[2,1e5], a,b∈[1,N], da,db∈[1,n-1]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先解释下为什么把博奕类问题归为构造类
        设决策函数F(A,B), A代表Alice的决策, B代表Bob的决策
        如果Alice赢, 规定F输出为1; 如果Bob赢, 规定F输出为0
        那么博奕类问题本质是看是否存在一种方案, 使得F的输出为0
        这样就归为了构造类题目, 即对于任意A, 存在B, 使得F(A,B) = 0
        对于这种追逐博弈问题, 首先思考先手优势
        如果dist(a,b) <= da, 显然Alice一步就获胜了
        接下来分析Bob的逃脱能力:
            由于树上任意两点间的路径唯一, 因此自然想到Alice的一种贪心策略:
            Alice每次移动都在Alice->Bob的简单路径上移动da距离
            由于Bob无法通过其他路径绕行, 且树的边数有限, 可知Bob的空间会不断被缩小
            假设若干回合后, Bob被逼入了死角
            ___(___A__B), 此时Bob要想逃脱, 必须至少在一步之内走到左括号左侧一格
            因此对于这种情况, 必须满足db > 2 * da, Bob才有合法解
        此时又引发了一个新的问题, 如果树的直径比较小的话, 可能导致左括号左侧没有格点
        这样相当于Alice一步之内可以到达树上任意一点, 那么Bob是无解的
        因此对于树的直径diam必须满足diam > 2 * a 
        总结下, 这三条关键判断实际是博弈论中"先手优势"、"追逐博弈"以及
        "空间约束"在此题中的具体体现
*/
void solve() { 
    int n, a, b, da, db;
    cin >> n >> a >> b >> da >> db;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if(db <= 2 * da) {
        cout << "Alice\n";
        return;
    }
    int d = 0;
    auto dfs = [&](this auto &&self, int u, int fa) -> int {
        int mx = 0, se = 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            int cur = self(v, u) + 1;
            if(cur >= mx) {
                se = mx;
                mx = cur;
            } else if(cur > se) {
                se = cur;
            }
        }
        d = max(d, mx + se);
        return mx;
    };
    int dist = 0;
    queue<int> q;
    q.push(a);
    vector<bool> vis(n + 1, false);
    vis[a] = true;
    while(!q.empty()) {
        bool ok = false;
        for(int i = 0, j = q.size(); i < j; i++) {
            int u = q.front(); q.pop();
            if(u == b) {
                ok = true;
                break;
            }
            for(int v : adj[u]) {
                if(!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
        if(ok) break;
        dist++;
    }
    if(dist <= da) {
        cout << "Alice\n";
        return;
    }
    dfs(1, 0);
    if(d > 2 * da) {
        cout << "Bob\n";
    } else {
        cout << "Alice\n";
    }
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
    
