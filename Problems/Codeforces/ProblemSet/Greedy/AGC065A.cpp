#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

//https://atcoder.jp/contests/agc065/tasks/agc065_a
/*
    贪心 || 构造
    题意:
        给定一个长度为N的数组和一个整数K, 你可以任意重排数组, 数组的得分为 ∑ ((a[i + 1] - a[i]) mod K) 
        求出你能得到的最大得分
        范围: N∈[2,2e5], K∈[1,1e9], a[i]∈[0,K - 1]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心||网络流, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 决策函数是一个复杂的求和式, 我们可以将其变形为:
            a[N] - a[1] + x * K, x是满足 a[i + 1] < a[i] 的 i 的个数
        我们设 x 能取到的最大值为 mx
        由于 a[N] - a[1] ∈ [-2K + 2, 2K - 2]
        因此 x 只可能取 {mx, mx - 1}, 若 x 取 <= mx - 2的值, 答案一定不优
        我们思考如何求出mx
        让我们先从简单情况入手, 假设数组中值是唯一的
        那么显然, 我们把数组按从大到小顺序排, 得到的必然是最大值 mx = N - 1
        如果有重复值呢? 我们设最大出现次数为 m
        不难发现, 此时有 mx <= N - m, 那么是否能够取等呢?
        考虑这种构造方式:
            把a分割成m段非空子数组b1,b2,...,bm, 要求每个子数组元素唯一 且 按降序排列
            显然, 由于每个数出现此时 <= m, 因此一定能够分配到这m个子数组中
            每个长度为L的子数组会贡献 L - 1
            mx = ∑ (L[i] - 1) = N - m 
        下面分别按照 x = mx 和 x = mx - 1进行讨论
        我们把所有出现m次的元素收集到数组v, 并把v按从小到大排序
        (1)x = mx:
            此时我们要最大化 a[N] - a[1], 等价于最大化 min(bm) - max(b1)
            由于v中元素必然出现在每个bi当中
            因此min(bm) <= min(v), max(b1) >= max(v)
            显然, 二者都取等时, min(bm) - max(b1)最大
            考虑以下构造:
                对于不在v中的元素
                把每个 >= max(v)的放到b2 ~ bm
                把每个 <  min(v)的放到b1 ~ bm-1
                由于这些元素出现次数 < m, 因此一定能放的下
            这样, min(bm) - max(b1) 的最大值就是 min(v) - max(v)
        (2)x = mx - 1:
            我们把a分割成m + 1非空子数组b1,b2,...,bm+1, 要求每个子数组元素唯一 且 按降序排列
            此时我们要最大化 a[N] - a[1], 等价于最大化 min(bm+1) - max(b1)
            由于v中每个元素出现m次, 因此要么在b1中出现, 要么在bm+1中出现, 要么都出现
            贪心地想, 我们一定是把一部分小的放到b1, 把剩下较大的部分放到bm+1
            换句话说, 最大值是max(v[i + 1] - v[i])
            思考其他出现次数 < m的元素如何放置?
            显然, 这些元素放在b1或bm+1只可能导致答案变劣, 因此把这些元素全部放到 b2 ~ bm中
        答案是两种情况的max
*/
void chmax(int &x, int y) {
    if(x < y) {
        x = y;
    }
}
void solve() {
    int n, k;
    cin >> n >> k;
    map<int,int> cnt;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    vector<PII> a(cnt.begin(), cnt.end());
    int mx = 0;
    for(auto [x, c] : a) {
        chmax(mx, c);
    }
    vector<int> val;
    for(auto [x, c] : a) {
        if(c == mx) {
            val.push_back(x);
        }
    }
    ll ans = val[0] - val.back() + 1LL * (n - mx) * k;
    for(int i = 1; i < val.size(); i++) {
        ans = max(ans, val[i] - val[i - 1] + 1LL * (n - mx - 1) * k);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
