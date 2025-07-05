#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc407/tasks/abc407_e
/*
    反悔贪心
    题意:
        给定一个长度为2N的数组, 定义一个长度为2N的合法括号序列S的得分为:
        f(S) := 所有'('位置对应的数组元素的总和
        你需要在所有长为2N的合法括号序列S中找到最大的得分f(S)
        范围: N∈[1,2e5], a[i]∈[0,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 对于合法括号序列问题, 很经典的方式是从区间DP的角度进行思考
        但我们很快发现, 区间DP的复杂度是O(N^3)的, 明显是错误的思路
        这启发我们必然要通过贪心来解决题目了
        我们考虑从0逐步生成长为2N的括号序列, 每步添加一个左括号和右括号, 并保证添加后
        得到的仍然是一个合法括号序列
        首先, 由于前面生成的已经是合法的了, 因此当前加入的()与之前的并列一定是合法的
        其次, 考虑嵌套情况, 把之前的一个右括号与当前的左括号互换位置, 得到的也一定是合法的
        这样我们能得到的最大权值是max{之前的')', 当前的'('}, 这可以用堆来维护
        这样贪心的正确性是显然的, 我们每步得到的都是当前步结束后的最优解, 那么第N步得到的
        自然是第N步结束后的最优解
*/
void solve() {
    int n;
    cin >> n;
    n <<= 1;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll ans = a[1], cur = 0;
    priority_queue<int> q;
    q.push(a[2]);
    for(int i = 3; i <= n; i += 2) {
        int u = q.top(); q.pop();
        ans += max(u, a[i]);
        q.push(min(u, a[i]));
        q.push(a[i + 1]);
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
        solve();
    }
    return 0;
}
