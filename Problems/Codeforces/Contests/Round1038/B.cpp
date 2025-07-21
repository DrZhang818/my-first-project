#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2122/problem/B
/*
    构造 || 贪心
    题意:
        给定N个二进制堆, 第i个堆顶部有ai个0, 底部有bi个1, 其目标状态为顶部有ci个0, 底部有di个1
        你可以进行以下操作:
        op: 取出任意一个堆的顶部元素, 并将其移动到任意一个堆(包括自身)的任意位置
        你需要求出最少需要多少次操作, 使得每个堆都转化为其目标状态
        数据保证至少存在一个合法的操作序列
        范围: N∈[1,2e5], a,b,c,d∈[0,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先分析操作性质, 由于每次取出的元素都能放到任意位置, 那么我们必然可以把他放到一个"合适"的位置
        使得它后续不再需要调整, 换句话说, 每个数最多移动一次
        有了这个性质后, 我们就只需要分析哪些数是必须移动的就可以了
        对于每个堆(a,b,c,d):
        (1)如果a > c:
            那么多出来的a - c个0必须要移动, 我们无需思考会移动到哪里, 根据上面分析的性质, 这个数
            最多操作一次, 且目前必须操作一次, 因此答案加上a - c
        (2)如果b > d:
            进行完(1)之后, 我们的堆顶还剩余min(a,c)个0, 为了把b - d个1移除, 我们必须把这些0下移
            把b-d个1顶上来, 因此答案加上min(a,c) + b - d
*/
void solve() {
    int n;
    cin >> n;
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        if(a > c) {
            ans += a - c;
        }
        if(b > d) {
            ans += min(a, c) + b - d;
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
