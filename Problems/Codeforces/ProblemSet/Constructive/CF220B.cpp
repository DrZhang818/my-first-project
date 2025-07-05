#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/220/B
/*
    离线 || 前缀和
    题意:
        给定一个长度为N的数组, 接下来有Q次询问, 每次询问给定一个区间[l,r], 回答a[l:r]中有
        多少个x, 满足x的出现次数恰好为x
        范围: N∈[1,1e5], Q∈[1,1e5], a[i]∈[1,1e9]
    关键思考:
        本题属于数据结构类题目, 需要读清题意, 选用合适的算法和数据结构维护题目信息, 回答询问
        首先思考暴力方法, 对于每个询问, 遍历a[l:r], 统计有多少个合法数字即可, 复杂度为O(Q*N)
        下面考虑优化方法, 由x的性质可知, m个合法数字的长度至少为1+2+...+m
        因此长度为N的数组最多有O(sqrt(N))个合法数字
        那么我们可以收集所有的合法数字, 然后暴力计算每个数字带来的贡献
        显然, 为了快速得到区间内的数字个数, 可以预处理前缀和
        这样时间复杂度为O(sqrt(N) * (N + Q))
*/
struct info {
    int l, r;
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        if(a[i] <= n) {
            cnt[a[i]]++;
        }
    }
    vector<int> val;
    for(int i = 1; i <= n; i++) {
        if(cnt[i] >= i) {
            val.push_back(i);
        }
    }
    vector<info> Q(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> Q[i].l >> Q[i].r;
    }
    vector<int> ans(m + 1);
    for(int v : val) {
        vector<int> pre(n + 1);
        for(int i = 1; i <= n; i++) {
            if(a[i] == v) {
                pre[i] = pre[i - 1] + 1;
            } else {
                pre[i] = pre[i - 1];
            }
        }
        for(int i = 1; i <= m; i++) {
            auto [l, r] = Q[i];
            if(pre[r] - pre[l - 1] == v) {
                ans[i]++;
            }
        }
    }
    for(int i = 1; i <= m; i++) {
        cout << ans[i] << "\n";
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
