#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

//https://ac.nowcoder.com/acm/contest/97666/H
/*
    贪心 + DP
    本题可能会与416题搞混
    力扣416分割等和子集，也就是在数字间加入"+" 或 "-"组成表达式，转化为0-1背包问题
    因此本题第一个想法也是值域DP, 即"值域i是否可达"从"值域[1, i - 1]是否可达"转移出来
    然而, 这样每次状态转移都是O(n)的时间, 会TLE, 因此需要考虑贪心优化
    关键观察: 
            表达式计算完乘法后, 转化成了{1, 0, -1}三个数之间的加法
            假设此时值为x(不妨设x >= 1, 因为小于1没有转化的意义)
            1 + 1 + 0 + (-1) + ... = x
            可以发现, 当我们把(0, 1)或者(1, 1)的组合之间的"+"改成"*"的时候, 值变为了x-1
            进一步考虑极端情况, 假设x = 2
            1 + (-1) + 1 + (-1) + ... + 1 + (-1) + 1 <--这时候x = 1
            根据鸽笼原理, 下一次出现的1必然与其中一个1相邻, 因此x = 2时x = 1可达
            因此对于x >= 1, 我们只需要维护最大值, 小于等于最大值的询问都是可达的
    问题转化成最大化表达式的值
        dp[i] := 前i个数组成的最大值
        初始条件: dp[0] = 0
        状态转移:
                1.当nums[i - 1] = 1时, dp[i] = dp[i - 1] + 1
                2.当nums[i - 1] = 0时
                        (1)若nums[i - 1] = -1 且 nums[i - 2] != -1 
                                则dp[i] = dp[i - 2]
                        (2)其他情况都是dp[i] = dp[i - 1]
                3.当nums[i - 1] = -1时
                        (1)若nums[i - 1] = 0
                                则dp[i] = dp[i - 2];
                        (2)其他情况就要找最近的nums[idx] = -1, 让这一段做乘法
                                极限情况是前面为-1 1 1, 则此时的-1可以与这三个凑一对
                                变为1
                            因此dp[i] = dp[idx - 1]
    
*/
void solve(){
    int n, q;
    cin >> n >> q;
    vector<int> nums(n);
    for(auto& num : nums){
        cin >> num;
    }
    vector<int> dp(n + 1, -1);
    dp[0] = 0;
    for(int i = 1; i <= n; i++){
        int sum = 1;
        for(int j = 1; j <= min(i, 4); j++){
            sum *= nums[i - j];
            dp[i] = max(dp[i], dp[i - j] + sum);
        }
    }
    for(int i = 0; i < q; i++){
        int x; 
        cin >> x;
        cout << (x <= dp[n] ? "Yes\n" : "No\n") ;
    }
}

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}