#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://leetcode.cn/problems/count-beautiful-numbers/description/
/*
    数位DP
    题意:
        给定区间[L,R], 计算区间内合法数字的数量
        一个数字是合法的, 当且仅当它的数位之积被数位之和整除
        范围: L,R∈[1,1e9]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数据结构
        首先思考暴力做法, 验证一个数字的时间为log_10, 总复杂度为O(nlogn), 超时
        瓶颈在于暴力做法需要逐个验证, 所以任何优化方法都必须跳过逐个判断才能起作用
        很容易想到数位DP来优化, 因为32...和23...的计算结果完全相同(在没有前导零和数值限制下)
        这意味着有很多状态是重复计算的, 可以用记忆化的方式保证只算一次
        数位DP的过程很容易, 只需要设计出a表示当前选出来的数的乘积, b表示累加和
        而pos, lead, lim都是经典数位dp的必备参数, 套用即可
        比较难的是记忆化数组由于乘积很大(上界为9^9), 显然不能直接开大数组
        解决方法是使用map<tuple<int,int,int>,int>, 或者像本文一样写个Hash函数
        Hash更快一些但不保险
        DP过程中注意前导0和lim状态正确转移即可得到正确答案
        这样我们就能得到[1,x]的合法数量
        而要计算区间[L,R]的合法数量, 只需计算出[1,R]再减去[1,L-1]即可
*/
class Solution {
public:
    ull Hash(ull a, ull b, ull pos) {
        ull base = 131;
        return a * 131 * 131 + b * 131 + pos;
    }
    int num[12];
    int cnt = 0;
    unordered_map<ull,int> mp; 
    int dfs(int a, int b, int pos, bool lead, bool lim) {
        if(pos == 0) {
            if(lead) return 0;
            return a % b == 0;
        }
        ull H = Hash(a, b, pos);
        int &t = mp[H];
        if(!lead && !lim && t) return t;
        int up = (lim ? num[pos] : 9);
        int res = 0;
        for(int i = 0; i <= up; i++) {
            if(i == 0 && lead) {
                res += dfs(a, b, pos - 1, true, lim && i == up);
            }
            else res += dfs(a * i, b + i, pos - 1, false, lim && i == up);
        }
        if(!lead && !lim) {
            t = res;
        }
        return res;
    }
    int solve(int x) {
        cnt = 0;
        while(x) {
            num[++cnt] = x % 10;
            x /= 10;
        }
        return dfs(1, 0, cnt, true, true);
    }
    int beautifulNumbers(int l, int r) {
        return solve(r) - solve(l - 1);        
    }
};