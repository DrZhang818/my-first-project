#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2134/problem/E
/*
    DP || 交互 || 构造
    题意:
        这是一个交互式问题
        你有N个盒子, 编号为1到N, 每个盒子有一个神秘能量值a[i], 这个值只能是1或2
        起初, 第i个盒子被放置在数轴上的坐标i, 你可以进行以下两种操作:
        "swap x": 交换当前位于坐标x和x + 1的两个盒子
        "throw x": 向位于坐标x的盒子扔一个球, 如果该盒子的能量值是p, 球会向前跳跃p个单位, 抵达坐标
                   x + p, 如果新坐标上还有盒子, 球会继续根据那个盒子的能量值跳跃, 直到球落在一个
                   没有盒子的坐标为止。 你将获得球跳跃的总次数作为回应
        你的任务是在不超过ceil(3N / 2)次操作内, 确定每个盒子的能量值
        范围: N∈[2,1000]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先观察题目性质, 由于小球只能向前跳跃, 因此构成一个标准的DAG, 我们很自然想到dp
        定义dp[i] := 从盒子i开始跳跃, 能够得到的总次数
        则有转移方程 dp[i] = dp[i + a[i]] + 1
        由于a[i]∈{1,2}, 因此我们只需关注 dp[i + 1] 和 dp[i + 2]即可
        不难发现, 如果 dp[i + 1] ≠ dp[i + 2], 我们可以通过 "throw i" 直接确定a[i]
        因此, 我们的核心任务就是: 如何在规定次数内处理 dp[i + 1] = dp[i + 2]这种情况
        我们允许的效率是每个盒子最多1.5次操作, 或者说每2个盒子最多3分配3次操作
        这里有个关键观察:
            当dp[i + 1] = dp[i + 2]时, 由于转移方程dp[i] = dp[i + a[i]] + 1, a[i]∈{1,2}
            因此必然有 dp[i] = dp[i + 1] + 1 ≠ dp[i + 1]
            这样对于dp[i - 1]来说, dp[i] 和 dp[i + 1]一定不同, 这就转化成了上面的情况
        于是我们可以直接确定a[i - 1], 然后利用"swap i", 把i调整到i - 1再次查询, 就能确定a[i]
        这样做可以完美处理偶数情况, 但对于奇数情况来说有些麻烦
        对于i = 1来说, 如果dp[2] = dp[3], 我们就不能采取上面的做法了
        但正由于dp[2] = dp[3], 我们必然能推出dp[3] ≠ dp[4]
        因此这种情况我们可以"swap 1", 将1调整到2, 然后"throw 2"即可判断
*/
//优化解法
void solve() {
    int n;
    cin >> n;
    vector<int> ans(n + 1);
    vector<int> dp(n + 3);
    auto q1 = [&](int x) -> void {
        cout << "swap " << x << endl;
    };
    auto q2 = [&](int x) -> int {
        cout << "throw " << x << endl;
        int c;
        cin >> c;
        return c;
    };
    for(int i = n; i >= 1; i--) {
        if(dp[i + 1] != dp[i + 2]) {
            dp[i] = q2(i);
            if(dp[i] == dp[i + 2] + 1) {
                ans[i] = 2;
            } else {
                ans[i] = 1;
            }
        } else if(i > 1) {
            if(q2(i - 1) == dp[i + 1] + 1) {
                ans[i - 1] = 2;
            } else {
                ans[i - 1] = 1;
            }
            
            q1(i - 1);
            
            dp[i - 1] = q2(i - 1);
            if(dp[i - 1] == dp[i + 1] + 1) {
                ans[i] = 2;
            } else {
                ans[i] = 1;
            }
            dp[i] = dp[i + 1] + 1;
            i--;
        } else {
            q1(1);
            if(q2(2) == dp[3] + 1) {
                ans[i] = 1;
            } else {
                ans[i] = 2;
            }
        }
    }
    cout << "!";
    for(int i = 1; i <= n; i++) {
        cout << " " << ans[i];
    }
    cout << endl;
}





// void solve() {
//     int n;
//     cin >> n;
//     vector<int> ans(n + 1);
//     vector<int> dp(n + 3);
//     auto q1 = [&](int x) -> void {
//         cout << "swap " << x << endl;
//     };
//     auto q2 = [&](int x) -> int {
//         cout << "throw " << x << endl;
//         int cnt;
//         cin >> cnt;
//         return cnt;
//     };  

//     for(int i = n - 1; i >= 1; i -= (i == 2 ? 1 : 2)) {
//         int c1, c2;
//         if(dp[i + 2] == dp[i + 3]) {
//             c1 = q2(i);
//             q1(i);
//             if(n % 2 != 1 || i != 1) {
//                 c2 = q2(i);
//             } else {
//                 if(ans[2] == 1) {
//                     c2 = c1 + 1;
//                 } else {
//                     c2 = dp[3] + 1;
//                 }
//             }
//             if(c1 == dp[i + 2] + 2 && c2 == dp[i + 2] + 2) {
//                 if(n % 2 != 1 || i != 1) ans[i + 1] = 1;
//                 ans[i] = 1;
//             } else if(c1 == dp[i + 3] + 2 && c2 == dp[i + 2] + 1) {
//                 if(n % 2 != 1 || i != 1) ans[i + 1] = 2;
//                 ans[i] = 1;
//             } else if(c1 == dp[i + 2] + 1 && c2 == dp[i + 3] + 2) {
//                 if(n % 2 != 1 || i != 1) ans[i + 1] = 1;
//                 ans[i] = 2;
//             } else {
//                 if(n % 2 != 1 || i != 1) ans[i + 1] = 2;
//                 ans[i] = 2;
//             }
//             dp[i + 1] = dp[i + 1 + ans[i]] + 1;
//             dp[i] = dp[i + ans[i + 1]] + 1;
//         } else {
//             if(n % 2 != 1 || i != 1) c1 = q2(i + 1);
//             q1(i);
//             c2 = q2(i + 1);

//             if(n % 2 != 1 || i != 1) {
//                 if(c1 == dp[i + 2] + 1) {
//                     ans[i + 1] = 1;
//                 } else {
//                     ans[i + 1] = 2;
//                 }
//             }

//             if(c2 == dp[i + 2] + 1) {
//                 ans[i] = 1;
//             } else {
//                 ans[i] = 2;
//             }

//             dp[i + 1] = dp[i + 1 + ans[i]] + 1;
//             dp[i] = dp[i + ans[i + 1]] + 1;
//         }
//     }
//     cout << "!";
//     for(int i = 1; i <= n; i++) {
//         cout << " " << ans[i];
//     }
//     cout << endl;
// }

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
