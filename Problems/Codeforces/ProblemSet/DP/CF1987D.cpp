#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/1987/problem/D
/*
    DP || 贪心
    题意:
        Alice和Bob在轮流争夺N块蛋糕, 其中第i块蛋糕的美味值为a[i]
        Alice先吃, 规则如下:
        (1)Alice每次必须选择一块比之前吃过的最大美味值还要高的蛋糕 (第一回合可以随便选)
        (2)Bob可以随意吃
        当轮到某位选手找不到符合要求的蛋糕时, 游戏结束
        设x为Alice吃掉的蛋糕数量, Alice想最大化x, Bob想最小化x
        两人都以最优策略进行, 求Alice最终能吃多少块蛋糕
        范围: N∈[1,5000], a[i]∈[1,N]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        由于相同美味值的蛋糕之间没有区别, 因此我们首先按照美味值进行分组
        贪心地想, 对于任意局面, Alice的最优策略一定是选择吃掉可用的美味值最小的蛋糕
        因为吃掉比它更大的蛋糕带来的收益仍为1, 但代价是对下次吃的蛋糕要求更高, 显然是劣的
        Bob的操作也有个很明显的性质: 如果选择吃掉美味度为x的蛋糕, 那么必须在Alice吃到x之前, 把所有
        美味度等于x的蛋糕全部吃掉, 这样才是有意义的
        我们考虑把问题建模为01背包
        分出来的m组蛋糕视为m个物品, 每个物品的代价为该组蛋糕的数量
        dp[i][j] := 考虑前i个物品, 背包容量为j时, 未选的最小物品数量
        下面考虑状态转移:
        (1)如果不选第i个物品, 那么Alice必然选择这个物品, Bob会多一次吃蛋糕的机会, 即背包容量加一
            dp[i + 1][j + 1] = min(dp[i + 1][j + 1, dp[i][j] + 1)
        (2)如果选第i个物品, 那么Bob必须消耗cnt[i]个吃蛋糕机会, 即背包容量减cnt[i]
            dp[i + 1][j - cnt[i]] = min(dp[i + 1][j - cnt[i]], dp[i][j])
        最后答案为dp[n][0:n]的最小值
*/
void chmin(int &x, int y) {
    if(x > y) {
        x = y;
    }
}
void solve() {
    int n;
    cin >> n;
    vector<int> cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }    
    vector<int> a{0};
    for(int i = 1; i <= n; i++) {
        if(cnt[i]) {
            a.push_back(i);
        }
    }
    n = a.size() - 1;
    vector<int> dp(n + 1, inf);
    dp[0] = 0;
    for(int i = 0; i < n; i++) {
        vector<int> ndp(n + 1, inf);
        for(int j = 0; j <= i; j++) {
            chmin(ndp[j + 1], dp[j] + 1);
            if(j - cnt[a[i + 1]] >= 0) {
                chmin(ndp[j - cnt[a[i + 1]]], dp[j]);
            }
        }
        swap(dp, ndp);
    }
    cout << *min_element(dp.begin(), dp.end()) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
