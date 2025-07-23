#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

/*
    数论 || 暴力枚举 || 贪心
    题意:
        给定一个长度为N的数组, 接下来有Q次询问, 每次询问为:
        q: 给定一个整数x, 回答max{a[i]//x + a[i] % x}, i∈[1,N]
        范围: N∈[1,2e5], Q∈[1,2e5], a[i]∈[1,1e6], x∈[1,1e6]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先思考暴力方法, 对于每个查询x, 枚举数组所有元素, 计算a[i]//x + a[i]%x
        时间复杂度为O(q*n)
        考虑对于固定的x, 按a[i] // x的值进行分块
        在每个块内, a[i]//x的值都相同, 此时肯定是选块内最后一个元素能获得最大的a[i]%x
        这样我们就把求解一个x的时间复杂度降为O(V/x), V为值域最大值
        对于Q个查询, 如果有相同查询显然可以记忆化之前的结果, 当查询都不同时
        最坏情况为O(V/1 + V/2 + ... + V/2e5) = O(VlogQ), 可以通过题目
        那么如何知道一个块内的最后一个元素呢?
        可以用pre数组来预处理即可
        pre[i] := 最后一个小于等于i的元素值
*/
const int N = 1000000;
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> pre(N + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        pre[x] = 1;
    }
    for(int i = 1; i <= N; i++) {
        if(pre[i]) {
            pre[i] = i;
        } else {
            pre[i] = pre[i - 1];
        }
    }
    vector<int> vis(N + 1, -1);
    while(q--) {
        int x;
        cin >> x;
        if(vis[x] != -1) {
            cout << vis[x] << "\n";
            continue;
        }
        int ans = 0;
        for(int i = x - 1, c = 0; i <= N; i += x, c++) {
            int p = pre[i];
            if(p <= i - x) continue;
            ans = max(ans, c + p % x);
        }
        vis[x] = ans;
        cout << ans << "\n";
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
