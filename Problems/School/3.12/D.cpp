#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.luogu.com.cn/problem/AT_arc085_b
/*
    贪心 || 博弈论
    题意:
        Alice和Bob在玩一种卡牌游戏, Alice起初有一张数值为Z的牌, Bob有一张数值为W的牌
        给定N张牌, 从上到下第i张牌的数值为ai
        游戏规则如下: 每回合从牌堆摸至少一张牌, 除最后一张牌之外全部弃掉
        定义游戏的得分为: 牌堆无牌后, 二人手牌上的数值的绝对差
        Alice的策略是让得分最大, Bob的策略是让得分最小
        问Alice先手的情况下, 最终得分是多少?
        范围: N∈[1,2000], Z,W,ai∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->贪心||DP, 常用优化手段为: 二分、双指针、数据结构
        首先发现本题是特殊的博弈论, 二人的游戏目标恰好相反
        那么由于Alice先手, 朴素想法是枚举Alice第一步的选法, 并从中取最大值
        我们记Alice第一步选的区间右端点为r
        从简单情况到复杂情况来分析
        (1)当r=n时情况最简单, Alice一口气选走所有牌, 得到的得分为abs(a[n] - w)
        (2)当r=n-1时, Bob只有唯一一张可选, 得到的得分为abs(a[n] - a[n - 1])
        (3)当r<=n-2时, 得分一定 <= 情况(2)的得分
            因为Bob可以通过选择区间[r+1, n-1], 得到得分abs(a[n] - a[n - 1])
            而Bob按照他的策略选取, 得到的得分一定 ≤ abs(a[n] - a[n - 1])
        因此, 最终得分为max( abs(a[n] - w), abs(a[n] - a[n - 1]) )
*/
constexpr int inf = 1000000000;
void solve() { 
    int n, z, w;
    cin >> n >> z >> w;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll ans = abs(w - a[n]);
    if(n > 1) ans = max(ans, (ll)abs(a[n - 1] - a[n]));
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
