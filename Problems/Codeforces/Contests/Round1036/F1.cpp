#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

//https://codeforces.com/contest/2124/problem/F1
/*
    DP || 组合数学
    题意:
        给定一个整数N, 你需要用若干段"r-循环移位排列"构造出一个长度为N的数组
        另给M个限制条件, 每个条件给定i,x, 构造出的数组必须满足a[i] ≠ x
        "r-循环移位排列": 排列1,2,...,r经任意次左移后得到的排列
        请你求出有多少种构造方式
        范围: N∈[1,100], M∈[0,min(N^2,5000)], i,x∈[1,N]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        对于这种多条件的问题, 我们先考虑不含限制条件的版本
        如何计算不带限制条件下, 构造长度为N的数组的方案数?
        可以尝试用dp来解决:
        定义dp[i] := 构建长度为i的数组的方案数
        考虑状态转移: 设当前状态为i, 下一步拼接长度为j的数组
        则有dp[i + j] += dp[i] * 合法数量
        但是这样的经典dp显然会遭到重复计数问题:
        例如1 2 1 有两种划分方式: [1][2,1]或[1,2][1]
        再如1 2 3 4 1 2 3, 可以划分为[1,2,3,4][1,2,3]或[1,2,3][4,1,2,3]
        我们尝试总结规律:
            [    ]1[    ][   ]1[   ]
               a     b     c     d
        (1)当a不为空时, 划分方式唯一:
            这点显然, 假设存在另一种划分方式, 那么一定是在b + c段找到一个新的分界点
            那么b与c一个长度减小一个长度增加
            b将无法与a衔接在一起, 因此是不合法的划分
        这一性质说明, 实际情况只有这种:
            1[   ][  ]1[   ]
               a    b    c
            下面a,b,c分别代指a,b,c段的长度
        (2)当a + b <= c时, 划分方式唯一:
            [1,a,b]是排列时, max(b) = 1+a+b <= 1+c, 而max([1,c]) = 1+c
                            因此[b,1,c]不是合法排列
            [b,1,c]是排列时, min(b) = 2+c, 而max([1,a]) = 1+a
                            2 + c = 1 + a ==> a = c + 1
                            但a + b <= c ==> b <= -1, 显然矛盾
                            因此[1,a,b]不是合法排列
        (3)当a + b > c时, 有且仅有两种划分方式
            1[   ][  ]1[   ]
               a    b    c
            ①当[1,a,b]是排列时, max(b) = 1+a+b > 1+c
                因此我们可以减小b的长度
                1[   ][ ][ ]1[  ]
                   a   b  d    c
                使得1+a+b=1+c, 此时d = [c+2,c_3,...]
                因此[d,1,c]为一个合法排列, 这便是第二种划分方式
            ②当[b,1,c]是排列时, min(b) = 2+c < 2+a+b <= 1+a+b
                如果a = c, 则min(b) = 2+a
                此时[1,a,b]是合法排列
                则[1,a,b][1,c]为第二种划分方式
        综上, 存在两种划分方式的充要条件是形如1[a][b]1[c]的段, 且a+b>c
            a,b,c代指段长
        思考去重方法: 我们只需要钦定其中一种来计数即可
        例如: 当我们的排列以1为开头时 [1,a]
              下一个拼接上的排列不能以2+a开头
            这样, ②的计数就被我们人工去除了, ①的计数仍然保留
            满足了不重不漏原则
        因此我们可以为dp数组增加两个维度:
        dp[i][j][0/1] := 构建长度为i的数组, 末尾元素为j, 开头元素是否为1的方案数
        下面考虑状态转移:
            我们需要暴力枚举新加入的长度为j的排列的首元素k
            并得到尾元素en = (k + j - 1) % j
            接下来枚举当前数组的尾元素las
            如果k != las + 1:
                dp[i+j][en][k==1] += dp[i][las][0] + dp[i][las][1]
            否则:
                dp[i+j][en][k==1] += dp[i][las][0]
        
        最后, ∑dp[n][j][0/1]就是答案
        初始状态:
            令dp[0][0][0] = 1, 表示什么都没有算作一种方案

        那么如何解决限制条件呢?
        很简单, 用一个邻接矩阵记录所有被ban的位置
        然后O(j)扫一遍即可, 检查首元素为k是否合法即可
*/
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    int n, m;
    cin >> n >> m;
    vector ban(n + 1, vector<bool>(n + 1));
    for(int i = 1; i <= m; i++) {
        int pos, x;
        cin >> pos >> x;
        ban[pos][x] = true;
    }
    vector dp(n + 1, vector(n + 1, vector<int>(2)));
    dp[0][0][0] = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i + j > n) continue;
            for(int k = 1; k <= j; k++) {
                int x = k, en = (k + j - 1) % j;
                bool ok = true;
                for(int p = i + 1; p <= i + j; p++) {
                    if(ban[p][x]) {
                        ok = false;
                        break;
                    }
                    x++;
                    if(x == j + 1) x = 1;
                }
                if(ok) {
                    for(int las = 0; las <= n; las++) {
                        add(dp[i + j][en][k == 1], dp[i][las][0]);
                        if(k != las + 1) {
                            add(dp[i + j][en][k == 1], dp[i][las][1]);
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        add(ans, dp[n][i][0]);
        add(ans, dp[n][i][1]);
    }
    cout << ans << "\n";
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
