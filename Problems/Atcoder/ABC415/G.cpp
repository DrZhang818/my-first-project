#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc415/tasks/abc415_g
/*
    贪心 || DP || 抽屉原理
    题意:
        共有M家商店, 起初你有N瓶可乐, 0个空瓶, 你可以进行任意次以下操作:
        op1: 喝掉1瓶可乐, 持有的可乐数量-1, 空瓶数量+1
        op2: 选择一家商店, 向商店交出a[i]个空瓶, 换取b[i]瓶可乐、
        每一时刻必须保证持有的可乐和空瓶数量为非负整数
        请你求出最多能喝多少瓶可乐
        范围: N∈[1,1e15], M∈[1,2e5], 1 <= b[i] < a[i] <= 300
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        本题是D题的Hard版本, 我们发现与D题的区别是, 收益不再是固定的了
        对于每家商店, 我们的价格是a[i] - b[i], 得到的收益是b[i]
        因此性价比是b[i] / (a[i] - b[i])
        按照性价比进行排序, b[i] / (a[i] - b[i]) > b[j] / (a[j] - b[j])
        化简后, 本质是按照b[i] / a[i]做排序, 我们能够找到最大的一个b[i] / a[i]的物品
        那么是否贪心地选这个物品就对了呢?
        观察以下样例:
        手中有9个可乐, 第一家商店a[1] = 9, b[1] = 5, 第二家商店a[2] = 6, b[2] = 3
        如果按照b[i]/a[i]选, 我们只能选一次第一家, 喝掉9 + 5 = 14个可乐
        但我们事实上可以选两次第二家, 喝掉9 + 3 + 3 = 15个可乐
        这说明, 在手里空瓶数比较少的时候, 较差的解有潜力晋升为最优解
        但我们感性地理解, 当手里空瓶数非常多的时候, 就失去了"买不起"的瓶颈, 这时候贪心应该是对的
        那么这个多与少的边界是多少呢?
        我们设性价比最大的物品的a[i] = x
        根据抽屉原理, 长度 >= x的正整数数组必然存在某个子段和是x的倍数
        那我们把这一段全部替换成x显然能得到更优的解
        本题a[i]最大是300, 也就是说选的物品 >= 300的时候必然有某段可以被性价比最高的物品代替
        因此分界线是300 * 300 = 90000, 当空瓶数 >= 90000时, 贪心一定是正确的
        做完这一部分的贪心后, 我们手中有 < 90000的瓶子, 该如何求解这部分的最优解呢?
        此时N不大, 我们可以直接做完全背包
        dp[i][j] := 考虑前i家商店, 手中有j个瓶子能得到的最多可乐数量
        对于第i家商店:
        dp[i][j] = max(dp[i - 1][j], dp[i][j - a[i] + b[i]] + b[i])
        答案为dp[M][N]
*/
const int N = 90005;
void solve() {
    ll n;
    int m;
    cin >> n >> m;
    vector<int> w(301);
    for(int i = 1; i <= m; i++) {
        int A, B;
        cin >> A >> B;
        w[A] = max(w[A], B);
    }
    int a = 1, b = 0;
    for(int i = 1; i <= 300; i++) {
        int x = i, y = w[i];
        if(y * a > x * b) {
            a = x;
            b = y;
        }
    }
    ll ans = n;
    if(n > N + a) {
        ll t = (n - N - a) / (a - b) + 1;
        ans += t * b;
        n -= t * (a - b);
    }
    vector<ll> dp(n + 1);
    for(int i = 1; i <= 300; i++) {
        for(int j = i; j <= n; j++) {
            dp[j] = max(dp[j], dp[j - i + w[i]] + w[i]);
        }
    }
    cout << ans + dp[n] << "\n";
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
