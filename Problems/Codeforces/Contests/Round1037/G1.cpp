#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2126/problem/G1
/*
    暴力枚举 || 中位数Trick
    题意:
        给定一个长度为N的数组, 你需要从中选取一段子数组a[l:r], 
        使得med(a[l:r]) - min(a[l:r])最大
        med(a[l:r])表示a[l:r]的中位数, 即第(k+1)/2大元素(上取整)
        输出能得到的最大值
        范围: N∈[1,2e5], a[i]∈[1,min(n,100)]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        由于a[i]的范围非常小, 因此我们考虑暴力枚举
        枚举有两种方式, 枚举med或者枚举min
        由于med比min更难维护, 因此考虑枚举med维护min
        设当前枚举的med为x
        对于每个a[i], 我们要考虑如何判定: 能否有一个包含a[i]的子数组, 使得x为中位数
        这是经典的中位数判定问题, 可以采用以下Trick:
        我们构建一个数组b, 如果a[i]>=x, 则b[i] = 1, 否则b[i] = -1
        对b做前缀和, 得到前缀和数组S
        那么∃包含a[i]的, 以x为中位数的子数组, 等价于max(S[i:n])-min(S[0:i-1])>=0
        因此预处理一下后缀max和前缀min即可O(1)判定
        那么有了med, 如何维护min呢
        很简单, 我们可以直接钦定a[i]为min
        因为假设包含a[i]的,以x为中位数的子数组不是以a[i]为最小值
        那么设这个最小值的下标为j
        那么我们在遍历a[j]的时候, 同样会识别到这个子数组, 而那时就自然得到了真正的min
        且由于x - a[i] <= x - a[j], 我们不会得到超过最优解的答案, 算法正确
        因此我们甚至不用管min, 只需要枚举med并且计算x - a[i]即可
        注意: 我们所说的枚举med实际上是中位数 >= med, 我们是从小到大逐步逼近到最优解时的
              中位数, 过程中的med不一定真的能取到, 但保证最优解一定能取到
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int ans = -inf;
    for(int x = 1; x <= 100; x++) {
        vector<int> b(n + 1);
        for(int i = 1; i <= n; i++) {
            b[i] = a[i] >= x ? 1 : -1;
        }
        vector<int> pre(n + 1), premn(n + 1), sufmx(n + 1);
        for(int i = 1; i <= n; i++) {
            pre[i] = pre[i - 1] + b[i];
        }
        sufmx[n] = pre[n];
        for(int i = 1; i <= n; i++) {
            premn[i] = min(premn[i - 1], pre[i]);
        }
        for(int i = n - 1; i >= 1; i--) {
            sufmx[i] = max(sufmx[i + 1], pre[i]);
        }
        for(int i = 1; i <= n; i++) {
            if(sufmx[i] >= premn[i - 1]) {
                ans = max(ans, x - a[i]);
            }
        }
    }
    cout << ans << "\n";
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
