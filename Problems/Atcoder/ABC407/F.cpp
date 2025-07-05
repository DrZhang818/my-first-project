#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc407/tasks/abc407_f
/*
    单调栈 || 二阶差分
    题意:
        给定一个长度为N的数组, 对于K∈[1,N], 数组有N-K+1个长度为K的子数组
        定义每个子数组的权值为子数组内最大的元素值
        对于每个K, 请你求出这K个子数组的权值和
        范围: N∈[1,2e5], a[i]∈[0,1e7]
    关键思考:
        本题为数据结构类题目, 需要读请题意, 选用合适的算法和数据结构维护题目信息, 回答询问
        首先思考暴力做法, 对于每个K都暴力计算, 时间复杂度为O(N^2), 超时
        优化的方式比较显然, 要利用贡献法, 思考每个元素会对哪些K做贡献
        首先利用单调栈求出每个元素的有效作用边界[L,R]
        那么向左延伸的个数是i-L+1, 向右延伸的个数是R-i+1
        下面我们令L = min(i-L+1,R-i+1), R = max(i-L+1,R-i+1)
        不难发现, 对于这个元素, 受其影响的K的范围是[1,L+R-1]
        但是难点在于, 对于不同的K, 贡献的次数不同
        如果对于每个K再去单独计算贡献次数, 时间复杂度还是O(N^2)的
        继续观察, 我们发现一下性质:
        (1)对于K∈[1,L], 贡献的次数就是K
        (2)对于K∈[L+1,R], 贡献的次数是L
        (3)对于K∈[R+1,L+R-1], 贡献的次数是L+R-K
        这是一个梯形的形状, 难点在于如何O(1)添加等差数列型贡献
        可以利用二阶差分解决
        如果要在数组区间[L,R]内加入首项为s, 公差为d的等差数列
        我们需要处理好边界点的衔接 以及 斜率修正
        一般的有这样的公式:
        设首项为s, 末项为e = s + (R-L)*d
        d[L] += s, d[L+1] += d - s
        d[R+1] -= d + e, d[R+2] += d
        可以把斜率看作惯性, 当我们调整的时候, 先要抵消惯性, 然后再调数值
        例如
            0 0 0 1 2 3 4  4 4 4  3 2 1 0 0 0 0
        d=[ 0 0 0 1 0 0 0 -1 0 0 -1 0 0 0 1 0 0]
        如果要打破等差数列, 先将斜率调成0, 然后思考数值变化, 接着在下一步调整斜率
*/  
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    stack<int> stk;
    vector<int> pre(n + 1, 0), suf(n + 1, n + 1);
    for(int i = 1; i <= n; i++) {
        while(!stk.empty() && a[stk.top()] <= a[i]) {
            suf[stk.top()] = i;
            stk.pop();
        }
        if(!stk.empty()) pre[i] = stk.top();
        stk.push(i);
    }
    vector<ll> d(n + 3);
    for(int i = 1; i <= n; i++) {
        ll l = i - pre[i], r = suf[i] - i;
        if(r < l) swap(l, r);
        d[1] += a[i], d[l + 1] -= a[i];
        d[r + 1] -= a[i], d[l + r + 1] += a[i];
    }
    for(int i = 1; i <= n; i++) {
        d[i] += d[i - 1];
    }
    for(int i = 1; i <= n; i++) {
        d[i] += d[i - 1];
    }
    for(int i = 1; i <= n; i++) {
        cout << d[i] << "\n";
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
