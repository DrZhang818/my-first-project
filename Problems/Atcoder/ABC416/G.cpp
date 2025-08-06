#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc416/tasks/abc416_g
/*
    DP || 贪心 || 字符串理论
    题意:
        给定N个字符串, 你需要从中有放回地选K个字符串依次拼接起来
        找出你能得到的最小字符串
        范围: N∈[1,1e5], K∈[1,1e5], |S| <= 10
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        本题涉及字符串拼接理论, 我们先从一个经典题目开始思考:
            给定N个字符串, 你需要选择一种顺序将这N个串拼接起来, 使得到的字符串字典序最小
        这个经典问题有个固定的结论: 按照s + t < t + s进行排序
        回到本题, 本题是有放回的选择, 那如果我们不加K的限制, 要求无限拼接, 能得到的最小字符串是什么呢? 
        我们设最小的字符串是T, T是一个无穷字符串
        考虑T的第一个位置选的是S_i, 那么有 T = S_i + ?
        因为T是最小的字符串, 所以 ? 位置仍然要放 T
        因此有 T = S_i + T, 这说明最小的T形如 S_i^∞
        问题的关键在于, 我们如何找到这个S_i呢?
        这需要使用引理: s + t < t + s <==> s^∞ < t^∞
        我们只需要按s + t < t + s进行排序, 排完后的第一个字符串就是我们要找的S_i
        这样我们就找到了无限拼接的策略, 下一步考虑引入K的限制
        我们断言, 在加入限制K后的最优字符串T', 一定是无限情况下的最优字符串T的一个前缀
        使用反证法证明:
        (1)假设T' > T, 那么T' > T > S_min^k, 这与T'是拼接K次后最优的串矛盾
        (2)假设T' < T但T'不是T的前缀, 那么T'^∞ < T, 这与T是拼接无穷次后的最优串矛盾
        因此问题就变成, 我们拼接K次后, 能得到的T'的最短前缀
        我们可以用dp来求解
        dp[i][j] := 拼接i个字符串, 能组成的T[j:]的最短前缀长度
        注: 为什么会有这样的定义方式呢? 我们从记忆化搜索(自顶向下dfs)的角度思考
            我们的问题是求拼接k次后能组成的T[0:]的最短前缀
            因此我们需要遍历N个字符串, 如果S_i可以成为T[0:]的前缀, 我们就需要对"第一步选S_i"进行dfs
            子问题变成了, 拼接k-1次后能组成的T[|S_i|:]的最短前缀
            因此我们自然能得到上面的dp定义方式, 这不是空穴来风的定义
        问题是转移代价太高了, 我们需要枚举K, 枚举T的每个位置, 枚举每个字符串
        由于我们直接把S_min拼接K次后得到的必然是T的前缀, 因此dp[K][0] <= |S_min| * k
        我们对T进行裁剪, 取|T| = |S_min| * K
        因此总时间复杂度为O(N * K^2 * |S_min|), 完全不能接受
        我们注意到一个关键性质, |S| <= 10, 很明显, 对于一个固定长度, 我们只需要保留字典序最小的字符串
        也就是我们可以把枚举N个字符串的工作变成枚举10个字符串
        这样就优化成O(K^2 * |S|^2)
        进一步地, 由于T是个循环串, T的循环节S_min的长度 <= 10, 因此T的本质不同位置也就最多10个
        从而枚举T的每个位置也可以变成枚举|S_min|个位置
        时间复杂度进一步变成O(K * |S|^2)
        代码实现是简单的, 我们可以刷表法或查表法进行转移即可
*/
void solve() {
    int n, k;
    cin >> n >> k;
    vector<string> ss(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> ss[i];
    }
    sort(ss.begin() + 1, ss.end(), [&](auto s, auto t){
        return s + t < t + s;     
    });
    vector<string> a(11);
    for(int i = 1; i <= n; i++) {
        int sz = ss[i].size();
        if(a[sz].empty()) {
            a[sz] = ss[i];
        }
    }
    string T;
    while(T.size() < 20) T += ss[1];
    int len = ss[1].size();
    vector<int> dp(len, 0);
    for(int i = 0; i < k; i++) {
        vector<int> ndp(len, inf);
        for(int j = 0; j < len; j++) {
            if(dp[j] == inf) continue;
            for(int sz = 1; sz <= 10; sz++) {
                if(a[sz].empty()) continue;
                int st = ((j - sz) % len + len) % len;
                if(T.substr(st, sz) == a[sz]) {
                    ndp[st] = min(ndp[st], sz + dp[j]);
                }
            }
        }
        swap(dp, ndp);
    }
    for(int i = 0; i < dp[0]; i++) {
        cout << T[i % len];
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
