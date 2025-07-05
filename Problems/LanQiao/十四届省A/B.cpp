#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.lanqiao.cn/problems/3497/learning/
/*
    搜索
    题意:
        共有30个题目, 有以下规则:
        (1)每题只有正确和错误两种情况, 答对一题后加10分, 答错一题后分数重置为0
        (2)分数到达100后停止答题
        (3)可以在任意时刻结束答题并获得当前分数对应的奖项
        已知小蓝最终实际获得了70分对应的奖项, 请问小蓝所有可能的答题情况有多少种
        两种答题情况被认为是不同的, 当且仅当答题数量不同或存在某一题的正误不同
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        由于是填空题, 我们想办法设计出爆搜即可
        定义dfs(i,j) := 已经答完了i个题, 当前分数为j
        如果j = 7, 按照题意, 可以立即停止答题, 因此答案 + 1
        如果j = 10或i = 30, 按照题意, 将强制停止答题
        接着按照题目逻辑, 分两条路径搜索"答对"和"答错"的情况即可        
        时间复杂度为O(2^30)
*/
ll ans = 0;
void dfs(int cnt, int sum) {
    if(sum == 7) ans++;
    if(sum == 10 || cnt == 30) return;
    dfs(cnt + 1, sum + 1);
    dfs(cnt + 1, 0);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    dfs(0, 0);
    cout << ans << "\n";
    return 0;
}
    
