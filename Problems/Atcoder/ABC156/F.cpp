#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc156/tasks/abc156_f
/*
    数论 || 容斥原理
    题意:
        给定一个长度为K的序列d, 接下来有Q组询问, 每次询问给出n,x,m
        你需要按照下面要求生成一个长度为n的序列a, 并求出满足a[i]%m < a[i+1]%m的数量
        a[1] = x
        i >= 2时, a[i] = a[i - 1] + d[(i - 1) % K]
        范围: K∈[1,5000], Q∈[1,5000], d[i],a[i]∈[0,1e9], n,m∈[2,1e9]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先观察题目性质, 由于a[i]的生成方式是k-环的, 因此我们必然要利用周期性来解决题目
        由于运算是在模m意义下进行的, 因此对于每组询问, 加d[i]与加d[i] % m是等价的
        a[i + 1]是在a[i]基础上加上一个非负整数x, 且x < m
        我们思考什么时候a[i] % m会小于a[i + 1] % m
        可以用m-进制的方式理解这件事, 当x不为0, 且加上x不发生进位的时候, a[i] < a[i + 1]
        这件事显然并不好计算, 因为我们并不能预测哪些位置不会发生进位
        但我们可以从反面思考, 看哪些位置会发生进位以及哪些位置x = 0
        (1)对于x = 0是很好想的, 我们利用贡献法, 算出每个a[i] % m贡献了多少次就可以了
        (2)对于计算哪些位置会进位, 其实和不进位难度是一样的, 我们都无法预测
            但我们其实并不需要真的知道哪些地方发生了进位, 只需要算出来总共进了多少位就足够了
            同样利用贡献法, 我们可以在O(k)的时间内计算出来a[n]是多少
            利用a[n] / m - a[1] / m, 我们就可以精确计算出一共发生了多少次进位
        利用容斥原理, 我们通过计算两种容易计算的反面情况得到了要求的复杂问题, 这是本题带给我们
        的最大启发
        同时, 我们也要把模运算 和 进制 联系起来, 从进制角度思考才会发现可以把问题转成"进位"
        这件事
*/
void solve() {
    int k, q;
    cin >> k >> q;
    vector<ll> a(k + 1);
    for(int i = 1; i <= k; i++) {
        cin >> a[i];
    }
    auto cal = [&](ll n, ll x, ll m) -> ll {
        ll c0 = 0, c1 = 0;
        ll cnt = (n - 1) / k, rem = (n - 1) % k;
        ll tot = x % m;
        for(int i = 1; i <= k; i++) {
            if(a[i] % m == 0) {
                if(i <= rem) {
                    c0 += cnt + 1;
                } else {
                    c0 += cnt;
                }
            }
            if(i <= rem) {
                tot += (cnt + 1) * (a[i] % m);
            } else {
                tot += cnt * (a[i] % m);
            }
            c1 += tot / m;
            tot %= m;
        }
        return n - 1 - c0 - c1;
    };  
    while(q--) {
        ll n, x, m;
        cin >> n >> x >> m;
        cout << cal(n, x, m) << "\n";
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
