#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc407/tasks/abc407_a
/*
    数学
    题意:
        给定两个数字, 输出距离实数a/b最近的整数(b为奇数)
        范围: a,b∈[1,407], b为奇数
    关键思考:
        本题为模拟类题目, 需要读请题目, 选用合适的算法和数据结构维护题目信息, 回答询问
        首先观察题目性质, 由于b是奇数, 因此最终答案一定是唯一的
        我们需要处理浮点数掉精度的问题
        观察题目性质, 我们可以把a/b写为c + a%b/b的形式
        如果a%b/b < 0.5答案就是c, 如果大于0.5答案就是c+1
        处理这样的分数问题, 常用手段就是交叉相乘
        把问题转化为2(a%b) - b 与 0 的关系就可以在不出现浮点数的情况下解决问题
*/
void solve() {
    int a, b;
    cin >> a >> b;
    int c = a / b;
    a %= b;
    if(2 * a > b) c += 1;
    cout << c << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
