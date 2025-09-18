#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
const int N = 70000;

//https://leetcode.cn/problems/sum-of-beautiful-subsequences/description/
/*
    组合数学 || DP || 数据结构
    题意:
        给定一个长度为N的数组a, 定义子序列S的权值为 f(S) = gcd(S)
        对于a的每个严格递增子序列S, 求出 ∑f(S), 结果对1000000007取模
        范围: N∈[1,1e4], a[i]∈[1,7e4]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        我们首先思考easy版本, 不考虑"严格递增"这个条件的话, 应该如何求呢?
        问题变成对于所有子序列S, 求解∑f(S)
        这是个经典的问题, 我们可以用"倍数容斥"来做
        定义dp[i] := 满足gcd(S)为i的倍数的子序列个数
        为了求解dp[i], 我们可以定义cnt[g] := 有多少个a[i]包含因子g
        则有dp[i] = C(cnt[i], 1) + C(cnt[i], 2) + ... + C(cnt[i], cnt[i])
                  = 2^cnt[i] - 1
        接着, 我们倒序做一次倍数容斥, 把dp[i]减去dp[k * i], k∈[2, inf) ∧ k * i <= mx
        容斥后, dp[i]就变成 满足gcd(S)恰好为i的子序列个数
        ∑ (dp[i] * i) 就是答案
        
        接下来考虑另一个easy问题: 如何求解所有"严格递增"的子序列个数
        这是个经典的树状数组优化dp问题
        定义dp[i][x] := 考虑前i个数, 结尾为x的严格递增子序列个数
        则有转移 dp[i][a[i]] = 1 + ∑dp[i - 1][x], 其中1 <= x < a[i]
        
        想清楚这两个easy问题, 我们就可以思考原问题了
        如何将二者结合起来呢? 我们有了个自然的DP套DP的做法
        定义dp[i] := 满足gcd(S)为i的倍数的"严格递增"子序列个数
        这时求解dp[i]就不能再用组合数学的方法了, 我们需要把第二个easy问题的思路迁移过来
        我们可以对数组进行一下处理: 我们创建一个数组b, 其中只保留数组a中是i的倍数的那些数
        我们在数组b上完成第二个easy问题, 得到的答案天然就是dp[i]的答案
        因此, 我们可以按顺序预处理出数组b, 在值域7e4内, 每个数的因子个数最多120个
        故最多有O(D * N)个数

        问题在于, 每次做第二个easy问题时, 我们都需要清空树状数组, 每次重新开的时间就已经O(M^2)了
        M是数组中的最大值
        如何解决这一问题呢?
        这里用到一个trick: 用时间戳懒初始化
        我们可以在树状数组中加入时间t和时间数组time
        time记录树上每个节点存储值的时间
        每次进行第二个问题时, 我们都让t++
        修改时, 如果time不等于t, 我们就让tr[o]清零, 并令time[o] = t
        查询时, 如果time不等于t, 说明time存储的值是之前的值, 我们将其忽略即可
*/


inline int lowbit(int o) { return o & -o; }
void add_mod(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
vector<int> fac[N + 1];
auto init = []() -> int {
    for(int i = 1; i <= N; i++) {
        for(int j = i; j <= N; j += i) {
            fac[j].push_back(i);
        }
    }
    return 0;
}();
class Solution {
public:
    struct BIT {
        vector<int> tr;
        vector<int> time;
        int n, t;
        BIT(int x) : tr(x + 1), time(x + 1), n(x), t(0) {}
        void add(int o, int d) {
            for(; o <= n; o += lowbit(o)) {
                if(time[o] != t) {
                    time[o] = t;
                    tr[o] = 0;
                }
                add_mod(tr[o], d);
            } 
        }
        int query(int o) {
            int res = 0;
            for(; o > 0; o -= lowbit(o)) {
                if(time[o] == t) {
                    add_mod(res, tr[o]);
                }
            }
            return res;
        }
    };
    int totalBeauty(vector<int>& a) {
        int mx = *max_element(a.begin(), a.end());
        vector<vector<int>> adj(mx + 1);
        for(int x : a) {
            for(int g : fac[x]) {
                adj[g].push_back(x);
            }
        }
        BIT tr(mx);
        vector<int> dp(mx + 1);
        for(int g = 1; g <= mx; g++) {
            tr.t++;
            for(int x : adj[g]) {
                int c = tr.query(x - 1);
                tr.add(x, 1 + c);
                add_mod(dp[g], 1 + c);
            }
        }
        
        for(int i = mx; i >= 1; i--) {
            for(int j = i * 2; j <= mx; j += i) {
                add_mod(dp[i], MOD - dp[j]);
            }
        }
        
        int ans = 0;
        for(int i = 1; i <= mx; i++) {
            add_mod(ans, 1LL * i * dp[i] % MOD);
        }
        return ans;
    }
};