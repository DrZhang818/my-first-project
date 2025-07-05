#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.lanqiao.cn/problems/19703/learning/
/*
    差分 || 前缀和 || 贪心
    题意:
        有n名士兵, 每名士兵有两个属性val和cnt, 表示该名士兵至少要训练cnt次, 每次消耗val代价
        现给定一个正整数S表示训练一次全部士兵的代价
        你有以下操作方式:
        op1: 选定一名士兵, 并训练一次
        op2: 训练全部士兵一次, 消耗S代价
        求让所有士兵i都至少训练cnt[i]次所需的最小代价
        范围: n∈[1,1e5], val,cnt∈[1,1e6], S∈[1,1e10]
    关键思考:
        本题是决策类题目, 常用思考方式为: 暴力->贪心||DP, 常用优化手段为: 前缀和、二分、数据结构
        首先思考决策函数F与什么有关
        对于本题来说, 显然与op2的操作次数有关, 当op2的操作次数定了, 总代价也就定了
        F(x) = x * S + Σval[i] * max(cnt[i] - x, 0), i∈[1,n]
        目标就是求min{F(x)}
        暴力枚举x的时间复杂度是O(n * cnt)的, 主要瓶颈在于∑的计算
        这里有一个很显然的贪心优化: 
            考虑单次操作, 如果在这一次里面S比此时的∑val[i]小(cnt[i]不为0), 那么就肯定选S更优
        因此我们希望快速知道在第i次里面的S与Σval[i]的关系
        我们可以做一个差分数字, 对于每个i, 在D[1] += val[i], 在D[cnt[i]+1] -= val[i]
        这样就统计出每一次的Σval[i], 就能一次遍历解决了
*/
struct info {
    ll val, cnt;
};
void solve() { 
    ll n, S;
    cin >> n >> S;
    vector<info> a(n + 1);
    ll mx = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].val >> a[i].cnt;
        mx = a[i].cnt > mx ? a[i].cnt : mx;
    }
    vector<ll> b(mx + 2);
    for(int i = 1; i <= n; i++) {
        int x = a[i].cnt;
        b[1] += a[i].val;
        b[x + 1] -= a[i].val;
    }
    ll ans = 0, cur = 0;
    for(int i = 1; i <= mx; i++) {
        cur += b[i];
        if(cur > S) {
            ans += S;
        } else {
            ans += cur;
        }
    }    
    cout << ans << "\n";
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
