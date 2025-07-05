#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://leetcode.cn/problems/find-sum-of-array-product-of-magical-sequences/
/*
    DP || 组合数学
    题意:
        给定一个长度为N的数组a(下标从0开始)和两个整数M和K
        定义一个下标序列idx是合法的, 当且仅当序列长度为M, 且序列元素idx[i]∈[0,N-1],
        且∑2^idx[i]的二进制形式恰好有K个置位
        定义一个合法下标序列的权值为Πa[idx[i]]
        请你求出所有合法下标序列的权值之和, 结果对1000000007取模
        范围: M∈[1,30], K∈[1,M], N∈[1,50], a[i]∈[1,1e8]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先思考暴力做法, 我们需要枚举所有合法序列, 并检查合法性, 如果合法就加入答案
        时间复杂度为O(A[N][M] * M), 超时
        优化的关键在于, 如何解决"状态量爆炸"这个问题, 对于计数类问题, 可以往贡献法上思考
        (1)我们发现, 一个序列的顺序与权值无关, 这意味着我们只需要枚举无序可重集合就可以了,
            利用这一性质, 我们可以把时间复杂度优化为O(C[N][M] * M)
        (2)我们发现, 枚举集合这件事可以简化为: 枚举第i个位置选了多少次
        下面思考: 对于一个合法的集合, 它对应多少个合法的序列
        由组合数学知识, 设第i个位置选了p[i]次
        那么数量为: M! / Πp[i]!
        因此这个合法集合对答案的贡献为: M! * Πa[i]^p[i] / Πp[i]
        由于所有合法集合都有系数M!, 我们可以提出这一项, 那么问题转化成
        Πa[i]^p[i] / Πp[i] = Π(a[i]^p[i] / p[i])
        这意味着, 每个位置的次数选择是相互独立的, 这是个重要的无后效性信息
        我们可以设计出f(i,j) := 当前枚举到第i个位置, 选了j个数得到的答案
        这样我们就避免了逐一访问集合, 把状态数量优化成了O(NM)
        当然这样处理会丢失对合法性的检查, 我们还需要额外的关于"合法性"的状态信息
        朴素的想法是, 把当前集合的s = ∑2^idx[i]作为状态, 只要(i,j,s)相同答案就相同
        但这显然是不可行的, 因为n∈[1,50], s的数量级太大了
        这里就用到一个关键性的trick: 由于选到第i位的时候, 新加入集合的元素是2^i,
        这在位信息中对于0~i-1位是不会产生任何影响的, 因此我们可以提前算出0~i位的贡献cnt
        记录s >> i这个信息传递给i + 1位, 这样(i,len,s,cnt)就可以完美描述任意时刻集合的状态了
        下面考虑状态转移:
        对于f(i,len,s,cnt):
            枚举第i位选j次, j∈[0,m-len]
            那么有f(i,len,s,cnt) = ∑f(i+1,len+j,(s+j)>>1,cnt+((s+j)&1))
*/
const int MOD = 1000000007; 
ll pow_mod(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
vector<ll> fac(31), inv_fac(31);
auto init = [] {
    fac[0] = inv_fac[0] = 1;
    for(int i = 1; i <= 30; i++) fac[i] = fac[i - 1] * i % MOD, inv_fac[i] = pow_mod(fac[i], MOD - 2);    
    return 0;
}();

class Solution {
public:
    int magicalSum(int m, int k, vector<int>& a) {
        int n = a.size();
        vector memo(n + 1, vector<vector<vector<ll>>>(m + 1, vector<vector<ll>>(m / 2 + 1, vector<ll>(k + 1, -1))));
        vector<vector<ll>> pow(n + 1, vector<ll>(m + 1, 1));
        for(int i = 0; i < n; i++) {
            for(int j = 1; j <= m; j++) {
                pow[i][j] = pow[i][j - 1] * a[i] % MOD;
            }
        }
        auto dfs = [&](this auto &&dfs, int i, int len, int s, int cnt) -> ll {
            if(i == n) return len == m && __builtin_popcount(s) + cnt == k;
            if(cnt > k || m - len + __builtin_popcount(s) < k - cnt) return 0; 
            ll &res = memo[i][len][s][cnt];
            if(res != -1) return res;
            res = 0;
            for(int j = 0; j <= m - len; j++) {
                ll r = dfs(i + 1, len + j, (s + j) >> 1, cnt + ((s + j) & 1));
                res = (res + r % MOD * pow[i][j] % MOD * inv_fac[j] % MOD) % MOD;
            }
            return res;
        };
        return fac[m] * dfs(0, 0, 0, 0) % MOD;
    }
};