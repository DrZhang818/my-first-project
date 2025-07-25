#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2119/problem/D
/* 
    DP || 组合数学
    题意:
        给定N个盒子和N个小球, 编号分别为1~N, 你将会按照编号从小到大的顺序依次进行N次操作
        op: 对于编号为i的盒子, 选择一个0~i之间的数字j
            如果j = 0, 则不能选球;
            如果j ≠ 0, 则从编号在[j,i]之间的未被选过的小球中任选一个
        两个选球方案被认为是不同的, 当且仅当存在t∈[1,N], 使得编号为t的盒子所进行的操作不同
        两个操作是不同的, 当且仅当选择的j不同, 或选到的小球不同
        求出选球方案总数
        由于答案过大, 每组数据给定一个模数MOD, 只需要输出答案 % MOD
        范围: N∈[1,5000], MOD∈[1e8, 1.01e9] 
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数据结构
        首先思考暴力方法, 把每个盒子选择的j当作一个序列S, 显然有(n+1)!个序列
        枚举每个序列, 从前到后遍历每个盒子, 枚举每个盒子可选择的小球
        这样时间复杂度显然是爆炸的, 我们要设计出合适的状态来划分等价类, 利用贡献法一次性算出大量方案数
        考虑选球问题常用的dp设计, 定义f(i,j) := 考虑前i个盒子, 选了j个球时的方案数
        由于"枚举每个序列"是必须要优化掉的, 因此在考虑状态转移的时候必须把这一项引入进来
        下面考虑状态转移:
        枚举到第i个盒子时, 考虑第i个盒子选择数字p∈[0,i]
        当p=0时比较简单, 有f(i,j) = f(i-1,j)
        当p≠0时, 我们需要知道p~i中有多少个球没有被选到, 而现在已有的状态无法表示这一信息
        此外, 由于涉及枚举p, 时间复杂度至少是O(n^3), 这是无法接受的

        我们刚才是从盒子选球的角度出发的, 如果改为球选盒子能否有机会呢? 这是常用的换维思考
        定义f(i,j) := 考虑前i个球, 选了j个盒子时的方案数
        枚举到第i个球时, 考虑第i个球选择某个盒子
        (1)如果这个球不放进盒子, 那么f(i,j) = f(i-1,j)
        (2)如果这个球放进盒子, 那么必然是[i,n]之间的某个盒子
            于是我们需要维护[i,n]中未被选择的盒子数量
            这同样无法维护, 因为前面1~i-1个球选择的盒子可能占据了[i,n], 占据的个数无法得知
        但我们立刻意识到, 第i个球选择的盒子必然占据前1~i-1个球可选的盒子, 由于这种必然性
        使得占据的个数是可以确定的, 因此就有了下面的逆向求解:
        
        定义f(i,j) := 考虑第i~n个球, 选了j个盒子时的方案数
        倒序枚举到第i个球时, 考虑第i个球是否选择某个盒子
        (1)如果这个球不放进盒子, 那么f(i,j) = f(i+1,j)
        (2)如果这个球放进盒子, 那么必然是[i,n]之间的某个盒子
            于是我们需要维护[i,n]中未被选择的盒子数量
            这时我们会惊奇发现, 由于第i+1~n个球选择的盒子必然在[i,n]之间
            因此我们维护了f(i+1,j), 那么选了的这j个盒子就是[i,n]之间已经被选过的盒子数量
            因此[i,n]之间未被选择的盒子数量为 n - i + 1 - j
            而由于每个盒子如果想选择第i个球, 那么这个盒子选择的编号必须在[1,i]之间
            因此选择第i个球带来的贡献是(n-i+1-j)*i
            根据乘法原理
            f(i,j+1) = f(i+1,j) * (n - i + 1 - j) * i
        综上, f(i,j+1) = f(i+1,j+1) + f(i+1,j) * (n - i + 1 - j) * i
        最后, 答案为∑f(1,i), i∈[0,n]
*/
void solve() {
    int n;
    ll MOD;
    cin >> n >> MOD;
    vector<ll> dp(n + 1);
    dp[0] = 1;
    for(int i = n; i >= 1; i--) {
        for(int j = n - i; j >= 0; j--) {
            dp[j + 1] = (dp[j + 1] + dp[j] * (n - i + 1 - j) % MOD * i % MOD) % MOD;
        }
    }
    ll ans = 0;
    for(int i = 0; i <= n; i++) {
        ans = (ans + dp[i]) % MOD;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
