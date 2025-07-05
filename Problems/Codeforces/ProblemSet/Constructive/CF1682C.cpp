#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/problemset/problem/1682/C
/*
    贪心 || 构造
    题意:
        给定一个长度为N的数组a, 定义LIS(a)表示a的最长严格递增子序列的长度
        定义a'为a翻转后得到的数组, 定义数组a的权值为min(LIS(a), LIS(a'))
        你可以对数组进行任意重排列, 使得a的权值最大, 输出最大的权值
        范围: n∈[1,2e5], ai∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 前缀和、双指针、二分、数据结构
        由于涉及到最小值最大化, 我们首先思考能否二分答案
        首先把题意进行等价转化, LIS(a') 就等于 LDS(a), LDS是a的最长严格递减子序列长度
        答案具有单调性是显然的, 于是我们思考验证一个答案是否合法的时间复杂度
        我们可以先构造出LIS(a), 让其等于x, 再用剩下的数构造LDS(a), 看能否 >= x
        时间复杂度为O(n), 因此二分答案的时间复杂度为O(nlogn), 可以通过
        但这并不是最优解, 我们进一步利用贡献法思考能否同时构造出最大的LIS和LDS
        由于min函数的特点, 答案最大的时候一定有LIS(a) ≈ LDS(a)
        考虑每个元素对LIS和LDS的贡献
        由于排列顺序任意, 因此对于任意元素x, 它一定可以对LIS或LDS做出1的贡献
        但如果两个相同元素x都放在LIS或LDS中, 只有其中之一是有效的
        因此对于出现了两次及以上的元素, 最优解是在LIS和LDS中各放一个, 贡献为2
        特别地, 对于任意元素, 我们可以把他同时放在LIS和LDS中, 即两个序列的交点
        由于一个单增一个单减, 交点一定只有一个, 因此最优的做法是把这个机会给只出现了一次的元素
        这样我们分两部分统计:
        (1)出现了两次及以上的元素A, 贡献为2, 对ans的贡献为1
        (2)出现了一次的元素B, 贡献为1, 对ans的贡献为1 / 2
        (3)一个交点元素C, 贡献为2, 对ans的贡献为1
        因此答案就是cnt[A] + (cnt[B] - cnt[C]) / 2 + cnt[C]
        其中cnt[C] = min(1, cnt[B])
        因此答案化简为cnt[A] + (cnt[B] + 1) / 2
*/
void solve() { 
    int n;
    cin >> n;
    map<int,int> mp;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(mp[x] < 2) mp[x]++;
    }
    int ans = 0, v = 0;
    for(auto [_, c] : mp) {
        if(c == 2) {
            ans++;
        } else {
            v++;
        }
    }
    ans += (v + 1) / 2; 
    cout << ans << "\n";
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
    
