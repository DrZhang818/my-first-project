#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc143/tasks/abc143_f
/*
    构造 || 数学
    题意:
        给定一个长度为N的数组, 给定整数K, 你可以进行以下操作:
        op: 选择恰好K个不同元素并从数组中删除
        对于K = 1,2,...,N, 分别回答能够进行的最大操作次数
        范围: N∈[1,3e5], a[i]∈[1,N]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        由于值域不大, 且操作与值有关, 因此考虑把问题进行转化:
        求出数组a的cnt数组, cnt[i] = i在a中的出现次数
        操作变成: 在cnt数组中选择k个正数, 并将所有数减一
        对于决策类题目, 我们考虑把题目分解为 局面 + 问题
        局面: 当前的cnt数组
        问题: 能够进行的最大操作次数
        接下来, 我们不妨头脑风暴一下, 挖掘出尽可能多的问题中隐含的性质
        (1)单调性: 能够进行x次操作, 就一定能进行x-1次操作
        (2)答案范围为[0,N/K]
        (3)单调性: 随着K的增大, 能够进行的最大操作次数单调递减
        下面考虑解决问题的方式, 由于出现了单调性, 因此我们优先思考二分答案是否成立
        问题变成: 给定k时, 如何检查cnt数组能否进行至少x次操作
        长为k的x次操作, 意味着cnt数组必须提供减掉x * k的机会
        考虑每个数i∈[1,N], cnt[i] = c
        那么i能参与min(c,x)个操作当中
        因此必要条件为: ∑min(cnt[i], x) >= x * k
        那么该条件是否是充分条件呢?
            是, 我们给出构造性证明:
            每次选择cnt数组的前k大作为一次操作
            进行了t次操作后, 最大元素 <= x - t
            我们只需要证明第k大 > 0即可
            假设第k大 = 0, 则操作无法继续进行, 此时sum <= (k-1)*(x-t)
            前面进行了t次操作, 减掉的sum为k * t
            则起始sum <= k*t + (k-1)*x - (k-1)*t
                      = (k-1)*x + t
            由于t∈[0,x-1]
            则sum <= (k-1)*x + x-1 = x * k - 1
            这与sum >= x * k矛盾
        因此, 问题的充要条件为∑min(cnt[i], x) >= x * k
        到这里基本就解决问题了, 下面考虑如何快速计算∑min(cnt[i],x)即可
        把问题拆为∑cnt[i] + ∑x, 分别套上条件, 转化为前缀和与后缀和即可
        由(1)(3), x与k都有单调性, 我们用双指针维护即可           
*/
void solve() {
    int n;
    cin >> n;
    vector<int> cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    vector<ll> c1(n + 1), c2(n + 2);
    for(int i = 1; i <= n; i++) {
        c1[cnt[i]] += cnt[i];
        c2[cnt[i]] += 1;
    }
    for(int i = 1; i <= n; i++) {
        c1[i] += c1[i - 1];
    }
    for(int i = n; i >= 1; i--) {
        c2[i] += c2[i + 1];
    }
    for(int i = 1, x = n; i <= n; i++) {
        while(x && c1[x] + x * c2[x + 1] < 1LL * x * i) x--;
        cout << x << "\n";
    }
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
