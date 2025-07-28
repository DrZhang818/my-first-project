#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2128/problem/A
/*
    贪心
    题意:
        给定一个长度为N的数组和一个整数c, 你需要执行以下操作, 直至数组为空
        op: 移除a[i], 数组剩余元素 × 2, 如果a[i] > c代价为1, a[i] <= c代价为0
        求使得数组变为空数组所需的最小代价
        范围: N∈[1,30], c∈[1,1e9], a[i]∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        观察题目性质, 我们很快得到:
        (1)如果a[i]已经大于c, 那么无论什么时候删除的代价都是1, 因此优先级最低
        (2)如果a[i] <= c, 贪心地想, 我们应该清除符合此条件的最大的a[i], 因为这个元素最有潜力让代价
            从0变为1
        因此, 我们只需把数组排序后, 从大到小进行贪心即可
*/
void solve() {
    int n, c;
    cin >> n >> c;
    vector<int> a(n + 1);
    ll cur = 1;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    int ans = 0;
    for(int i = n; i >= 1; i--) {
        if(a[i] * cur > c) {
            ans++;
        } else {
            cur <<= 1;
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
