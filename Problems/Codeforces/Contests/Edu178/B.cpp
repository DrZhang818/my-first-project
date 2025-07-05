#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2104/problem/B
/*
    贪心
    题意:
        给定一个长度为N的数组, 对于i∈[1,N], 你必须执行以下操作:
        1.从数组中任意选择一个元素, 并将其移动到最后
        2.输出后i个元素的和
        3.恢复原状
        对于每个i∈[1,N], 你必须最大化后i个元素和
        范围: n∈[1,2e5], a[i]∈[1,1e9]
    关键思考:
        本题属于决策||数据结构类题目, 常用选用合适的算法和数据结构维护题目信息, 回答询问
        首先分析题目性质, 我们有n次查询, 说明每次查询要做到O(logn)以下的级别
        考虑单次查询, 每次查询都有N种状态(把第1,2,...,n个移动到最后), 状态量太大
        此时我们有两种优化手段, 第一种是找到合适的等价关系对状态进行划分, 第二种是
        找到贪心策略, 两种方法的目的都是为了避免逐个访问状态
        通过分析不难发现贪心策略是可行的, 因为如果我们要让后i个数最大, 由于只能操作一次
        那么后i-1个数是必然参与运算的, 此时问题就变成了查找a[1:n-i+1]中的最大值
        这样问题就变得非常清晰了, 我们只需要预处理后缀和, 然后从左到右遍历的同时维护
        前缀max即可
*/
void solve() {
    int n, k;
    cin >> n;
    vector<ll> a(n + 1), suf(n + 2);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = n; i >= 1; i--) {
        suf[i] = suf[i + 1] + a[i];
    }
    ll mx = 0;
    vector<ll> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        mx = max(mx, a[i]);
        ans[n - i + 1] = suf[i + 1] + mx;
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
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
