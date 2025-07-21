#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2122/problem/C
/*
    构造 || 贪心
    题意:
        给定二维平面上的N个点(x,y), N为偶数, 你需要把这N个点划分成N/2个二元点对, 每个点对
        的距离定义为两点间的曼哈顿距离, 请你最大化所有点对的距离之和
        输出任意一种合法的划分方案
        范围: N∈[2,2e5], x,y∈[-1e6,1e6]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        赛时盲目地把曼哈顿距离转为切比雪夫距离进行思考, 事实上, 曼哈顿距离天然适合应对
        求和形式, 而切比雪夫距离适合求"找出两个距离最大的点"
        我们要最大化的是:
            ∑(|xi-xj| + |yi-yj|)
        运用经典绝对值trick, 把一个点(x,y)拆成四种状态:
        (x,y), (x,-y), (-x,y), (-x,-y)
        用二进制表示状态, 即
        11,10,01,00
        则11只能与00匹配, 10只能与01匹配
        我们进一步发现, x和y是完全独立的两个维度, 本质上我们是在做:  
            把n/2个点的x取相反数
            把n/2个点的y取相反数
            取相反数的这些数字必须满足: 有一个更大的数字与他匹配, 这样他才能表现为相反数
            然后全部累加起来
        那么我们贪心的想, 把x轴上较小的n/2个点标记为0, 把y轴上较小的n/2个点标记为0
        最终就能得到每个点在两个维度上的状态, 按照规则进行匹配即可
        代码实现采用tourist的写法
        先按x进行排列, 然后把数组分成两部分, 分别按y进行排序
        这样数组的四段就依次为:
        00 01 10 11
        这样直接就能得到匹配方案了, 即p[i]与p[n-i+1]进行匹配
*/
void solve() {
    int n;
    cin >> n;
    vector<int> x(n + 1), y(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    sort(p.begin() + 1, p.end(), [&](auto i, auto j){
        return x[i] < x[j];
    });
    sort(p.begin() + 1, p.begin() + n / 2 + 1, [&](auto i, auto j){
        return y[i] < y[j];
    });
    sort(p.begin() + n / 2 + 1, p.end(), [&](auto i, auto j){
        return y[i] < y[j];
    });
    for(int i = 1; i <= n / 2; i++) {
        cout << p[i] << " " << p[n - i + 1] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
