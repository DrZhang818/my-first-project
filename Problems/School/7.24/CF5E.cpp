#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/5/problem/E
/*
    DP || 单调栈
    题意:
        有一个N个点的环, 第i个点权值为a[i]
        环上任意两点(i,j)存在两条路径: i顺时针到j, j顺时针到i
        定义两个不同的点(i,j)是连通的, 当且仅当i到j的两条路径中至少存在一条路径, 满足路径上的
        所有点(除i,j外)的权值都不超过a[i]和a[j]
        请你求出有多少个连通的点对
        范围: N∈[3,1e6], a[i]∈[1,1e9]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        对于环形问题, 我们先考虑非环形的情况如何做
        此时问题变为: 求有多少个i,j, ∀k∈(i,j), a[k] <= min(a[i], a[j])
        我们发现, 问题本质上是有多少对(i,j)能互相看到彼此
        这种"可见性"问题与单调栈非常契合
        我们考虑用单调栈 + dp来做
        我们可以维护一个严格单调递减栈, 这样在栈中的元素都是可以向右看的元素, 被弹出的元素都是
        无法向右看的元素
        这样的好处是, 接下来只需要考虑遍历到的元素向左看能看到谁, 向右看已经被满足了
        定义dp[i] := 以i为结尾, 连续等于a[i]的块长度
        (1)如果a[i] > 栈顶元素
            此时a[i]能看到栈顶元素的整个块
            因此贡献dp[stk.top]
            之后stk.top不能再与后续元素连通, 因为中间被a[i]隔断
        (2)如果a[i] < 栈顶元素
            此时a[i]只能看到栈顶元素的块的最后一个元素
            答案贡献为1
            a[i]入栈, stk.top无需弹栈
        (3)如果a[i] = 栈顶元素
            那么a[i]可以和已形成的块中的点连通
            如果栈顶元素形成的连续块的前面还有元素, 那么a[i]还可以与这个元素连通
            答案贡献dp[stk.top] + (stk.size > 1)
            此时dp[stk.top] += 1
            a[i]无需入栈
        如果带环的话该如何做呢?
        带环之后, 就有了循环移位的性质
        我们可以利用这一特性, 把最大值移动到开头
        这样方便我们统计反向连通的情况
        我们思考下, 哪些情况的计数被我们漏掉了
        例如5 5 3 3 1 1这种情况:
        1.最后两个1与第一个5连通, 但我们目前认为被3阻隔
        2.中间的两个3与第一个5连通, 但我们目前认为被第二个5阻隔
        当我们钦定第一个值为最大值时, 我们漏掉的就只有这一种情况:
        在栈中的元素向右走, 穿越到数组开头与最大值连通的情况
        为什么不在栈中的元素就不会与最大值连通呢? 因为被右侧元素阻隔, 无法穿越到数组开头
        此时要特判次大元素, 即栈中的第二个元素
        在(2)种, 我们已经认为这些元素与最大值连通, 如果最大值这个块只有一个元素, 那么就不用再计数了
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int id = 1;
    for(int i = 1; i <= n; i++) {
        if(a[i] > a[id]) {
            id = i;
        }
    }
    vector<int> b(n + 1);
    for(int i = 1; i <= n; i++) {
        b[i] = a[id++];
        if(id > n) id = 1;
    }
    swap(a, b);
    ll ans = 0;
    vector<int> stk(n);
    stk[0] = 1;
    int top = 1;
    vector<ll> dp(n + 1);
    dp[1] = 1;
    for(int i = 2; i <= n; i++) {
        while(a[i] > a[stk[top]]) {
            ans += dp[stk[top]];
            top--;
        }
        if(a[i] < a[stk[top]]) {
            ans++;
            dp[i] = 1;
            stk[++top] = i;
        } else {
            ans += dp[stk[top]];
            dp[stk[top]]++;
            if(top >= 1) {
                ans++;
            }
        }
    }
    if(top >= 1 && dp[stk[0]] > 1) {
        ans += dp[stk[1]];
    }
    for(int i = 2; i <= top; i++) {
        ans += dp[stk[i]];
    }
    cout << ans << "\n";
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
