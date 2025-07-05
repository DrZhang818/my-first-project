#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/1396/problem/B
/*
    构造 || 贪心 || 博弈论 || 二分图
    题意:
        Alice和Bob在玩石子游戏, 一共有n堆石子, 起初第i堆有a[i]个石子
        Alice和Bob轮流进行以下操作:
        op: 选择一个非空的, 且不是上轮被选中的石子堆, 从中拿走一个石子
        如果当前轮无法进行任何合法操作, 则判负
        Alice先手, 二人都以最优策略进行, 问谁能获胜?
        范围: n∈[1,100], a[i]∈[1,100]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先分析题目性质:
            B获胜 <==> 无论A第一步走什么, B都有必胜策略
            A获胜 <==> 存在第i堆石子, A第一步选这堆后, 无论B走什么, A都有必胜策略
        这是博弈论的经典转化, 分析第一步至关重要, 因为每一轮都可以看做第一轮, 具有递归性质
        关键观察: 选择可选的石头最多的石子堆是最优的
        证明:
            假设选择的不是石头最多的石子堆, 记数量为a, 最多的石子堆石子数量为b, a < b
            我们要证明选择b得到的结果一定是不劣的
            为了量化决策收益, 我们引入两个决策参数, 并把当前"占领"的石子堆的石子数记为hp:
            (1)剩余非空石子堆数量   (2)hp
            显然, 无论选a还是选b, 对于下一轮的对手来说, 参数(1)是相同的
            而对我们来说, 选a得到的hp < 选b得到的hp
            对下一轮的对手来说, 我们选a后, 对手下一轮的可能hp >= 我们选b时对手的可能hp
            显然hp越大, 越有利于获胜, 故选b是不劣的
        有了这一点后, 题目就非常简单了
        (1)Alice第一步选择最大的mx, 如果mx足够大, 超过了其余石子数的总和
        这时候Alice一定获胜了, 因为第tot - mx轮后对手就无法操作了
        (2)mx没有超过tot-mx, 此时二人轮流选可用的最大值, 过程中的mx'始终不能超过tot'-mx'
           那么游戏就会进行到最后一个石子才能分出胜负, 这与tot的奇偶性有关

        另一种简洁证明:
            当mx  <= tot - mx时, 每堆石子数量都 <= tot / 2
            (1)若tot为偶数我们可以把石子进行编号1~tot, 记mid = tot / 2
            将1~mid的每个石子i与i + mid进行匹配, 这两个棋子一定在不同堆中
            这样选手1选择某个石子后, 选手2可以选择与其匹配的石子
            因此游戏会进行到最后一轮, 后手获胜
            (2)若tot为奇数, Alice任意选择一个石子后, 转化为情况(1), 此时Alice获胜
            当mx > tot - mx时, 此时Alice持续选mx就可以获胜
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int tot = 0, mx = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        tot += a[i];
        mx = max(mx, a[i]);
    }
    if(tot % 2 == 0 && 2 * mx <= tot) {
        cout << "HL\n";
    } else {
        cout << "T\n";
    }
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
