#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

//https://codeforces.com/problemset/problem/1684/D
/*
    贪心
    题意:
        有N个陷阱, 你需要按顺序通过它们, 第i个陷阱造成a[i]点伤害, 你有k次跳过陷阱的机会:
        op: 跳过第i个陷阱, 免受a[i]点伤害, 但后续的[i+1,n]陷阱的a[i]都将增加1
        请你最小化受到的伤害
        范围: N∈[1,2e5], k∈[1,n], a[i]∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        很明显, 我们有个dp的思路, f(i,j) := 考虑前i个陷阱, 跳过j个陷阱的最小伤害
        但是这样的时间复杂度是O(nk), 超时
        考虑二分能否优化? 我们发现二分的check函数仍需要O(nk), 因为必须知道前面跳过了多少个陷阱
        那么我们只能往贪心上想了, 首先有个不难想到的性质:
        (1)我们一定会跳过恰好k次陷阱
            假设跳过的次数 < k, 那么我们把末尾的未被选择的陷阱跳过, 必然能减小受到的伤害
            因为选这些陷阱没有对后续的减益效果, 有这一点就足以证明选k次比选小于k次是更优的
        我们把选第i个陷阱带来的减益效果算在自己身上, 这样就方便我们推导式子
        考虑第i个陷阱:
        (1)不跳过, 那么带来的伤害为 a[i]
        (2)跳过, 那么带来的伤害为 n - i + (i+1 ~ n中跳过的陷阱数量)
        那么总伤害为 ∑a[i]<不跳过i> + ∑(n - i + cnt[i+1~n])<跳过i>
        这就是我们的决策函数, 我们要最小化这个函数的值
        然后我们惊奇地发现, 由于证明了一定会跳过k个陷阱, 那么∑cnt[i+1,n]<跳过i>是一个常数!
        因为对于第一个跳过的陷阱, 后面跳过k-1个, 对于第二个跳过的陷阱, 后面有k-2个, ...
        那么这一项的权值就等于 ∑i (i∈[0,k-1])
        扔掉常数后, 决策函数就变得非常简单了
        ∑a[i]<不跳过i> + ∑(n - i)<跳过i>
        那么只需要贪心地按照a[i] - (n - i)的值从大到小排序即可
*/
struct info {
    int v, cnt;
    friend bool operator < (const info &a, const info &b) {
        return a.v - a.cnt > b.v - b.cnt;
    }
};
void solve() {
    int n, k;
    cin >> n >> k;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].v;
        a[i].cnt = n - i;
    }
    sort(a.begin() + 1, a.end());
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        if(i <= k) ans += a[i].cnt;
        else ans += a[i].v;
    }
    ans -= 1LL * k * (k - 1) / 2;
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
