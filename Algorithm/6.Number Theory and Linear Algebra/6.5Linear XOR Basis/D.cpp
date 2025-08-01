#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef uint32_t u32;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://leetcode.cn/problems/partition-array-for-maximum-xor-and-and/description/
/*
    枚举 || 线性基 || DP || 数学 || 贪心
    题意:
        给定一个长度为N的数组, 你需要把数组划分成恰好三个子序列(可以为空)A,B,C
        最大化XOR(A) + AND(B) + XOR(C)的值
        范围: N∈[1,19], a[i]∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        由于N很小, 这提示我们要枚举集合
        由于XOR(A)与XOR(C)都是异或运算, 这样相同类型的运算可能会产生一些好的性质
        因此我们考虑枚举集合B, 令U - B = S, 则有S = A + C
        我们思考XOR(S)与XOR(A) + XOR(C)有没有什么关系
        首先二者有这样一个关系: XOR(S) = XOR(A) ^ XOR(C)
        (1)对于XOR(S)中为1的比特位, 无论怎么划分, XOR(A)和XOR(C)一定是一个为1一个为0
            那么XOR(A) + XOR(C)的这一位固定为1
        (2)对于XOR(S)中为0的比特位, XOR(A)和XOR(C)要么同为0要么同为1
            因此XOR(A) + XOR(C)的这一位可能为0可能为2
            虽然结果不一样, 但有一样东西是不变的: XOR(A)在这一位上的异或和 = XOR(C)在这一位的异或和
            只考虑有偶数个1的比特位(特殊比特位), 把S中的每个数的非特殊比特位改成0, 得到一个新的集合
            S', 然后把S'划分为A'和C', 由于XOR(A') = XOR(C'), 得XOR(A') + XOR(C') = 2*XOR(A')
        所以XOR(A) + XOR(C) = XOR(S) + 2 * XOR(A')
        由于XOR(S)是个定值, 问题转化为计算XOR(A')的最大值, 即:
            从S'中选择一些数A', 计算这些数的最大异或和
        这是线性基的标准应用
        此外, 如何预处理每个子集的AND和XOR呢? 
        我们可以写一个状压DP做预处理
        剪枝:
            XOR(A)和XOR(C)的理论最大值是OR(U - B)
            如果AND(B) + 2 * OR(U - B) <= ans, 那么答案不可能增大, 跳过计算
            进一步的, 对于XOR(U - B)中等于1的比特位, XOR(A)+XOR(C)在这些位上恒为1, 不可能是2
            因此AND(B) + 2 * OR(U - B) - XOR(U - B) <= ans时, 跳过计算

*/
class XorBasis {
    vector<u32> b;
public:
    XorBasis(int n) : b(n) {}
    void insert(u32 x) {
        while(x) {
            int i = bit_width(x) - 1;
            if(b[i] == 0) {
                b[i] = x;
                return;
            }
            x ^= b[i];
        }
    }
    u32 xor_max() {
        u32 res = 0;
        for(int i = b.size() - 1; i >= 0; i--) {
            res = max(res, res ^ b[i]);
        }
        return res;
    }
};
class Solution {
public:
    ll maximizeXorAndXor(vector<int>& a) {
        int n = a.size(), mx = 0;
        int sz = bit_width(u32(*max_element(a.begin(), a.end())));
        const int N = 1 << n;
        vector<int> sub_xor(N), sub_and(N), sub_or(N);
        sub_and[0] = -1;
        for(int i = 0; i < n; i++) {
            int x = a[i];
            int high_bit = 1 << i;
            for(int s = 0; s < high_bit; s++) {
                sub_xor[high_bit | s] = sub_xor[s] ^ x;
                sub_and[high_bit | s] = sub_and[s] & x;
                sub_or[high_bit | s] = sub_or[s] | x;
            }
        }
        auto query = [&](int s) -> ll {
            XorBasis b(sz);
            ll _xor = sub_xor[s];
            for(int i = 0; i < n; i++) {
                if(s >> i & 1) {
                    b.insert(a[i] & ~_xor);
                }
            }
            return _xor + 2LL * b.xor_max();
        };
        sub_and[0] = 0;
        ll ans = 0;
        for(int u = 0; u < N; u++) {
            int s = (N - 1) & ~u;
            if(sub_and[u] + 2LL * sub_or[s] - sub_xor[s] <= ans) continue;
            ans = max(ans, sub_and[u] + query(s));
        }   
        return ans;
    }
};