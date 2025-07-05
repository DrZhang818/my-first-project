#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://leetcode.cn/problems/concatenated-divisibility/description/
/*
    状压DP || 贡献法 || 抽屉原理
    题意:
        Alice拿到了N个数字卡片和一个正整数k, 她想找到这N个数字的一种排列, 
        使得按照排列顺序连接起来后得到的数字能够被k整除, 但由于排列方式实在太多了,
        这对于数学不好的Alice来说很困难, 因此她把这个任务交给了你
        形式化地, 有一个长度为N的数组[a1,a2,...,an], 你可以对数组进行重排列,
        使得排列后得到的b1b2...bn能够被k整除, 如果有多组解, 输出[b1,b2,...,bn]字典序
        最小的方案
        范围: N∈[1,13], a[i]∈[1,1e5], k∈[1,100]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先思考暴力方法, 枚举所有可能的排列并验证, 时间复杂度为O(n!), n最大为13无法接受
        这种属于状态数量过大的问题, 回想数位DP的朴素算法
        这种问题是无法通过优化手段来加速的, 我们唯一的手段就是贡献法
        通过一种状态快速推导出大量其他状态, 从而避免对于这些状态的访问
        本题的关键就在于k的范围很小, 这启示我们可以利用"模k同余类"来对状态进行划分
        假设我们从n个数中选择了m个, 这m个数字的排列有m!种, 而m!是远大于k的
        由抽屉原理, 这里有大量重复状态!
        这意味着, 在模k意义下, 原本对m!种的讨论被我们压缩成了对k种的讨论
        这有什么帮助呢? 我们回顾下数字拼接模k的转移方程
        rem = (rem * pow(10,len(x)) + x) % k
        我们会发现, 填写后续的(n-m)个数的时候, 我们只关心前m个数拼接后的rem
        因此模k同余类里面的每一个元素都能代表整个等价类, 我们算出一种后, 其余的状态无需计算!
        有了这一点后, 我们再回看题目, 会发现题目从枚举排列变成了枚举子集与rem的问题
        也可以理解为, 我们把排列的"顺序"这个信息压缩成了排列的"余数"
        这样状态就从[选的数][顺序] 变成了[选的数][余数]
        由于顺序->余数这个映射是多对一, 因此一定会有重复访问, 我们用memo数组来记忆化
        [选的数]这个状态可以利用二进制状压来记录
        至此我们解决了状态数过大的问题, 下一个问题是如何找到字典序最小的方案
        这点很好想, 由于dfs的搜索顺序是可控的, 我们贪心地对数组排个序, 这样第一个搜到
        的合法状态必然是全局最小方案
*/
class Solution {
public:
    int pow_mod(int a, int b, int mod) {
        int res = 1;
        a %= mod;
        while(b) {
            if(b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }
    vector<int> concatenatedDivisibility(vector<int>& a, int k) {
        sort(a.begin(), a.end());
        int n = a.size();
        vector<int> ans, len(n);
        vector memo(1 << n, vector<int>(k + 1, -1));
        for(int i = 0; i < n; i++) len[i] = pow_mod(10, to_string(a[i]).size(), k);
        auto dfs = [&](this auto &&dfs, int s, int rem) -> bool {
            if(s == (1 << n) - 1) return rem == 0;
            if(memo[s][rem] != -1) return memo[s][rem];
            for(int i = 0; i < n; i++) {
                if(s >> i & 1) continue;
                ans.push_back(a[i]);
                if(dfs(s | (1 << i), (rem * len[i] + a[i]) % k)) {
                    return true;
                }
                ans.pop_back();
            }
            memo[s][rem] = false;
            return false;
        };
        dfs(0, 0);
        return ans;
    }
};