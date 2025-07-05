#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;



//https://codeforces.com/problemset/problem/1646/C
/*
    DFS
    题意:
        给定一个整数N, 定义一个数是好数, 当且仅当它可以表示为2^d或d!
        你需要把N拆解为k个不同的好数之和, 现要求计算出k的最小值
        如果k不存在, 输出-1
        范围: n∈[1,1e12], t∈[1,100]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先分析下题目的一些性质:
        (1)题目一定有解, 因为2进制可以表示任意[1,1e12]的整数
        (2)15! > 1e12, 我们得到的好数集合范围很小
        (3)x的二进制中1的个数就是单独使用形如2^d的好数所需的个数
        由性质(2)我们可以知道, 最多有14个阶乘, 根据选或不选产生2^14种状态
        我们可以枚举每种状态, 利用__builtin_popcount函数O(1)计算二进制中1的个数
        总时间复杂度为O(2^MX), 其中MX为最后一个小于等于N的阶乘的序号
        因此我们可以写一个dfs来枚举组合, 也可以使用二进制状态压缩来实现
        但由于状态数不多, dfs的代码更容易编写
*/
constexpr ll MX = 1e12 + 5;
vector<ll> fac;
void solve() { 
    ll n;
    cin >> n;
    int ans = 1000000000, m = fac.size();
    auto dfs = [&](this auto &&dfs, ll x, int cnt, int pos) -> void {
        if(cnt > ans || x < 0) return;
        if(pos >= m) {
            ans = min(ans, __builtin_popcountll(x) + cnt);
            return;
        }
        dfs(x, cnt, pos + 1);
        dfs(x - fac[pos], cnt + 1, pos + 1);
    };
    dfs(n, 0, 0);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    
    ll cur = 1;
    for(ll i = 1; cur < MX; i++) {
        cur *= i;
        fac.push_back(cur);
    }
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
