#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

//https://atcoder.jp/contests/abc416/tasks/abc416_f
/*
    DP
    题意:
        给定一棵N个顶点的树和一个整数K, 每个顶点o有权值a[o], 起初所有顶点颜色均为白色
        你可以进行至多K次以下操作:
        op: 选择树上一条所有顶点均为白色的路径, 将该路径上所有顶点染成黑色
        求最终所有黑色顶点上的数字之和的最大可能值
        范围: N∈[2,2e5], K∈[1,5], a[i]∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        我们首先观察题目性质, 发现K非常小, 这启示我们可以往树上背包的方向思考
        考虑定义 dp[i][j] := 以i为根的子树进行j次操作的最大值
        直接这样定义显然无法进行状态转移, 我们需要寻找描述状态的关键信息
        在树上做dp时, 常见的是从下向上转移, 把v的信息合并到u
        这时, 最值得关注的是v和u这两个点的信息, 至于v子树的内部是什么情况往往不需要关注
        很明显, v和u是否已经变为黑色是值得关注的, 因为每个点只能选择一次
        但这还不够, 例如u是白色, v是黑色, 那么v和u是否一定不能在一条路径中呢?
        很明显这不对, 如果v的路径没有"拐回去", 意味着还可以向上延伸, 此时就有机会与u在一条路径
        因此我们对于已经变黑的情况还需要细分为: 是否可以向父节点延伸
        这样我们的dp变为: dp[i][j][s:0/1/2] := 以i为根的子树进行j次操作, i的状态为s的最大值
        0代表i为白色
        1代表i为黑色且可以向父节点延伸
        2代表i为黑色且不能向父节点延伸
        下面考虑状态转移, 我们考虑如何将u的子树v合并到u:
        我们枚举u和v各自进行的操作次数x,y
        (1)如果不把u和v放在一条路径, 此时二者完全独立
            ndp[u][x + y][s] = dp[u][x][s] + max(dp[v][y][0~2])
        (2)如果考虑u和v放在一条路径
            1.如果u为0, v为1
            此时有ndp[u][x + y][1] = dp[u][x][0] + dp[v][y][1] + a[u]
            2.如果u为1, v为1
            此时有ndp[u][x + y - 1][2] = dp[u][x][1] + dp[v][y][1]
        考虑初值:
        初始化所有状态为-inf表示不合法
        对于每个顶点i, dp[i][0][0] = 0, dp[i][1][1] = a[u]
        后者的意义是: 选择自身作为一条路径
        细节:
            对于这样的设定, 只选择自身一个节点, 我们与子树v合并后得到的状态理应是1而不是2
            但这并不影响, 因为(2)1.会把这种情况算出来
            我们要记住决策类dp的一个理念: dp表不一定要符合事实, 只要保证最优解对应的dp值是精确的即可 
*/
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector dp(n + 1, vector(k + 1, array<ll,3>({-inf, -inf, -inf})));  
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        dp[u][0][0] = 0;
        dp[u][1][1] = a[u];
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(self, v, u);
            vector ndp(k + 1, array<ll,3>({-inf, -inf, -inf}));
            for(int x = 0; x <= k; x++) {
                for(int y = 0; y <= k; y++) {
                    ll f = max({dp[v][y][0], dp[v][y][1], dp[v][y][2]});
                    if(x + y <= k) {
                        ndp[x + y][0] = max(ndp[x + y][0], dp[u][x][0] + f);
                        ndp[x + y][1] = max(ndp[x + y][1], dp[u][x][1] + f);
                        ndp[x + y][2] = max(ndp[x + y][2], dp[u][x][2] + f);
                        ndp[x + y][1] = max(ndp[x + y][1], dp[u][x][0] + dp[v][y][1] + a[u]);
                    }
                    if(x && y && x + y - 1 <= k) {
                        ndp[x + y - 1][2] = max(ndp[x + y - 1][2], dp[u][x][1] + dp[v][y][1]);
                    }
                }
            }
            swap(dp[u], ndp);
        }
    };
    dfs(dfs, 1, 0);
    ll ans = 0;
    for(int i = 1; i <= k; i++) {
        ans = max(ans, *max_element(dp[1][i].begin(), dp[1][i].end()));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}