#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/contest/2084/problem/D
/*
    构造 || 贪心
    题意:
        给定三个正整数n,m,k, 对于一个由非负整数组成的数组b, 你可以进行以下操作:
        op: 删除一段长度为k的区间, 并将剩余部分拼接起来
        定义f(b)为对数组b进行至多m次操作(可以为0)后, mex(b)的最小值
        现在你需要构造一个长度为n的数组a, a[i]∈[0,1e9], 使得f(a)最大
        范围: n∈[2,2e5], m∈[1,n), k∈[1,n), m*k∈[1,n)
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先观察题目性质, 对于mex的构造题, 常用的思考方式就是从小到大贪心构造
        分析题目给的m和k:
        (1)m是删的次数, 意味着从小到大每个数至少要出现m+1次
        (2)k是间隔, 意味着每两个相同的数间隔至少为k, 否则可以在一次操作中同时删除, 贪心的想
           这样放一定是不优的
        于是我们可以总结出答案应有的特征: 从小到大每个数至少出现m+1次, 并且间隔至少为k
        接下来细致的思考一下, 我们可以确定一种贪心策略:
        (1)从小到大每个数恰好出现m+1次是最优的, 因为任何多余出现替换成别的数字都是不劣的
        (2)在满足(1)的前提下, 设出现的数字最大为up, 那么0~up为一组不断循环一定是最优的
           因为间隔是由不同的数字放在一起产生的, 把0~up分为一组, 对每个数来说都能最大化间隔
        下面的难题就是如何确定up了, 这是本题最核心的难点
        对于一个复杂问题, 我们可以采用区间估计法, 即估计它的下界和上界, 不断向中间逼近
        首先一定有 up >= k, 由上述讨论, 间隔至少为k, 而up就是间隔, 因此up >= k
        再来考虑up的上界:
            由于从小到大每个数至少出现m + 1次, 因此up <= n / (m + 1)
        现在有了up的取值范围, up∈[k, n/(m+1)], 我们思考最优解是否有单调性
        我们会发现, 随着up的增大, 间隔越来越大, 出现次数越来越少
        而由上述讨论, 出现次数恰好为m + 1时是最优的, 因此up直接取定义域内最大值即可
        故得到up = max(k, n / (m + 1))
*/
void solve() { 
    int n, m, k;
    cin >> n >> m >> k;
    int up = max(k, n / (m + 1));
    for(int i = 0; i < n; i++) {
        cout << i % up << " \n"[i == n - 1];
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
    
