#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.luogu.com.cn/problem/P1880
/*
    DP || 前缀和优化 || 四边形不等式优化(未写)
    题意:
        有N堆石子分布在一个圆上, 每堆石子的石子数量为A[i]
        你可以进行以下操作:
        op: 选择两堆相邻的石子合并成一堆, 代价为两堆石子数量之和
        求将N堆石子合并成一堆所需的最小代价和最大代价
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->贪心||DP, 常用优化手段为: 二分、前缀和、双指针、数据结构、
        首先对于环形问题, 我们考虑能否利用断环成链来简化问题
        对于链状的石子合并问题, 实际上可以理解为把一个环沿着某个分界点断开了
        对于环状的, 我们一共要进行n-1次操作, 那么记最后一次操作的两堆石子中间的分界点为P
                    则其等价于处理以P为分界点的链状问题
        于是问题简化为在1~2N的链上求出每个长度为N的区间合并的最小/大值
        暴力求解的方法需要枚举O(N!)种合并方式, 优化的关键在于大区间的最优解可以由小区间得到
        我们定义f(i,j) := 合并区间[i,j]的最优解
        通过枚举最后一个不同点, 我们可以通过以下子问题来解决父问题
        合并一个区间时, 需要两个被合并的区间已经被合并为一个石子
        我们可以通过枚举两个被合并区间的分界点来完成状态转移, 下面以最小代价为例
        定义k∈[i,j), 则f(i,j) = min{f(i,k) + f(k+1,j) + ∑a[i:j]}
        判断一个转移方程是否正确, 就看它是否做到了不重不漏
        我们不考虑f(i,k)和f(k+1,j)具体如何得到, 只看最后一步合并成f(i,j)时是否
        覆盖了全部情况, 这是显然的
        因此我们就完成了状态转移, 下面考虑状态初值
        f(i,i) = 0
        接着考虑如何填写DP表
        由于f(i,j)只会用到长度比它小的子区间, 因此我们最外层枚举区间长度
        接着枚举区间起点i, 并由i和len来得到j
        最后枚举分界点k, 通过子区间进行状态转移
        最后获取答案, 我们找到所有长度为N的f(i,j), 取最优值就是环形的最优值
*/
constexpr int inf = 1000000000;
void solve() { 
    int n;
    cin >> n;
    vector<int> a(2 * n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    vector<int> pre(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    vector mndp(2 * n + 1, vector<int>(2 * n + 1));
    vector mxdp = mndp;
    for(int len = 2; len <= n; len++) {
        for(int i = 1; i + len - 1 <= 2 * n; i++) {
            int j = i + len - 1;
            mndp[i][j] = inf;
            mxdp[i][j] = -inf;
            for(int k = i; k < j; k++) {
                mndp[i][j] = min(mndp[i][j], mndp[i][k] + mndp[k + 1][j] + pre[j] - pre[i - 1]);
                mxdp[i][j] = max(mxdp[i][j], mxdp[i][k] + mxdp[k + 1][j] + pre[j] - pre[i - 1]);
            }
        }
    }
    ll mx = -inf, mn = inf;
    for(int i = 1; i < n + 1; i++) {
        mn = min(mn, (ll)mndp[i][i + n - 1]);
        mx = max(mx, (ll)mxdp[i][i + n - 1]);
    }
    cout << mn << "\n" << mx << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
