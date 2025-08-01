#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://leetcode.cn/problems/maximum-number-of-subsequences-after-one-inserting/description/
/*
    DP || 贪心
    题意:
        给定一个长度为N的由大写字母构成的字符串S, 你最多进行一次以下操作:
        op: 在字符串任意位置插入一个大写字母
        求字符串可以形成的"LCT"子序列的最大数量
        范围: N∈[1,1e5]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        我们可以把答案拆为两部分: 原字符串的答案 + 新增答案
        对于原字符串的答案, 我们可以利用状态机DP解决
        定义:
        l表示遍历过的L个数
        lc表示遍历过的LC个数
        lct表示遍历过的LCT个数
        决策部分为如何最大化新增答案
        显然, 添加L,C,T之一才是有意义的
        添加L时, 我们希望右侧有更多的CT, 因此把L放开头是最优的
        添加T时, 我们希望左侧有更多的LC, 因此把T放末尾是最优的
        添加C时, 我们希望左侧L和右侧T的乘积更大, 这需要枚举每个位置
        因此我们额外定义:
        c表示遍历过的C个数
        ct表示遍历过的CT个数
        lt表示遍历到当前位置可以得到的LT最大乘积
        t表示后面还剩的t的个数
        下面考虑状态转移:
        遇到L时, l++
        遇到C时, c++, lc += l
        遇到T时, t--, ct += c, lct += lc
        每个位置都统计l * t
        最后答案为lct + max(lc, ct, lt)
*/
class Solution {
public:
    ll numOfSubsequences(string s) {
        ll l = 0, c = 0, t = count(s.begin(), s.end(), 'T');
        ll lc = 0, ct = 0, lt = 0, lct = 0;
        for(char b : s) {
            if(b == 'L') {
                l++;
            } else if(b == 'C') {
                lc += l;
                c++;
            } else if(b == 'T') {
                lct += lc;
                ct += c;
                t--;
            }
            lt = max(lt, l * t);
        }
        return lct + max({lc, ct, lt});
    }
};