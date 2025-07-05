#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2108/problem/C
/*
    贪心
    题意:
        有N个按钮排成一排, 每个按钮有一个权值a[i], 有开/关两种状态, 起初都是开的
        你可以按任意顺序执行以下操作:
        op1: 在任意位置召唤一个机器人
        op2: 将一个已有机器人向左或向右移动
        如果机器人的位置与一个开启状态的按钮的位置重叠, 那么该按钮切换到关闭状态
        如果机器人的位置与一个关闭状态的按钮的位置重叠, 那么不会发生任何事情
        你必须保证所有按钮被按下的顺序是单调不增的, 求出最小需要召唤几个机器人
        范围: n∈[1,2e5], a[i]∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 我们很明显有个贪心策略: 
        从大到小依次处理, 如果当前位置在之前添加过的机器人的可达位置中, 那么就不添加
        否则就必须添加一个新的机器人
        注意这里有个细节处理: 如果有多个相同权值的按钮连在一起, 那么要合并成一个,
        否则会受到操作顺序的影响
        进一步思考, 题目本质是在计算去除相邻相同后的数组有多少个极大值
        我们可以把机器人的移动看作下坡的过程, 那么到达一个极大值就相当于上坡
        机器人不能做上坡操作, 因此每个极大值点都必须通过op1实现
        而对于不是极大值点的位置, 必然可以通过下坡来实现, 因此无需召唤机器人
        可以证明, 一定能通过调整顺序构造出合法方案
*/
//jiangly做法: 计算极大值点
void solve1() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a.erase(unique(a.begin() + 1, a.end()), a.end());
    n = a.size() - 1;
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if((i == 1 || a[i] > a[i - 1]) && (i == n || a[i] > a[i + 1])) {
            ans++;
        }
    }
    cout << ans << "\n";
}

//自己的做法: set维护顺序
void solve2() {
    int n;
    cin >> n;
    vector<int> a(n + 1, -1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a.erase(unique(a.begin() + 1, a.end()), a.end());
    n = a.size() - 1;
    vector<int> idx(n + 1);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin() + 1, idx.end(), [&](auto x, auto y){
        return a[x] > a[y];
    });
    int ans = 0;
    set<int> st;
    for(int i = 1; i <= n; i++) {
        if(!st.count(idx[i] - 1) && !st.count(idx[i] + 1)) ans++;
        st.insert(idx[i]);
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve1();
    }
    return 0;
}
